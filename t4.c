#include <sys/stat.h>
#include <stdlib.h>
#include <glib/gprintf.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>     /* for gtk_plug */

#define PROMPT "Launch:\t"
#define COMPLETION_TIMEOUT 100
#define MINWIDTH 260    // la suma de min-width gtk-entry + gtk-label (15 caracteres)
#define FONT "12px Sans"
#define CO  "White"
#define BC  "LightSlateGray"
#define SC  "White"
#define SB  "LightCyan"
#define FC  "White"
#define FB  "MediumBlue"
#define SFC "White"
#define SFB "LightCoral"
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
  char *co;   // foreground color
  char *bc;   // normal background color
  char *sc;   // selected color
  char *sb;   // selected background
  char *fc;   // focused color
  char *fb;   // focused background color
  char *sfc;  // selected & focused color
  char *sfb;  // selected & focused background color
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
  gulong timeout;
  GtkFlowBoxChild *child_first;
  gulong completion_timeout;
  gint count_child;
  GdkRectangle rect;    // tamaño del popup
  GtkAdjustment *adj;
  struct Monitor *monitor;
  struct Top *top;
  struct Options *opt;
};

struct Monitor
{
  GdkMonitor *mon;
  GdkRectangle area;
  /* const gchar *name; */
  gboolean wayland_backend;
};

/* GdkRectangle rec_win; */
/* GdkRectangle rec_popup; */

/* debug
   void
   adj_changes_h (GtkAdjustment *a, gpointer data)
   {
   GtkAdjustment *adj;
   GtkFlowBoxChild *child;
   static double value_old;
   double value, upper, lower, step_increment, page_increment, page_size;
   gint tmp;

   if (!gtk_widget_is_visible (popup->flow))
   return;

   g_message ("Changed???");
   adj = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (popup->scrolled));
   g_print ("value: %g\nlower: %g\nupper %g\nstep_increment %g\npage_increment: %g\npage_size %g\n\n",
   gtk_adjustment_get_value (adj),
   gtk_adjustment_get_lower (adj),
   gtk_adjustment_get_upper (adj),
   gtk_adjustment_get_step_increment (adj),
   gtk_adjustment_get_page_increment (adj),
   gtk_adjustment_get_page_size (adj));
   value = gtk_adjustment_get_value (adj);
   page_size = gtk_adjustment_get_page_size (adj);
   upper = gtk_adjustment_get_upper (adj);
   step_increment = gtk_adjustment_get_step_increment (adj);
   page_increment = gtk_adjustment_get_page_increment (adj);
   lower = gtk_adjustment_get_lower (adj);

   child = gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow),
   (gint) value,
   rec_popup.height - 3);

   if (value < lower)
   {
   lower = value - page_size;
   upper = value;
   }
   else
   {
   lower = value;
   upper = value + page_size;
   }

   gtk_adjustment_configure (adj, value, lower, upper, step_increment,
   page_increment, page_size);
   gtk_adjustment_set_lower (adj, lower);
   gtk_adjustment_set_upper (adj, upper);

   gtk_flow_box_set_hadjustment (GTK_FLOW_BOX (popup->flow), adj);
   g_signal_emit_by_name (G_OBJECT (child), "activate");

   return;
   }
   end debug */

static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer userdata)
{
  /* cairo_t *new_cr = gdk_cairo_create(gtk_widget_get_window(widget)); */

  cairo_set_source_rgba (cr, 0.0, 0.0, 0.0, 0.0); /* transparent */
  /* draw the background */
  cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);
  cairo_paint (cr);

  /* cairo_destroy(new_cr); */

  return FALSE;
}

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer userdata)
{
  /* To check if the display supports alpha channels, get the visual */
  GdkScreen *screen = gtk_widget_get_screen(widget);
  GdkVisual *visual = gdk_screen_get_rgba_visual(screen);

  if (!gdk_screen_is_composited (screen))
    {
      /* printf("Your screen does not support alpha channels!\n"); */
      visual = gdk_screen_get_system_visual(screen);
    }
  else
    {
      /* printf("Your screen supports alpha channels!\n"); */
      g_signal_connect (G_OBJECT (widget), "draw", G_CALLBACK (draw), NULL);
      g_signal_connect (G_OBJECT (widget), "draw", G_CALLBACK (draw), NULL);
    }

  gtk_widget_set_visual(widget, visual);
}

