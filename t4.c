#include <stdlib.h>
#include <glib/gprintf.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>     /* for gtk_plug */
#include "desktop.h"

#define PROMPT "Launch : "
#define COMPLETION_TIMEOUT 100
#define MINWIDTH 260    // la suma de min-width gtk-entry + gtk-label (15 caracteres)
#define FONT "12px Sans"
#define CO  "White"
#define BC  "LightSlateGray"
#define FC  "White"
#define FB  "MediumBlue"
#define PC  "White"
#define PB  "LightSlateGray"
#define EC  "White"
#define EB  "DimGray"


struct Options
{
  guint x;
  guint y;
  guint W;
  guint l;    // listing, num rows
  gboolean b; // bottom
  char *p;    // prompt
  char *f;    // font
  char *t;    // terminal
  char *co;   // foreground color
  char *bc;   // normal background color
  char *fc;   // focused color
  char *fb;   // focused background color
  char *pc;   // prompt foreground color
  char *pb;   // prompt background color
  char *ec;   // entry color
  char *eb;   // entry background color
  gboolean n; // persistent, no quit on lost focus
  char *w;    //embed X11, windowid
  gboolean v;
};

struct Monitor;

struct Top
{
  GtkWidget *window;
  GtkWidget *entry;
  GtkWidget *prompt;
  GdkRectangle rect;
  struct Monitor *monitor;
};

struct Popup
{
  GtkWidget *window;
  GtkWidget *scrolled;
  GtkWidget *flow;
  GtkWidget *items;
  gchar *key;
  GtkFlowBoxChild *child_first;
  gint count_child;
  GdkRectangle rect;  // tamaño del popup
  GtkAdjustment *adj;
  gdouble lower;      // adjusment value
  struct Monitor *monitor;
  struct Top *top;
  struct Options *opt;
};

struct Monitor
{
  GdkMonitor *mon;
  GdkRectangle area;
  gboolean wayland_backend;
};

enum scroll {
    POS,
    PREVIOUS,
    NEXT,
    PAGENEXT,
    PAGEPREVIOUS,
    FIRST,
    END,
};

gboolean DESKTOP;

static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer userdata)
{
  cairo_set_source_rgba (cr, 0.0, 0.0, 0.0, 0.0); /* transparent */
  cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);
  cairo_paint (cr);
  return FALSE;
}

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer userdata)
{
  /* To check if the display supports alpha channels, get the visual */
  GdkScreen *screen = gtk_widget_get_screen(widget);
  GdkVisual *visual = gdk_screen_get_rgba_visual(screen);

  if (!gdk_screen_is_composited (screen))
      /* printf("Your screen does not support alpha channels!\n"); */
      visual = gdk_screen_get_system_visual(screen);
  else
      /* printf("Your screen supports alpha channels!\n"); */
      g_signal_connect (G_OBJECT (widget), "draw", G_CALLBACK (draw), NULL);

  gtk_widget_set_visual(widget, visual);
}

static void
monitor_set (struct Top *top, struct Options *opt)
{
  /*TODO: set monitor */
  GtkWidget *w = top->window;
  GdkDisplay *display;
  GdkWindow *gdk;
  GdkWindow *window;
  const char *t;

  if (opt->w)
    {
      display = gdk_display_get_default ();
      gdk = gdk_x11_window_foreign_new_for_display (display, strtol(opt->w,NULL, 0));
      gdk_window_get_root_origin (gdk, &(top->monitor->area.x), &(top->monitor->area.y));
      top->monitor->area.width = gdk_window_get_width (gdk);
      top->monitor->area.height = gdk_window_get_height (gdk);
      gdk_window_set_transient_for (gtk_widget_get_window (top->window),
                                    gdk);
    }
  else
    {
      display = gtk_widget_get_display (w);
      window = gtk_widget_get_window (w);
      top->monitor->mon = gdk_display_get_monitor_at_window (display, window);
      gdk_monitor_get_geometry (top->monitor->mon, &(top->monitor->area));
    }
  t = gdk_display_get_name (display);
  top->monitor->wayland_backend = !strncmp (t, "wayland", strlen("wayland"));

  return;
}