/* void */
/* ver_page_next (void) */
/* { */
  /* GtkAdjustment *adj; */
  /* GtkFlowBoxChild *child; */

  /* adj = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (popup->scrolled)); */

  /* double value = gtk_adjustment_get_value (adj); */
  /* double page_size = gtk_adjustment_get_page_size (adj); */
  /* double upper = gtk_adjustment_get_upper (adj); */
  /* gint tmp = (gint) (upper - (value + page_size)); */

  /* if (tmp <= 0) */
    /* value = upper - 5; */
  /* else */
    /* value = value + page_size - 10; */

  /* child = gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow), */
                                         /* 1, */
                                         /* (gint) value); */
  /* gtk_adjustment_set_value (adj, value); */
  /* gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (popup->flow), adj); */
  /* g_signal_emit_by_name (G_OBJECT (child), "activate"); */

  /* return; */
/* } */

/* void */
/* ver_page_back (void) */
/* { */
  /* GtkAdjustment *adj; */
  /* GtkFlowBoxChild *child; */

  /* adj = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (popup->scrolled)); */

  /* double value = gtk_adjustment_get_value (adj); */
  /* double page_size = gtk_adjustment_get_page_size (adj); */
  /* gint tmp = (gint) (value - page_size); */

  /* if (tmp < 0) */
    /* value = 0; */
  /* else */
    /* value = value - page_size + 24; */

  /* child = gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow), */
                                         /* 1, */
                                         /* (gint) value); */
  /* gtk_adjustment_set_value (adj, value); */
  /* gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (popup->flow), adj); */
  /* g_signal_emit_by_name (G_OBJECT (child), "activate"); */

  /* return; */
/* } */

/* void */
/* hor_page_back (GtkAdjustment *a, gpointer data) */
/* { */
  /* GtkAdjustment *adj = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (popup->scrolled)); */
  /* GtkFlowBoxChild *child; */
  /* gint width; */

  /* if (!gtk_widget_is_visible (popup->flow)) */
    /* return; */

  /* double value = gtk_adjustment_get_value (adj) - gtk_adjustment_get_page_increment (adj); */
  /* if (value < 0) */
    /* value = 0; */
  /* child = gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow), */
                                         /* (gint)value, */
                                         /* rec_popup.height - 3); */


  /* g_signal_emit_by_name (G_OBJECT (child), "activate"); */
  /* [> reload new value <] */
  /* adj = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (popup->scrolled)); */

  /* gtk_widget_get_preferred_width (GTK_WIDGET (child), NULL, &width); */
  /* value = gtk_adjustment_get_value (adj) - gtk_adjustment_get_page_size (adj) + width; */
  /* gtk_adjustment_set_value (adj, value); */
  /* gtk_flow_box_set_hadjustment (GTK_FLOW_BOX (popup->flow), adj); */

  /* return; */
/* } */

/* void */
/* hor_page_next (GtkAdjustment *a, gpointer data) */
/* { */
  /* GtkAdjustment *adj = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (popup->scrolled)); */
  /* GtkFlowBoxChild *child; */

  /* if (!gtk_widget_is_visible (popup->flow)) */
    /* return; */

  /* double value = gtk_adjustment_get_value (adj); */
  /* double page_size =  gtk_adjustment_get_page_size (adj); */
  /* double upper = gtk_adjustment_get_upper (adj); */
  /* gint tmp = (gint) (upper - (value + page_size)); */

  /* if (tmp <= 0) */
    /* { */
      /* value = upper - 5; */
    /* } */
  /* else */
    /* { */
      /* value = value + page_size; */
    /* } */

  /* child = gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow), */
                                         /* (gint) value, */
                                         /* rec_popup.height - 3); */

  /* gtk_adjustment_set_value (adj, value); */
  /* gtk_flow_box_set_hadjustment (GTK_FLOW_BOX (popup->flow), adj); */
  /* g_signal_emit_by_name (G_OBJECT (child), "activate"); */
  /* return; */