/* Horizontal {{{1 */
void
g_horizontal (struct Top *top, struct Popup *pop, struct Options *opt)
{
  GtkRequisition req;
  gtk_widget_show_all (top->window);
  gtk_widget_show_all (pop->window);
  monitor_set (top, opt);

  gtk_label_set_ellipsize (GTK_LABEL (top->prompt), PANGO_ELLIPSIZE_END);
  gtk_widget_get_preferred_size (top->window, &req, NULL);
  top->rect.width = req.width;
  top->rect.height = req.height;

  top->rect.width = MINWIDTH;

  top->rect.width++;

  if ((opt->W >= (2 * top->rect.width)) && (opt->W < top->monitor->area.width))
    {
      if (opt->x > top->monitor->area.width)
        {
          top->rect.x = top->monitor->area.width - opt->W;
          pop->rect.x = top->rect.x + top->rect.width;
          pop->rect.width = top->monitor->area.width - pop->rect.x;
        }
      else if (!opt->x)
        {
          top->rect.x = 0;
          pop->rect.x = top->rect.x + top->rect.width;
          pop->rect.width = opt->W - top->rect.width;
        }
      else
        {
          top->rect.x = opt->x > top->monitor->area.width - opt->W ? top->monitor->area.width - opt->W : opt->x;
          pop->rect.x = top->rect.x + top->rect.width;
          pop->rect.width = opt->W - top->rect.width;
        }
    }
  else if (!opt->W)
    {
      if ((!opt->x) || (opt->x > top->monitor->area.width))
        {
          /* width = top->monitor->area.width; */
          top->rect.x = 0;
          pop->rect.x = top->rect.x + top->rect.width;
          pop->rect.width = top->monitor->area.width - top->rect.width;
        }
      else
        {
          /* width = top->monitor->area.width - opt->x; */
          top->rect.x = opt->x;
          pop->rect.x = top->rect.x + top->rect.width;
          pop->rect.width = top->monitor->area.width - top->rect.width - opt->x;
        }
    }
  else
    {
      top->rect.x = 0;
      pop->rect.x = top->rect.x + top->rect.width;
      pop->rect.width = top->monitor->area.width - top->rect.width;
    }

  pop->rect.height = top->rect.height;

  if (opt->b)
    {
      top->rect.y = top->monitor->area.height - top->rect.height;
      pop->rect.y = top->rect.y;
    }
  else
    {
      top->rect.y = !opt->y ? 0 : opt->y < (top->monitor->area.height - top->rect.height) ?
        opt->y : (top->monitor->area.height - top->rect.height);
      pop->rect.y = top->rect.y;
    }

  if (opt->w)
    {
      top->rect.x += top->monitor->area.x;
      pop->rect.x += top->monitor->area.x;
      top->rect.y += top->monitor->area.y;
      pop->rect.y += top->monitor->area.y;
    }

  gtk_widget_set_size_request (top->window, top->rect.width, -1);
  gtk_window_move (GTK_WINDOW (top->window), top->rect.x, top->rect.y);

  gtk_widget_set_size_request (pop->window, pop->rect.width, -1);
  gtk_window_move (GTK_WINDOW (pop->window), pop->rect.x, pop->rect.y);

  return;
}

void
horizontal_scroll (struct Popup * popup, enum scroll sc)
{
  gdouble value, page, upper;
  GtkWidget *w;
  GtkAllocation alloc;

  if (!gtk_widget_is_visible (popup->flow))
    return;

  popup->adj = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (popup->scrolled));

  if (sc == NEXT)
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_VISUAL_POSITIONS, 1, &b);
      g_signal_emit_by_name (popup->flow, "toggle-cursor-child");
      value = gtk_adjustment_get_value (popup->adj);
      if (value != popup->lower)
        {
          w = gtk_container_get_focus_child (GTK_CONTAINER (popup->flow));
          gtk_widget_get_allocation (w, &alloc);
          popup->lower = alloc.x;
          gtk_adjustment_set_value (popup->adj, popup->lower);
          gtk_flow_box_set_hadjustment (GTK_FLOW_BOX (popup->flow), popup->adj);
        }
    }
  if (sc == PREVIOUS)
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_VISUAL_POSITIONS, -1, &b);
      g_signal_emit_by_name (popup->flow, "toggle-cursor-child");
      value = gtk_adjustment_get_value (popup->adj);
      if (value != popup->lower)
        {
          page = gtk_adjustment_get_page_size (popup->adj);
          w = gtk_container_get_focus_child (GTK_CONTAINER (popup->flow));
          gtk_widget_get_allocation (w, &alloc);
          popup->lower = alloc.x + alloc.width - page;
          gtk_adjustment_set_value (popup->adj, popup->lower);
          gtk_flow_box_set_hadjustment (GTK_FLOW_BOX (popup->flow), popup->adj);
        }
    }
  if (sc == PAGENEXT)
    {
      page = gtk_adjustment_get_page_size (popup->adj);
      upper = gtk_adjustment_get_upper (popup->adj);
      value = gtk_adjustment_get_value (popup->adj);
      gdouble tmp;
      if (value + page >= upper)
        tmp = upper;
      else
        tmp = value + page;

      w = (GtkWidget *) gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow),
                                                       tmp - 1, popup->rect.height / 2);
      gtk_widget_get_allocation (w, &alloc);
      if (alloc.x + page > upper)
        popup->lower = upper - page;
      else
        popup->lower = alloc.x;

      gtk_adjustment_set_value (popup->adj, popup->lower);
      gtk_flow_box_set_hadjustment (GTK_FLOW_BOX (popup->flow), popup->adj);
      g_signal_emit_by_name (G_OBJECT (w), "activate");
    }
  if (sc == PAGEPREVIOUS)
    {
      page = gtk_adjustment_get_page_size (popup->adj);

      w = (GtkWidget *) gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow),
                                                       popup->lower, popup->rect.height / 2);
      gtk_widget_get_allocation (w, &alloc);
      if (alloc.x - page < 0)
        popup->lower = 0.0;
      else
        popup->lower = alloc.x + alloc.width - page;
      gtk_adjustment_set_value (popup->adj, popup->lower);
      gtk_flow_box_set_hadjustment (GTK_FLOW_BOX (popup->flow), popup->adj);
      g_signal_emit_by_name (G_OBJECT (w), "activate");
    }
  if (sc == FIRST)
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_BUFFER_ENDS, -1, &b);
      popup->lower = 0.0;
    }
  if (sc == END)
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_BUFFER_ENDS, 1, &b);
      upper = gtk_adjustment_get_upper (popup->adj);
      page = gtk_adjustment_get_page_size (popup->adj);
      popup->lower = upper - page;
    }

}
/* }}}1 */

/* Vertical {{{2 */
void
g_popup_resize (struct Top *top, struct Popup *popup, struct Options *opt)
{
  GList *list;
  gint child_height, tmp, tmp_lim;

  gtk_widget_show_all (popup->window);
  gtk_widget_show_all (top->window);

  popup->rect.width = top->rect.width;
  popup->rect.x = top->rect.x;
  list = gtk_container_get_children (GTK_CONTAINER (popup->flow));

  gtk_widget_get_preferred_height (GTK_WIDGET (list->data), NULL, &child_height);

  if (!popup->count_child)
    {
      gtk_widget_hide (popup->window);
      return;
    }

  tmp= popup->count_child * child_height;

  tmp_lim = opt->l * top->rect.height;
  popup->rect.height = MIN(tmp, tmp_lim);

  if (opt->b)
    {
      if (popup->rect.height > top->rect.y)
        popup->rect.height = top->rect.y;
      popup->rect.y = top->rect.y - popup->rect.height <= 0 ? 0 : top->rect.y - popup->rect.height;
      if (top->monitor->wayland_backend)
        popup->rect.y = -(popup->rect.height + top->rect.y + top->rect.height- top->monitor->area.height);
    }
  else
    {
      if (popup->rect.height >= (top->monitor->area.height -
                                 (top->rect.y - top->monitor->area.y) + top->rect.height))
        popup->rect.height = top->monitor->area.height - (top->rect.y - top->monitor->area.y) - top->rect.height;
      popup->rect.y = top->rect.y + top->rect.height;
    }

  if (popup->count_child < 3)
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (popup->scrolled),
                                    GTK_POLICY_NEVER, GTK_POLICY_NEVER);
  else
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (popup->scrolled),
                                    GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

  gtk_widget_set_size_request (popup->window, popup->rect.width, popup->rect.height);
  if (top->monitor->wayland_backend)
    {
      gtk_widget_hide (popup->window);
      gtk_window_move (GTK_WINDOW (popup->window), popup->rect.x, popup->rect.y);
      gtk_widget_show (popup->window);
    }
  else
    {
      gtk_window_move (GTK_WINDOW (popup->window), popup->rect.x, popup->rect.y);
      gtk_widget_show (popup->window);
    }

  return;
}

void
g_vertical (struct Top *top, struct Popup *pop, struct Options *opt)
{
  GtkRequisition req;
  gtk_widget_show_all (top->window);
  monitor_set (top, opt);

  gtk_label_set_ellipsize (GTK_LABEL (top->prompt), PANGO_ELLIPSIZE_END);
  gtk_widget_get_preferred_size (top->window, &req, NULL);
  top->rect.width = req.width;
  top->rect.height = req.height;

  if (!opt->W)
    pop->rect.width = top->rect.width = MINWIDTH;

  if ((opt->W >= top->rect.width) && (opt->W < top->monitor->area.width))
    {
      top->rect.width =  opt->W;
      if (opt->x > top->monitor->area.width)
        top->rect.x = top->monitor->area.width - top->rect.width;
      else if (opt->x)
        top->rect.x = opt->x > top->monitor->area.width - opt->W ? top->monitor->area.width - opt->W : opt->x;
      else
        top->rect.x = 0;
    }
  else if (!opt->W)
    {
      if ((!opt->x))
        top->rect.x = 0;
      else if (opt->x < top->monitor->area.width)
        top->rect.x = opt->x < top->monitor->area.width - top->rect.width ?
          opt->x : top->monitor->area.width - top->rect.width;
      else
        top->rect.x = top->monitor->area.width - top->rect.width;
    }
  else if (opt->W > top->monitor->area.width)
    {
      top->rect.x = 0;
      top->rect.width = top->monitor->area.width;
    }
  else
    {
      if (opt->x > top->monitor->area.width)
        top->rect.x = top->monitor->area.width - top->rect.width;
      else
        top->rect.x = opt->x;
    }

  /* vertical */
  if (opt->b)
    {
      if (opt->y >= top->monitor->area.height - top->rect.height)
        top->rect.y = top->monitor->area.height - top->rect.height;
      else
        top->rect.y = !opt->y ? top->monitor->area.height - top->rect.height : opt->y > top->rect.height ?
          opt->y : top->monitor->area.height - top->rect.height;
    }
  else
    {
      top->rect.y = !opt->y ? 0 : opt->y < (top->monitor->area.height -  2 * top->rect.height) ?
        opt->y : 0;
    }

  if (opt->w)
    {
      top->rect.x += top->monitor->area.x;
      top->rect.y += top->monitor->area.y;
    }

  gtk_widget_set_size_request (top->window, top->rect.width, -1);
  gtk_window_move (GTK_WINDOW (top->window), top->rect.x, top->rect.y);

  g_popup_resize (top, pop, opt);

  return;
}