/* } */

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

/* void */
/* size_win (void) */
/* { */
  /* GtkRequisition req; */

  /* gtk_widget_get_preferred_size (top->window, &req, NULL); */
  /* rec_win.width = req.width; */
  /* rec_win.height = req.height; */

  /* return; */
/* } */

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

/* void */
/* g_popup_resize (void) */
/* { */
  /* GList *list; */
  /* [> gint count; <] */
  /* gint child_height, tmp, tmp_lim; */

  /* gtk_widget_show_all (popup->window); */
  /* gtk_widget_show_all (top->window); */

  /* rec_popup.width = rec_win.width; */
  /* rec_popup.x = rec_win.x; */
  /* list = gtk_container_get_children (GTK_CONTAINER (popup->flow)); */
  /* [> count = g_list_length (list);  total de child <] */
  /* [> g_message ("items: %i\n", count); <] */

  /* gtk_widget_get_preferred_height (GTK_WIDGET (list->data), NULL, &child_height); */

  /* if (!popup->count_child) */
    /* { */
      /* gtk_widget_hide (popup->window); */
      /* return; */
    /* } */

  /* tmp= popup->count_child * child_height; */

  /* tmp_lim = opt->l * rec_win.height; */
  /* rec_popup.height = MIN(tmp, tmp_lim); */

  /* if (opt->b) */
    /* { */
      /* if (rec_popup.height > rec_win.y) */
        /* rec_popup.height = rec_win.y; */
      /* rec_popup.y = rec_win.y - rec_popup.height <= 0 ? 0 : rec_win.y - rec_popup.height; */
      /* if (monitor.wayland_backend) */
        /* rec_popup.y = -(rec_popup.height + rec_win.y + rec_win.height- monitor.area.height); */
    /* } */
  /* else */
    /* { */
      /* if (rec_popup.height >= (monitor.area.height - (rec_win.y - monitor.area.y) + rec_win.height)) */
        /* rec_popup.height = monitor.area.height - (rec_win.y - monitor.area.y) - rec_win.height; */
      /* rec_popup.y = rec_win.y + rec_win.height; */
    /* } */

  /* if (popup->count_child < 3) */
    /* gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (popup->scrolled), */
                                    /* GTK_POLICY_NEVER, GTK_POLICY_NEVER); */
  /* else */
    /* gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (popup->scrolled), */
                                    /* GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC); */

  /* gtk_widget_set_size_request (popup->window, rec_popup.width, rec_popup.height); */
  /* if (monitor.wayland_backend) */
    /* { */
      /* gtk_widget_hide (popup->window); */
      /* gtk_window_move (GTK_WINDOW (popup->window), rec_popup.x, rec_popup.y); */
      /* gtk_widget_show (popup->window); */
    /* } */
  /* else */
    /* { */
      /* gtk_window_move (GTK_WINDOW (popup->window), rec_popup.x, rec_popup.y); */
      /* gtk_widget_show (popup->window); */
    /* } */

  /* return; */
/* } */