static void
vertical_scroll (struct Popup *popup, enum scroll sc)
{
  gdouble value, page, upper;
  GtkWidget *w;
  GtkAllocation alloc;
  gboolean b;

  if (!gtk_widget_is_visible (popup->window))
    return;

  popup->adj = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (popup->scrolled));

  if (sc == NEXT)
    {
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_VISUAL_POSITIONS, 1, &b);
      g_signal_emit_by_name (popup->flow, "toggle-cursor-child");
      value = gtk_adjustment_get_value (popup->adj);
      if (value != popup->lower)
        {
          w = gtk_container_get_focus_child (GTK_CONTAINER (popup->flow));
          gtk_widget_get_allocation (w, &alloc);
          popup->lower = alloc.y;
          gtk_adjustment_set_value (popup->adj, popup->lower);
          gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (popup->flow), popup->adj);
        }
    }
  if (sc == PREVIOUS)
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_VISUAL_POSITIONS, -1, &b);
      g_signal_emit_by_name (popup->flow, "toggle-cursor-child");
      value = gtk_adjustment_get_value (popup->adj);
      if (value != popup->lower)
        {
          page = gtk_adjustment_get_page_size (popup->adj);
          w = gtk_container_get_focus_child (GTK_CONTAINER (popup->flow));
          gtk_widget_get_allocation (w, &alloc);
          popup->lower = alloc.y + alloc.height - page;
          gtk_adjustment_set_value (popup->adj, popup->lower);
          gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (popup->flow), popup->adj);
        }
    }
  if (sc == PAGENEXT)
    {
      value = gtk_adjustment_get_value (popup->adj);
      page = gtk_adjustment_get_page_size (popup->adj);
      upper = gtk_adjustment_get_upper (popup->adj);
      gdouble tmp;
      if (value + page > upper)
        tmp = upper - page;
      else
        tmp = value + page - 3;
      w = (GtkWidget *) gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow),
                                                       1, tmp);
      gtk_widget_get_allocation (w, &alloc);
      if (alloc.y + page > upper)
        popup->lower = upper - page;
      else
        popup->lower = alloc.y;
      gtk_adjustment_set_value (popup->adj, popup->lower);
      gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (popup->flow), popup->adj);
      g_signal_emit_by_name (G_OBJECT (w), "activate");
    }
  if (sc == PAGEPREVIOUS)
    {
      value = gtk_adjustment_get_value (popup->adj);
      page = gtk_adjustment_get_page_size (popup->adj);

      w = (GtkWidget *) gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow),
                                                       2, popup->lower);
      gtk_widget_get_allocation (w, &alloc);
      if (alloc.y - page < 0)
        popup->lower = 0.0;
      else
        popup->lower = alloc.y + alloc.height - page;

      gtk_adjustment_set_value (popup->adj, popup->lower);
      gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (popup->flow), popup->adj);
      g_signal_emit_by_name (G_OBJECT (w), "activate");
    }
  if (sc == END)
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_BUFFER_ENDS, 1, &b);
      page = gtk_adjustment_get_page_size (popup->adj);
      upper = gtk_adjustment_get_upper (popup->adj);
      popup->lower = upper - page;
      gtk_adjustment_set_value (popup->adj, popup->lower);
      gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (popup->flow), popup->adj);

    }
  if (sc == FIRST)
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_BUFFER_ENDS, -1, &b);
      popup->lower = 0.0;
      gtk_adjustment_set_value (popup->adj, popup->lower);
      gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (popup->flow), popup->adj);
    }
}
/* }}}2 */

static gboolean
parse_opt (int *argc, char ***argv, struct Options *opt)
{
  GError *error = NULL;
  GOptionContext *context;

  GOptionEntry entries[] =
{
{ "xposition", 'x', 0, G_OPTION_ARG_INT, &(opt->x), "<int> pixels", NULL},
{ "yposition:", 'y', 0, G_OPTION_ARG_INT, &(opt->y),"<int> pixels", NULL},
{ "width", 'W', 0, G_OPTION_ARG_INT, &(opt->W), "<int> pixels", NULL},
{ "lines", 'l', 0, G_OPTION_ARG_INT, &(opt->l), "<int>, vertical mode", NULL},
{ "bottom", 'b', 0, G_OPTION_ARG_NONE, &(opt->b), "<strint> prompt at bottom window", NULL},
{ "font", 'f', 0, G_OPTION_ARG_STRING, &(opt->f), "<string>. \"10px Sans\"", NULL},
{ "prompt", 'p', 0, G_OPTION_ARG_STRING, &(opt->p), "<string> prompt", NULL},
{ "terminal", 't', 0, G_OPTION_ARG_STRING, &(opt->t), "terminal", NULL},
{ "windowid", 'w', 0, G_OPTION_ARG_STRING, &(opt->w), "<x11 winid>. embed windowid.", NULL},
{ "focus", 'n', 0, G_OPTION_ARG_NONE, &(opt->n), "no quit on lost focus", NULL},
{ "version", 'v', 0, G_OPTION_ARG_NONE, &(opt->v), "version", NULL},
{ "nc", 0, 0, G_OPTION_ARG_STRING, &(opt->co), "normal foreground color", NULL},
{ "nb", 0, 0, G_OPTION_ARG_STRING, &(opt->bc), "normal background color", NULL},
{ "fc", 0, 0, G_OPTION_ARG_STRING, &(opt->fc), "focused color", NULL},
{ "fb", 0, 0, G_OPTION_ARG_STRING, &(opt->fb), "focused background color", NULL},
{ "pc", 0, 0, G_OPTION_ARG_STRING, &(opt->pc), "prompt color", NULL},
{ "pb", 0, 0, G_OPTION_ARG_STRING, &(opt->pb), "prompt background color", NULL},
{ "ec", 0, 0, G_OPTION_ARG_STRING, &(opt->ec), "entry color", NULL},
{ "eb", 0, 0, G_OPTION_ARG_STRING, &(opt->eb), "entry background color", NULL},
{ NULL }
};

  context = g_option_context_new (NULL);
  g_option_context_add_main_entries (context, entries, NULL);
  g_option_context_set_ignore_unknown_options (context, TRUE);
  g_option_context_set_description (context,
"Color format:\n"
"\t rgba(rr,gg,bb,aa), rgb(rr,gg,bb), #rrggbb, color name.\n"
"Font format:\n"
"\t[style][variant][weight][strech] font-size font-family\n"
"Geometry:\n"
"\t x, y, W, l > monitor size, can be used"
"\t ");

  if (!g_option_context_parse (context, argc, argv, &error))
    {
      g_printf ("option parsing failed: %s\n", error->message);
    }
  if (opt->v)
    {
      fprintf (stdout, "version: %s\nbuild date: %s\n", VERSION,  BUILDDATE);
      exit (EXIT_SUCCESS);
    }

  g_option_context_free (context);
  return TRUE;
}