#if 0
void
g_vertical (void)
{
  gtk_widget_show_all (top->window);
  monitor_set (top->window);

  size_win ();

  rec_win.width++;

  if ((opt->W >= rec_win.width) && (opt->W < monitor.area.width))
    {
      rec_win.width =  opt->W;
      if (opt->x > monitor.area.width)
        rec_win.x = monitor.area.width - rec_win.width;
      else if (opt->x)
        rec_win.x = opt->x > monitor.area.width - opt->W ? monitor.area.width - opt->W : opt->x;
      else
        rec_win.x = 0;
    }
  else if (!opt->W)
    {
      if ((!opt->x))
        rec_win.x = 0;
      else if (opt->x < monitor.area.width)
        rec_win.x = opt->x < monitor.area.width - rec_win.width ? opt->x : monitor.area.width - rec_win.width;
      else
        rec_win.x = monitor.area.width - rec_win.width;
    }
  else if (opt->W > monitor.area.width)
    {
      rec_win.x = 0;
      rec_win.width = monitor.area.width;
    }
  else
    {
      if (opt->x > monitor.area.width)
        rec_win.x = monitor.area.width - rec_win.width;
      else
        rec_win.x = opt->x;
    }

  /* vertical */

  if (opt->b)
    {
      if (opt->y >= monitor.area.height - rec_win.height)
        rec_win.y = monitor.area.height - rec_win.height;
      else
        rec_win.y = !opt->y ? monitor.area.height - rec_win.height : opt->y > rec_win.height ?
          opt->y : monitor.area.height - rec_win.height;
    }
  else
    {
      rec_win.y = !opt->y ? 0 : opt->y < (monitor.area.height -  2 * rec_win.height) ?
        opt->y : 0;
      /* (monitor.area.height - 2 * rec_win.height); */
    }

  if (opt->w)
    {
      rec_win.x += monitor.area.x;
      rec_win.y += monitor.area.y;
    }

  gtk_widget_set_size_request (top->window, rec_win.width, -1);
  gtk_window_move (GTK_WINDOW (top->window), rec_win.x, rec_win.y);

  g_popup_resize ();

  return;
}
# endif

static gboolean
parse_opt (int *argc, char ***argv, struct Options *opt)
{
  GError *error = NULL;
  GOptionContext *context;

  GOptionEntry entries[] =
{
{ "xposition", 'x', 0, G_OPTION_ARG_INT, &(opt->x), "pixels. If x > monitor width , situate to rigth screen", NULL},
{ "yposition:", 'y', 0, G_OPTION_ARG_INT, &(opt->y), "pixels. If y > monitor height, situate to bottom screen", NULL},
{ "width", 'W', 0, G_OPTION_ARG_INT, &(opt->W), "pixels. In vertical mode, W > monitor width -> screen width", NULL},
{ "lines", 'l', 0, G_OPTION_ARG_INT, &(opt->l), "lines, vertical mode", NULL},
{ "bottom", 'b', 0, G_OPTION_ARG_NONE, &(opt->b), "prompt bottom", NULL},
{ "font", 'f', 0, G_OPTION_ARG_STRING, &(opt->f), "font. \"10px Sans [style]\"", NULL},
{ "prompt", 'p', 0, G_OPTION_ARG_STRING, &(opt->p), "String prompt", NULL},
{ "windowid", 'w', 0, G_OPTION_ARG_STRING, &(opt->w), "X11: embed into windowid.", NULL},
{ "focus", 'n', 0, G_OPTION_ARG_NONE, &(opt->n), "No quit on lost focus", NULL},
{ "version", 'v', 0, G_OPTION_ARG_NONE, &(opt->v), "version", NULL},
{ "nc", 0, 0, G_OPTION_ARG_STRING, &(opt->co), "normal foreground color", NULL},
{ "nb", 0, 0, G_OPTION_ARG_STRING, &(opt->bc), "normal background color", NULL},
{ "sb", 0, 0, G_OPTION_ARG_STRING, &(opt->sb), "selected background color", NULL},
{ "sc", 0, 0, G_OPTION_ARG_STRING, &(opt->sc), "selected color", NULL},
{ "fc", 0, 0, G_OPTION_ARG_STRING, &(opt->fc), "focused color", NULL},
{ "fb", 0, 0, G_OPTION_ARG_STRING, &(opt->fb), "focused background color", NULL},
{ "fsc", 0, 0, G_OPTION_ARG_STRING, &(opt->sfc), "focused selected color", NULL},
{ "fsb", 0, 0, G_OPTION_ARG_STRING, &(opt->sfb), "focused selected background color", NULL},
{ "pc", 0, 0, G_OPTION_ARG_STRING, &(opt->pc), "prompt color", NULL},
{ "pb", 0, 0, G_OPTION_ARG_STRING, &(opt->pb), "prompt background color", NULL},
{ "ec", 0, 0, G_OPTION_ARG_STRING, &(opt->ec), "entry color", NULL},
{ "eb", 0, 0, G_OPTION_ARG_STRING, &(opt->eb), "entry background color", NULL},
{ NULL }
};

  context = g_option_context_new (NULL);
  g_option_context_add_main_entries (context, entries, NULL);
  g_option_context_set_ignore_unknown_options (context, TRUE);
  g_option_context_set_description (context, "Geometry: \n"
"\tx > minitor width: stack to right\n"
"\tW > monitor width: width screen\n"
"Color:\n"
"\t ");


  if (!g_option_context_parse (context, argc, argv, &error))
    {
      g_print ("option parsing failed: %s\n", error->message);
    }

  if (opt->v)
    {
      /* fprintf (stdout, "%s - version: %s\nbuild date: %s\n", NAME, VERSION,  BUILDDATE); */
      fprintf (stdout, "%s\n","Copyright © 2018 Alberto Higashikadoguchi <athrun@arnet.com.ar>");
      exit (EXIT_SUCCESS);
    }

  g_option_context_free (context);
  return TRUE;
}

void
read_input (struct Popup *popup)
{
  struct Options *opt = popup->opt;
  guint count = 0;
  gchar buf[BUFSIZ], *p;
  GtkWidget *tmp;

  for (; fgets (buf, BUFSIZ, stdin); count ++)
    {
      if ((p = strchr (buf, '\n')))
        *p = '\0';
      tmp = gtk_label_new (buf);
      /* gtk_label_set_ellipsize (GTK_LABEL (tmp), PANGO_ELLIPSIZE_MIDDLE); */
      if (opt->l )
        {
          gtk_label_set_xalign (GTK_LABEL(tmp), 0);
          gtk_label_set_line_wrap(GTK_LABEL(tmp), FALSE);
          gtk_label_set_ellipsize (GTK_LABEL(tmp), PANGO_ELLIPSIZE_END);
        }
      gtk_container_add (GTK_CONTAINER (popup->flow), tmp);
      popup->count_child++;
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
  " label, entry, flowbox * {font: %s; margin:0px; padding:0px;min-height:12px; border-radius:0px; background-image:none;border:0px;}"
  " scrollbar.horizontal *, slider* {min-height:0px;border:0px; margin:0px; padding:0px; border-radius:0px;}"
  " flowboxchild:not(:selected), flowbox {color: %s; background-color: %s;}"
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
#if 0
gboolean
filter (GtkFlowBoxChild *child, gpointer dada)
{
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
          /* g_print ("Index: %i\n", (gtk_flow_box_child_get_index (child))); */
          g_signal_emit_by_name (G_OBJECT (popup->child_first), "activate");
          gtk_flow_box_select_child (GTK_FLOW_BOX (popup->flow), child);
        }
      ret = TRUE;
    }

  g_free (normalized_string);
  g_free (case_normalized_string);
  return ret;
}
#endif

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
      gtk_flow_box_set_column_spacing (GTK_FLOW_BOX (popup->flow), 4);
      gtk_widget_set_name (popup->flow, "horizontal");

      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (popup->scrolled),
                                      GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);

    }
  gtk_flow_box_set_min_children_per_line (GTK_FLOW_BOX(popup->flow), 1);
  gtk_flow_box_set_max_children_per_line (GTK_FLOW_BOX(popup->flow), 1);
  /* gtk_flow_box_set_filter_func (GTK_FLOW_BOX (popup->flow), filter, NULL, NULL); */
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
  g_print ("%s\n", st);
  gtk_main_quit();
}