void
item_insert (struct Popup *pop, char *item)
{
    struct Options *opt = pop->opt;
    GtkWidget *tmp;

    tmp = gtk_label_new (item);
    gtk_label_set_use_markup (GTK_LABEL (tmp), TRUE);
    if (opt->l )
    {
        gtk_widget_set_halign (tmp, GTK_ALIGN_START);
        gtk_label_set_ellipsize (GTK_LABEL(tmp), PANGO_ELLIPSIZE_END);
    }
    gtk_container_add (GTK_CONTAINER (pop->flow), tmp);
    pop->count_child++;
    return;
}

void
read_stdin (struct Popup *popup)
{
  gchar buf[BUFSIZ], *p;

  while (fgets (buf, BUFSIZ, stdin) != NULL)
    {
      if ((p = strchr (buf, '\n')))
        *p = '\0';
      item_insert (popup, buf);
    }
  popup->lower = 0.0;
  return;
}

void
read_desktop (struct Popup *popup)
{
    GList *l;

    desktop_init_list ();
    l = desktop_list;

    while (l != NULL)
    {
        char *buf, *p;
        GList *next = l->next;
        struct item *it = l->data;
        buf = g_strdup_printf ("%s (%s)\n", it->name, (it->generic_name != NULL) ?
                it->generic_name : it->exec_striped);
        if ((p = strchr (buf, '\n')))
            *p = '\0';

        item_insert (popup, buf);
        g_free (buf);
        l = next;
    }
    popup->lower = 0.0;
    return;
}

void
read_input (struct Popup *popup)
{
    if (isatty (fileno (stdin)))
    {
        /* g_printerr ("stdin is connected to a terminal\n"); */
        DESKTOP = TRUE;
        read_desktop (popup);
    }
    else
    {
        read_stdin (popup);
    }
  return;
}

void
set_style (struct Top *top, struct Options *opt)
{
  auto GtkCssProvider *provider;
  GdkScreen *screen;
  provider = gtk_css_provider_new ();
  GString *str = g_string_new(NULL);

  g_string_printf (str,
  " @binding-set gtk-emacs-text-entry "
  " { "
  "   bind '<ctrl>b' { 'move-cursor' (logical-positions, -1, 0) }; "
  "   bind '<shift><ctrl>b' { 'move-cursor' (logical-positions, -1, 1) }; "
  "   bind '<ctrl>f' { 'move-cursor' (logical-positions, 1, 0) }; "
  "   bind '<shift><ctrl>f' { 'move-cursor' (logical-positions, 1, 1) }; "
  "   bind '<alt>b' { 'move-cursor' (words, -1, 0) }; "
  "   bind '<shift><alt>b' { 'move-cursor' (words, -1, 1) }; "
  "   bind '<alt>f' { 'move-cursor' (words, 1, 0) }; "
  "   bind '<shift><alt>f' { 'move-cursor' (words, 1, 1) }; "
  "   bind '<ctrl>a' { 'move-cursor' (paragraph-ends, -1, 0) }; "
  "   bind '<shift><ctrl>a' { 'move-cursor' (paragraph-ends, -1, 1) }; "
  "   bind '<ctrl>e' { 'move-cursor' (paragraph-ends, 1, 0) }; "
  "   bind '<shift><ctrl>e' { 'move-cursor' (paragraph-ends, 1, 1) }; "
  "   bind '<ctrl>y' { 'paste-clipboard' () }; "
  "   bind '<ctrl>d' { 'delete-from-cursor' (chars, 1) }; "
  "   bind '<alt>d' { 'delete-from-cursor' (word-ends, 1) }; "
  "   bind '<ctrl>k' { 'delete-from-cursor' (paragraph-ends, 1) }; "
  "   bind '<alt>backslash' { 'delete-from-cursor' (whitespace, 1) }; "
  "   bind '<ctrl>u' { 'move-cursor' (paragraph-ends, -1, 0) "
  "                    'delete-from-cursor' (paragraph-ends, 1) }; "
  "   bind '<ctrl>h' { 'delete-from-cursor' (chars, -1) }; "
  "   bind '<ctrl>w' { 'delete-from-cursor' (word-ends, -1) }; "
  " } "
  " entry {-gtk-key-bindings: gtk-emacs-text-entry;}"
  " flowbox label {margin: 0px 3px; }"
  " label, entry, flowbox * {font: %s; margin:0px; padding:0px;min-height:12px; border-radius:0px; background-image:none;border:0px;}"
  " scrollbar.horizontal *, slider* {min-height:0px;border:0px; margin:0px; padding:0px; border-radius:0px;}"
  " flowboxchild:not(:selected) label, flowbox {color: %s; background-color: %s;}"
  " flowboxchild:selected {color: %s; background-color: %s; }"
  " #prompt {color: %s; background-color: %s;}"
  " entry {padding-left:2px; color: %s; background-color: %s;}"
  , opt->f? opt->f: FONT, opt->co ? opt->co : CO,\
  opt->bc ? opt->bc : BC, opt->fc ? opt->fc : FC, opt->fb ? opt->fb : FB,\
  opt->pc ? opt->pc : PC, opt->pb ? opt->pb : PB,\
  opt->ec ? opt->ec : EC, opt->eb ? opt->eb : EB);

  gtk_css_provider_load_from_data (provider, str->str, -1, NULL);

  screen = gtk_window_get_screen (GTK_WINDOW (top->window));
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
          GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  g_string_free (str, TRUE);
  return;
}