gboolean
key_press_event_cb (GtkWidget *w, GdkEvent *event, gpointer data)
{
  struct Popup *popup = data;
  struct Top *top = popup->top;
  /* struct Options *opt = popup->opt; */
  guint key = GDK_KEY_VoidSymbol;
  GdkModifierType state;

  gdk_event_get_keyval (event, &key);
  gdk_event_get_state (event, &state);

#define KEY(x)      (key == GDK_KEY_ ## x)
#define CONTROL(x)  (KEY(x) && state & GDK_CONTROL_MASK)
#define SHIFT(x)    (KEY(x) && state & GDK_SHIFT_MASK)
#define MOD1(x)     (KEY(x) && state & GDK_MOD1_MASK)


  if (KEY(Escape) || CONTROL(c))
    {
      gtk_main_quit ();
      exit (-1);
    }
  else if ((KEY(Return) & !CONTROL(Return) & !SHIFT(Return)) || (KEY(m) && CONTROL(m)))
    {
      output (popup, TRUE);
      return TRUE;
    }
  else if (SHIFT(Return))
    {
      /*confirm input, Print the input text to stdout en exit, returning success */
      /* GList *l; */
      /* GtkLabel *lab; */
      /* gchar *s; */

      /* if (!popup->count_child) */
        /* return TRUE; */
      /* s = g_malloc (BUFSIZ); */
      /* l = gtk_flow_box_get_selected_children (GTK_FLOW_BOX (popup->flow)); */
      /* lab = GTK_LABEL(gtk_bin_get_child(GTK_BIN(l->data))); */
      /* g_sprintf (s, "%s ", gtk_label_get_text (lab)); */
      /* gtk_entry_set_text (GTK_ENTRY (top->entry), s); */
      /* gtk_editable_set_position (GTK_EDITABLE (top->entry), -1); */
      /* g_free (s); */

      return TRUE;
    }
  else if (CONTROL(Return))
    {
      /* Confirm selection. Print the selected item to stdout and continues. */
      return TRUE;
    }
  else if (CONTROL(Insert))
    {
      /* paste primary */
      gchar *s;
      s = gtk_clipboard_wait_for_text (gtk_clipboard_get(GDK_SELECTION_PRIMARY));
      gtk_entry_set_text (GTK_ENTRY (top->entry), s);
      gtk_editable_set_position (GTK_EDITABLE (top->entry), -1);
      g_free (s);
      return TRUE;
    }
  else if (CONTROL(p) || CONTROL(k) || CONTROL(Left) || CONTROL(Tab) || (KEY(Up) & !CONTROL(Up)))
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_VISUAL_POSITIONS, -1, &b);
      g_signal_emit_by_name (popup->flow, "toggle-cursor-child");
      return TRUE;
    }
  else if (CONTROL(n) || CONTROL(j) || CONTROL(Right) || KEY(Tab) || (KEY(Down) & !CONTROL(Down)))
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_VISUAL_POSITIONS, 1, &b);
      if (!KEY(Tab))
        g_signal_emit_by_name (popup->flow, "toggle-cursor-child");
      return TRUE;
    }
  else if (MOD1(j) || MOD1(n) || CONTROL(Down))
    {
      /* if (!opt->l) */
        /* [> hor_page_next (NULL, NULL); <] */
      /* else */
        /* { */
          /* [> ver_page_next (); <] */
        /* } */
      return TRUE;
    }
  else if (MOD1(k) || MOD1(p) || CONTROL(Up))
    {
      /* if (!opt->l) */
        /* hor_page_back (NULL, NULL); */
      /* else */
        /* [> ver_page_back (); <] */
      return TRUE;
    }
  else if (MOD1(g))
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_BUFFER_ENDS, 1, &b);
      /* g_signal_emit_by_name (popup->flow, "activate-cursor-child"); */
      return TRUE;
    }
  else if (MOD1(G))
    {
      gboolean b;
      g_signal_emit_by_name (popup->flow, "move-cursor", GTK_MOVEMENT_BUFFER_ENDS, -1, &b);
      /* g_signal_emit_by_name (popup->flow, "activate-cursor-child"); */
      return TRUE;
    }
  else
    return FALSE;


  return FALSE;
#undef MOD1
#undef SHIFT
#undef CONTROL
#undef KEY
}

/* static void */
/* changed_cb (GtkWidget *widget, gpointer data) */
/* { */
  /* gboolean b; */

  /* if (popup->completion_timeout) */
    /* { */
      /* g_source_remove (popup->completion_timeout); */
      /* popup->completion_timeout = 0; */
    /* } */
  /* gtk_flow_box_unselect_all (GTK_FLOW_BOX (popup->flow)); */

  /* popup->child_first = NULL; */
  /* popup->count_child = 0; */

  /* gchar *tmp; */
  /* GtkFlowBoxChild *b_child; */

  /* b_child = gtk_flow_box_get_child_at_index (GTK_FLOW_BOX (popup->flow), 0); */
  /* if (!b_child) */
    /* return ; */
  /* g_free (popup->key); */

  /* tmp = g_utf8_normalize (gtk_entry_get_text (GTK_ENTRY (top->entry)), */
                          /* -1, G_NORMALIZE_ALL); */
  /* popup->key = g_utf8_casefold (tmp, -1); */
  /* g_free (tmp); */

  /* gtk_flow_box_invalidate_filter (GTK_FLOW_BOX (popup->flow)); */

  /* if (opt->l ) */
    /* { */
      /* g_popup_resize (); */
    /* } */
  /* if (popup->count_child) */
    /* { */
      /* gtk_widget_show_all (popup->window); */
      /* g_signal_emit_by_name (popup->scrolled, "scroll-child", GTK_SCROLL_START, (opt->l )? FALSE: TRUE, &b); */
    /* } */
  /* else */
    /* { */
      /* gtk_widget_hide (popup->window); */
    /* } */

  /* g_signal_emit_by_name (popup->scrolled, "scroll-child", GTK_SCROLL_START, TRUE, &b); */
  /* return; */
/* } */

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
  gtk_widget_set_name (top.prompt, "prompt");
  gtk_box_pack_start (GTK_BOX (hbox), top.prompt, FALSE, FALSE, 0);

  top.entry = gtk_entry_new ();
  gtk_box_pack_start (GTK_BOX (hbox), top.entry, TRUE, TRUE, 0);
  g_signal_connect (top.entry, "key-press-event", G_CALLBACK (key_press_event_cb), &pop);
  /* g_signal_connect (top.entry, "changed", G_CALLBACK (changed_cb), NULL); */

  completion (&pop, &opt);

  set_style (&top, &opt);

  /* close popup window on lost focus */
  gtk_widget_add_events(top.entry, GDK_FOCUS_CHANGE_MASK);

  g_signal_connect (G_OBJECT(top.entry), "focus-out-event",
                    G_CALLBACK(focus_out_event_cb), &pop);
  g_signal_connect_swapped (G_OBJECT(top.entry), "focus-in-event",
                           G_CALLBACK(gtk_widget_show_all),pop.window);

  read_input (&pop);

  gtk_window_set_transient_for (GTK_WINDOW (pop.window), GTK_WINDOW (top.window));

  if (opt.l)
    {
      /* g_vertical (); */
    }
  else
    {
      g_horizontal (&top, &pop, &opt);
    }
  gtk_widget_set_can_focus (pop.flow, TRUE);

  gtk_main ();

  return 0;
}