gboolean
filter (GtkFlowBoxChild *child, gpointer data)
{
  struct Popup *popup = data;
  GtkLabel *label;
  gchar *normalized_string, *case_normalized_string;
  gboolean ret = FALSE;

  if (!popup->key)
    return TRUE;

  label = GTK_LABEL (gtk_bin_get_child (GTK_BIN (child)));
  normalized_string = g_utf8_normalize (gtk_label_get_text (label), -1, G_NORMALIZE_ALL);
  case_normalized_string = g_utf8_casefold (normalized_string, -1);

  if (strstr (case_normalized_string, popup->key))
    {
      popup->count_child++;
      if (!popup->child_first)
        {
          popup->child_first = child;
          g_signal_emit_by_name (G_OBJECT (popup->child_first), "activate");
          gtk_flow_box_select_child (GTK_FLOW_BOX (popup->flow), child);
        }
      ret = TRUE;
    }

  g_free (normalized_string);
  g_free (case_normalized_string);
  return ret;
}

void
completion (struct Popup *popup, struct Options *opt)
{
  popup->flow = gtk_flow_box_new ();

  popup->scrolled = gtk_scrolled_window_new (NULL, NULL);

  if (opt->l )
    {
      gtk_orientable_set_orientation (GTK_ORIENTABLE (popup->flow),
                                      GTK_ORIENTATION_HORIZONTAL);
      gtk_widget_set_name (popup->flow, "vertical");

      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (popup->scrolled),
                                      GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
      gtk_widget_set_valign (GTK_WIDGET (popup->flow), GTK_ALIGN_START);
    }
  else
    {
      gtk_orientable_set_orientation (GTK_ORIENTABLE (popup->flow),
                                      GTK_ORIENTATION_VERTICAL);
      gtk_widget_set_name (popup->flow, "horizontal");

      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (popup->scrolled),
                                      GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
      gtk_widget_set_halign (GTK_WIDGET (popup->flow), GTK_ALIGN_START);

    }
  gtk_flow_box_set_min_children_per_line (GTK_FLOW_BOX(popup->flow), 1);
  gtk_flow_box_set_max_children_per_line (GTK_FLOW_BOX(popup->flow), 1);
  gtk_flow_box_set_filter_func (GTK_FLOW_BOX (popup->flow), filter, popup, NULL);
  gtk_widget_set_name (popup->scrolled, "scrolled");
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (popup->scrolled),
                                       GTK_SHADOW_NONE);
  gtk_flow_box_set_selection_mode (GTK_FLOW_BOX (popup->flow), GTK_SELECTION_BROWSE);

  gtk_widget_show (popup->flow);
  gtk_widget_show (popup->scrolled);

  /* pack it all */
  popup->window = gtk_window_new (GTK_WINDOW_POPUP);
  gtk_widget_set_name (popup->window, "popup");
  gtk_window_set_resizable (GTK_WINDOW (popup->window), FALSE);
  gtk_window_set_accept_focus (GTK_WINDOW (popup->window), FALSE);
  gtk_window_set_skip_pager_hint (GTK_WINDOW (popup->window), FALSE);
  GtkWidget *overlay;
  overlay = gtk_overlay_new ();

  /* transparency */
  gtk_widget_set_app_paintable(popup->window, TRUE);
  g_signal_connect(G_OBJECT(popup->window), "screen-changed", G_CALLBACK(screen_changed), NULL);
  screen_changed (popup->window, NULL, NULL);

  gtk_container_add (GTK_CONTAINER (popup->scrolled), popup->flow);
  gtk_container_add (GTK_CONTAINER (overlay), popup->scrolled);
  gtk_container_add (GTK_CONTAINER (popup->window), overlay);

  return;
}

static void
launch (struct Popup *pop, const char *s)
{
    char *name;
    const char *exec = NULL;
    int i;
    GAppInfo *app_info;
    const struct item *it;

    for (i = 0; s[i] != '('; i++) {}
    name = g_strndup (s, --i);

    it = desktop_get_item (desktop_list, name);
    if (it && name)
    {
        exec = it->exec;
    }
    else // full command line, search exec, if exits in desktop app
    {
        GList *tmp;
        tmp = desktop_list;

        for (i = 0; s[i] != ' '; i++) {}
        name = g_strndup (s, i);

        while (tmp != NULL)
        {
            struct item *ittmp = tmp->data;
            if (g_str_has_prefix (ittmp->exec, name))
            {
                it = ittmp;
                exec = s;
                break;
            }
            tmp = tmp->next;
        }
    }

    if (!exec)
        exit (1);

    if (it && it->terminal)
    {
        // search terminal
        gchar *command, *term;

        term = NULL;
        term = getenv ("TERMINAL");

        if (pop->opt->t)
            term = pop->opt->t;
        else if (!term)
            term = "i3-sensible-terminal";

        command = g_strconcat (term, " -e ", "\"", exec, "\"", NULL);
        app_info = g_app_info_create_from_commandline (command, name, G_APP_INFO_CREATE_NONE, NULL);
        g_free (command);
    }
    else
    {
        app_info = g_app_info_create_from_commandline (exec, name, G_APP_INFO_CREATE_NONE, NULL);
    }

    g_app_info_launch (app_info, NULL, NULL, NULL);

    desktop_free_list ();
    g_free (name);
    gtk_main_quit ();
}

static void
output (struct Popup *pop, gboolean quit)
{
  struct Top *top = pop->top;
  GtkWidget *lab;
  const gchar *st;
  GList *l;

  if (pop->count_child)
    {
      l = gtk_flow_box_get_selected_children (GTK_FLOW_BOX (pop->flow));
      lab = GTK_WIDGET(gtk_bin_get_child(GTK_BIN(l->data)));
      st = gtk_label_get_text(GTK_LABEL(lab));
    }
  else
    {
      st = gtk_entry_get_text (GTK_ENTRY (top->entry));
    }
  if (DESKTOP)
  {
      launch (pop, st);
  }
  else
  {
      g_printf ("%s\n", st);
  }
  if (quit)
    gtk_main_quit();
  else
    return;
}

static void
copy_edit (GtkWidget *entry, struct Popup *popup)
{
  /* confirm input, Print the input text to stdout en exit, returning success */
  GList *l;
  GtkLabel *lab;
  gchar *s;

  if (!gtk_widget_is_visible (popup->window))
    return;
  s = g_malloc (BUFSIZ);
  l = gtk_flow_box_get_selected_children (GTK_FLOW_BOX (popup->flow));
  lab = GTK_LABEL(gtk_bin_get_child(GTK_BIN(l->data)));
  g_sprintf (s, "%s ", gtk_label_get_text (lab));
  gtk_entry_set_text (GTK_ENTRY (entry), s);
  gtk_editable_set_position (GTK_EDITABLE (entry), -1);
  g_free (s);
}

static void
paste_primary (GtkWidget *entry)
{
  /* paste primary */
  gchar *s;
  s = gtk_clipboard_wait_for_text (gtk_clipboard_get(GDK_SELECTION_PRIMARY));
  gtk_entry_set_text (GTK_ENTRY (entry), s);
  gtk_editable_set_position (GTK_EDITABLE (entry), -1);
  g_free (s);
}

gboolean
key_press_event_cb (GtkWidget *w, GdkEvent *event, gpointer data)
{
  struct Popup *popup = data;
  struct Top *top = popup->top;
  struct Options *opt = popup->opt;
  guint key = GDK_KEY_VoidSymbol;
  GdkModifierType state;

  gdk_event_get_keyval (event, &key);
  gdk_event_get_state (event, &state);

#define KEY(x)      (key == GDK_KEY_ ## x)
#define CONTROL(x)  (KEY(x) && state & GDK_CONTROL_MASK)
#define SHIFT(x)    (KEY(x) && state & GDK_SHIFT_MASK)
#define MOD1(x)     (KEY(x) && state & GDK_MOD1_MASK)

  if (KEY(Escape) || CONTROL(c) || CONTROL(g))
    {
      gtk_main_quit ();
      exit (-1);
    }
  if ((KEY(Return) & !CONTROL(Return) & !SHIFT(Return)) || (KEY(m) && CONTROL(m)) || (KEY(j) && CONTROL(j)))
    {
      output (popup, TRUE);
      return TRUE;
    }
  if (SHIFT(Return))
    {
      copy_edit (top->entry, popup);
      return TRUE;
    }
  if (CONTROL(Return))
    {
      /* Confirm selection. Print the selected item to stdout and continues. */
      output (popup, FALSE);
      return TRUE;
    }
  if (CONTROL(Insert))
    {
      paste_primary (top->entry);
      return TRUE;
    }
  if (CONTROL(p) || MOD1(h) || CONTROL(Left) || CONTROL(Tab) || (KEY(Up) & !CONTROL(Up)))
    {
      if (opt->l)
        vertical_scroll (popup, PREVIOUS);
      else
        horizontal_scroll (popup, PREVIOUS);
      return TRUE;
    }
  if (CONTROL(n) || MOD1(l) || CONTROL(Right) || KEY(Tab) || (KEY(Down) & !CONTROL(Down)))
    {
      if (opt->l)
        vertical_scroll (popup, NEXT);
      else
        horizontal_scroll (popup, NEXT);
      return TRUE;
    }
  if (MOD1(j) || MOD1(n) || CONTROL(Down) || KEY(Page_Down))
    {
      if (opt->l)
        vertical_scroll (popup, PAGENEXT);
      else
        horizontal_scroll (popup, PAGENEXT);
      return TRUE;
    }
  if (MOD1(k) || MOD1(p) || CONTROL(Up) || KEY(Page_Up))
    {
      if (opt->l)
        vertical_scroll (popup, PAGEPREVIOUS);
      else
        horizontal_scroll (popup, PAGEPREVIOUS);
      return TRUE;
    }
  if (MOD1(G) || KEY(End))
    {
      if (opt->l)
        vertical_scroll (popup, END);
      else
        horizontal_scroll (popup, END);
      return TRUE;
    }
  if (MOD1(g) || KEY(Home))
    {
      if (opt->l)
        vertical_scroll (popup, FIRST);
      else
        horizontal_scroll (popup, FIRST);
      return TRUE;
    }
  return FALSE;
#undef MOD1
#undef SHIFT
#undef CONTROL
#undef KEY
}

static void
changed_cb (GtkWidget *entry, gpointer data)
{
  gboolean b;
  struct Popup *popup = data;
  struct Options *opt = popup->opt;
  struct Top *top = popup->top;

  gtk_flow_box_unselect_all (GTK_FLOW_BOX (popup->flow));

  popup->child_first = NULL;
  popup->count_child = 0;

  gchar *tmp;
  GtkFlowBoxChild *b_child;

  b_child = gtk_flow_box_get_child_at_index (GTK_FLOW_BOX (popup->flow), 0);
  if (!b_child)
    return ;
  g_free (popup->key);

  tmp = g_utf8_normalize (gtk_entry_get_text (GTK_ENTRY (entry)),
                          -1, G_NORMALIZE_ALL);
  popup->key = g_utf8_casefold (tmp, -1);
  g_free (tmp);

  gtk_flow_box_invalidate_filter (GTK_FLOW_BOX (popup->flow));

  if (opt->l )
  {
      g_popup_resize (top, popup, opt);
  }
  else
  {
      gtk_widget_hide (popup->window);
      gtk_widget_show_all (popup->window);
  }

  if (popup->count_child)
    {
      gtk_widget_show_all (popup->window);
      g_signal_emit_by_name (popup->scrolled, "scroll-child", GTK_SCROLL_START, (opt->l )? FALSE: TRUE, &b);
    }
  else
    {
      gtk_widget_hide (popup->window);
    }

  g_signal_emit_by_name (popup->scrolled, "scroll-child", GTK_SCROLL_START, TRUE, &b);
  return;
}

static gboolean
focus_out_event_cb (GtkWidget *w, GdkEvent *e, gpointer data)
{
  struct Popup *pop =  data;
  if (pop->opt->n)
    {
      if (!pop->monitor->wayland_backend)
        gtk_widget_hide (pop->window);
    }
  else
    gtk_main_quit ();
  return GDK_EVENT_PROPAGATE;
}

int
main (int argc, char *argv[])
{
  struct Top top = {};
  struct Options opt = {};
  struct Popup pop = {};
  struct Monitor mon;
  pop.count_child= 0;
  GtkWidget *hbox;
  top.monitor = &mon;
  pop.monitor = &mon;
  pop.opt = &opt;
  pop.top = &top;

  DESKTOP = FALSE;

  gtk_init (&argc, &argv);
  parse_opt (&argc, &argv, &opt);

  top.window= gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_type_hint (GTK_WINDOW(top.window), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_decorated(GTK_WINDOW(top.window), FALSE);
  gtk_window_set_resizable (GTK_WINDOW (top.window), FALSE);
  gtk_window_set_skip_pager_hint (GTK_WINDOW (top.window), FALSE);
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW (top.window), FALSE);
  gtk_widget_set_app_paintable(top.window, TRUE);
  g_signal_connect (top.window, "destroy",
                    G_CALLBACK (gtk_main_quit), &top.window);
  g_signal_connect(G_OBJECT(top.window), "screen-changed", G_CALLBACK(screen_changed), NULL);
  screen_changed(top.window, NULL, NULL);

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER (top.window), hbox);

  top.prompt = gtk_label_new (opt.p ? opt.p : PROMPT);
  gtk_label_set_max_width_chars (GTK_LABEL (top.prompt), 15);
  gtk_widget_set_name (top.prompt, "prompt");
  gtk_box_pack_start (GTK_BOX (hbox), top.prompt, FALSE, FALSE, 0);

  top.entry = gtk_entry_new ();
  gtk_box_pack_start (GTK_BOX (hbox), top.entry, TRUE, TRUE, 0);
  g_signal_connect (top.entry, "key-press-event", G_CALLBACK (key_press_event_cb), &pop);
  g_signal_connect (top.entry, "changed", G_CALLBACK (changed_cb), &pop);

  completion (&pop, &opt);

  set_style (&top, &opt);

  /* close popup window on lost focus */
  g_signal_connect (G_OBJECT(top.entry), "focus-out-event",
                    G_CALLBACK(focus_out_event_cb), &pop);
  g_signal_connect_swapped (G_OBJECT(top.entry), "focus-in-event",
                           G_CALLBACK(gtk_widget_show_all),pop.window);

  read_input (&pop);

  gtk_window_set_transient_for (GTK_WINDOW (pop.window), GTK_WINDOW (top.window));

  if (opt.l)
      g_vertical (&top, &pop, &opt);
  else
      g_horizontal (&top, &pop, &opt);
  gtk_widget_set_can_focus (pop.flow, TRUE);

  gtk_main ();

  return 0;
}
