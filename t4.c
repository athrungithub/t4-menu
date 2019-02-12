#include <sys/stat.h>
#include <stdlib.h>
#include <glib/gprintf.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>     /* for gtk_plug */

#define PROMPT "Launch:\t"
#define COMPLETION_TIMEOUT 100

typedef struct
{
  guint x;
  guint y;
  guint W;
  char *w; // connect to window id (X11)
  gboolean l;
  gboolean b;
  char *p; // prompt string
  char *f; // font
  char *b_color; // normal color
  char *color; // color
  char *prompt_color;
  char *prompt_back_color;
  gboolean n;
  gboolean v;
}_Option;

_Option *opt;

struct Top
{
  GtkWidget *window;
  GtkWidget *entry;
  GtkWidget *prompt;
  char *env_sway;
};
struct Top *top;

typedef struct
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
  GtkAdjustment *adj;
}_Popup;

_Popup *popup;

struct
{
  GdkMonitor *mon;
  GdkRectangle area;
  const gchar *name;
} monitor;

GdkRectangle rec_win;
GdkRectangle rec_popup;

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

void
ver_page_next (void)
{
  GtkAdjustment *adj;
  GtkFlowBoxChild *child;

  adj = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (popup->scrolled));

  double value = gtk_adjustment_get_value (adj);
  double page_size = gtk_adjustment_get_page_size (adj);
  double upper = gtk_adjustment_get_upper (adj);
  gint tmp = (gint) (upper - (value + page_size));

  if (tmp <= 0)
    value = upper - 5;
  else
    value = value + page_size - 10;

  child = gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow),
                                         1,
                                         (gint) value);
  gtk_adjustment_set_value (adj, value);
  gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (popup->flow), adj);
  g_signal_emit_by_name (G_OBJECT (child), "activate");

  return;
}

void
ver_page_back (void)
{
  GtkAdjustment *adj;
  GtkFlowBoxChild *child;

  adj = gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (popup->scrolled));

  double value = gtk_adjustment_get_value (adj);
  double page_size = gtk_adjustment_get_page_size (adj);
  gint tmp = (gint) (value - page_size);

  if (tmp < 0)
    value = 0;
  else
    value = value - page_size + 24;

  child = gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow),
                                         1,
                                         (gint) value);
  gtk_adjustment_set_value (adj, value);
  gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (popup->flow), adj);
  g_signal_emit_by_name (G_OBJECT (child), "activate");

  return;
}

void
hor_page_back (GtkAdjustment *a, gpointer data)
{
  GtkAdjustment *adj = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (popup->scrolled));
  GtkFlowBoxChild *child;
  gint width;

  if (!gtk_widget_is_visible (popup->flow))
    return;

  double value = gtk_adjustment_get_value (adj) - gtk_adjustment_get_page_increment (adj);
  if (value < 0)
    value = 0;
  child = gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow),
                                         (gint)value,
                                         rec_popup.height - 3);


  g_signal_emit_by_name (G_OBJECT (child), "activate");
  /* reload new value */
  adj = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (popup->scrolled));

  gtk_widget_get_preferred_width (GTK_WIDGET (child), NULL, &width);
  value = gtk_adjustment_get_value (adj) - gtk_adjustment_get_page_size (adj) + width;
  gtk_adjustment_set_value (adj, value);
  gtk_flow_box_set_hadjustment (GTK_FLOW_BOX (popup->flow), adj);

  return;
}

void
hor_page_next (GtkAdjustment *a, gpointer data)
{
  GtkAdjustment *adj = gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (popup->scrolled));
  GtkFlowBoxChild *child;

  if (!gtk_widget_is_visible (popup->flow))
    return;

  double value = gtk_adjustment_get_value (adj);
  double page_size =  gtk_adjustment_get_page_size (adj);
  double upper = gtk_adjustment_get_upper (adj);
  gint tmp = (gint) (upper - (value + page_size));

  if (tmp <= 0)
    {
      value = upper - 5;
    }
  else
    {
      value = value + page_size;
    }

  child = gtk_flow_box_get_child_at_pos (GTK_FLOW_BOX (popup->flow),
                                         (gint) value,
                                         rec_popup.height - 3);

  gtk_adjustment_set_value (adj, value);
  gtk_flow_box_set_hadjustment (GTK_FLOW_BOX (popup->flow), adj);
  g_signal_emit_by_name (G_OBJECT (child), "activate");
  return;
}

static void
monitor_set (GtkWidget *w)
{
  /*TODO: set monitor */
  GdkDisplay *display;
  GdkWindow *gdk;
  GdkWindow *window;

  if (opt->w)
    {
      display = gdk_display_get_default ();
      gdk = gdk_x11_window_foreign_new_for_display (display, strtol(opt->w,NULL, 0));
      gdk_window_get_root_origin (gdk, &monitor.area.x, &monitor.area.y);
      monitor.area.width = gdk_window_get_width (gdk);
      monitor.area.height = gdk_window_get_height (gdk);
      gdk_window_set_transient_for (gtk_widget_get_window (top->window),
                                    gdk);
    }
  else
    {
      display = gtk_widget_get_display (w);
      window = gtk_widget_get_window (w);
      monitor.mon = gdk_display_get_monitor_at_window (display, window);
      gdk_monitor_get_geometry (monitor.mon, &monitor.area);
    }
  monitor.name =  gdk_display_get_name (display);
  return;
}

void
size_win (void)
{
  GtkRequisition req;

  gtk_widget_get_preferred_size (top->window, &req, NULL);
  rec_win.width = req.width;
  rec_win.height = req.height;

  return;
}

void
g_horizontal (void)
{
  gtk_widget_show_all (top->window);
  gtk_widget_show_all (popup->window);
  monitor_set (top->window);
  size_win ();

  rec_win.width++;

  if ((opt->W >= (2 * rec_win.width)) && (opt->W < monitor.area.width))
    {
      if (opt->x > monitor.area.width)
        {
          rec_win.x = monitor.area.width - opt->W;
          rec_popup.x = rec_win.x + rec_win.width;
          rec_popup.width = monitor.area.width - rec_popup.x;
        }
      else if (!opt->x)
        {
          rec_win.x = 0;
          rec_popup.x = rec_win.x + rec_win.width;
          rec_popup.width = opt->W - rec_win.width;
        }
      else
        {
          rec_win.x = opt->x > monitor.area.width - opt->W ? monitor.area.width - opt->W : opt->x;
          rec_popup.x = rec_win.x + rec_win.width;
          rec_popup.width = opt->W - rec_win.width;
        }
    }
  else if (!opt->W)
    {
      if ((!opt->x) || (opt->x > monitor.area.width))
        {
          /* width = monitor.area.width; */
          rec_win.x = 0;
          rec_popup.x = rec_win.x + rec_win.width;
          rec_popup.width = monitor.area.width - rec_win.width;
        }
      else
        {
          /* width = monitor.area.width - opt->x; */
          rec_win.x = opt->x;
          rec_popup.x = rec_win.x + rec_win.width;
          rec_popup.width = monitor.area.width - rec_win.width - opt->x;
        }
    }
  else
    {
      rec_win.x = 0;
      rec_popup.x = rec_win.x + rec_win.width;
      rec_popup.width = monitor.area.width - rec_win.width;
    }



  rec_popup.height = rec_win.height;

  if (opt->b)
    {
      rec_win.y = monitor.area.height - rec_win.height;
      rec_popup.y = rec_win.y;
    }
  else
    {
      rec_win.y = !opt->y ? 0 : opt->y < (monitor.area.height - rec_win.height) ?
        opt->y : (monitor.area.height - rec_win.height);
      rec_popup.y = rec_win.y;
    }

  if (opt->w)
    {
      rec_win.x += monitor.area.x;
      rec_popup.x += monitor.area.x;
      rec_win.y += monitor.area.y;
      rec_popup.y += monitor.area.y;
    }

  gtk_widget_set_size_request (top->window, rec_win.width, -1);
  gtk_window_move (GTK_WINDOW (top->window), rec_win.x, rec_win.y);

  gtk_widget_set_size_request (popup->window, rec_popup.width, rec_popup.height);
  gtk_window_move (GTK_WINDOW (popup->window), rec_popup.x, rec_popup.y);

  return;
}

void
g_popup_resize (void)
{
  GList *list;
  /* gint count; */
  gint child_height, tmp, tmp_lim;

  gtk_widget_show_all (popup->window);
  gtk_widget_show_all (top->window);

  rec_popup.width = rec_win.width;
  rec_popup.x = rec_win.x;
  list = gtk_container_get_children (GTK_CONTAINER (popup->flow));
  /* count = g_list_length (list);  total de child */
  /* g_message ("items: %i\n", count); */

  gtk_widget_get_preferred_height (GTK_WIDGET (list->data), NULL, &child_height);

  if (!popup->count_child)
    {
      gtk_widget_hide (popup->window);
      return;
    }

  tmp= popup->count_child * child_height;

  tmp_lim = opt->l * rec_win.height;
  rec_popup.height = MIN(tmp, tmp_lim);

  if (opt->b)
    {
      if (rec_popup.height > rec_win.y)
        rec_popup.height = rec_win.y;
      rec_popup.y = rec_win.y - rec_popup.height <= 0 ? 0 : rec_win.y - rec_popup.height;
      if (strstr (monitor.name, "wayland"))
        rec_popup.y = -(rec_popup.height + rec_win.y + rec_win.height- monitor.area.height);
    }
  else
    {
      if (rec_popup.height >= (monitor.area.height - (rec_win.y - monitor.area.y) + rec_win.height))
        rec_popup.height = monitor.area.height - (rec_win.y - monitor.area.y) - rec_win.height;
      rec_popup.y = rec_win.y + rec_win.height;
    }

  if (popup->count_child < 3)
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (popup->scrolled),
                                    GTK_POLICY_NEVER, GTK_POLICY_NEVER);
  else
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (popup->scrolled),
                                    GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);

  gtk_widget_set_size_request (popup->window, rec_popup.width, rec_popup.height);
  if (strstr (monitor.name, "wayland"))
    {
      gtk_widget_hide (popup->window);
      gtk_window_move (GTK_WINDOW (popup->window), rec_popup.x, rec_popup.y);
      gtk_widget_show (popup->window);
    }
  else
    {
      gtk_window_move (GTK_WINDOW (popup->window), rec_popup.x, rec_popup.y);
      gtk_widget_show (popup->window);
    }

  return;
}

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

static gboolean
parse_opt (int *argc, char ***argv)
{
  GError *error = NULL;
  GOptionContext *context;

  GOptionEntry entries[] =
    {
        { "xposition", 'x', 0, G_OPTION_ARG_INT, &(opt->x),
          "x <int>: If x > width screen, stack to rigth screen", NULL },
        { "yposition:", 'y', 0, G_OPTION_ARG_INT, &(opt->y),
          "y <int>: If y > height stack to bottom screen", NULL
        },
        { "width", 'W', 0, G_OPTION_ARG_INT, &(opt->W),
          "W <int>: Vertical mode. W > width screen -> screen width", NULL
        },
        { "lines", 'l', 0, G_OPTION_ARG_INT, &(opt->l),
          "l <int>: list items vertically", NULL
        },
        { "bottom", 'b', 0, G_OPTION_ARG_NONE, &(opt->b),
          "bottom screen", NULL
        },
        { "font", 'f', 0, G_OPTION_ARG_STRING, &(opt->f),
          "font. ex: \"10px [styles] Sans\"", NULL,
        },
        { "normal-color", 0, 0, G_OPTION_ARG_STRING, &(opt->color),
          "normal foreground color of opt", NULL,
        },
        { "normal-background", 0, 0, G_OPTION_ARG_STRING, &(opt->b_color),
          "normal background color of opt", NULL,
        },
        { "prompt", 'p', 0, G_OPTION_ARG_STRING, &(opt->p),
          "prompt. Define the string to show", NULL,
        },
        { "prompt-color", 0, 0, G_OPTION_ARG_STRING, &(opt->prompt_color),
          "prompt color", NULL,
        },
        { "prompt-background", 0, 0, G_OPTION_ARG_STRING, &(opt->prompt_back_color),
          "prompt background color", NULL,
        },
        { "windowid", 'w', 0, G_OPTION_ARG_STRING, &(opt->w),
          "X11: embed into windowid.", NULL,
        },
        { "focus", 'n', 0, G_OPTION_ARG_NONE, &(opt->n),
          "Persistent on lost focus", NULL,
        },
        { "version", 'v', 0, G_OPTION_ARG_NONE, &(opt->v),
          "version", NULL
        },
    };

  context = g_option_context_new (NULL);
  g_option_context_add_main_entries (context, entries, NULL);
  g_option_context_set_ignore_unknown_options (context, TRUE);
  g_option_context_set_description (context, "Geometry: \n"
                                    "\tx > width screen: stack to right\n\
                                    \tW > monitor width : width screen\n");

  if (!g_option_context_parse (context, argc, argv, &error))
    {
      g_print ("option parsing failed: %s\n", error->message);
    }

  if (opt->v)
    {
      fprintf (stdout, "%s - version: %s\nbuild date: %s\n", NAME, VERSION,  BUILDDATE);
      fprintf (stdout, "%s\n","Copyright © 2018 Alberto Higashikadoguchi <athrun@arnet.com.ar>");
      exit (EXIT_SUCCESS);
    }

  g_option_context_free (context);
  return TRUE;
}

void
read_input (void)
{
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
set_style (GtkWidget *w)
{
  auto GtkCssProvider *provider;
  GdkScreen *screen;

  provider = gtk_css_provider_new ();
  GString *style = g_string_new(NULL);
  if (opt->f)
    {
      g_string_append_printf (style, "* {font: %s;}", opt->f);
    }
  if (opt->color)
    {
      g_string_append_printf (style, "flowbox{color: %s;}", opt->color);
    }
  if (opt->b_color)
    {
      g_string_append_printf (style, "flowbox{background-color: %s;}", opt->b_color);
      /* g_string_append_printf (style, "#popup * {background-color: %s;}", opt->b_color); */
    }
  if (opt->prompt_color)
    {
      g_string_append_printf (style, "#Prompt{color: %s;}", opt->prompt_color);
    }
  if (opt->prompt_back_color)
    {
      g_string_append_printf (style, "#Prompt{background-color: %s;}", opt->prompt_back_color);
    }

  g_string_append_printf(style, "entry{min-height: %ipx;\nborder-radius: %ipx;}", 22, 0);
  g_string_append_printf(style, "scrollbar {-GtkScrollbar-has-backward-stepper: %i;\n\
                         -GtkScrollbar-has-forward-stepper: %i;\n }", 1, 1);

gtk_css_provider_load_from_data (provider,
                                 style->str,
                                 -1,
                                 NULL);

screen = gtk_window_get_screen (GTK_WINDOW (top->window));
gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
                                           GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

g_string_free (style, TRUE);
return;
}

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

void
completion (void)
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
      gtk_widget_set_name (popup->flow, "vertical");

      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (popup->scrolled),
                                      GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);

    }
  gtk_flow_box_set_min_children_per_line (GTK_FLOW_BOX(popup->flow), 1);
  gtk_flow_box_set_max_children_per_line (GTK_FLOW_BOX(popup->flow), 1);
  gtk_flow_box_set_filter_func (GTK_FLOW_BOX (popup->flow), filter, NULL, NULL);
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
  gtk_window_set_type_hint (GTK_WINDOW (popup->window), GDK_WINDOW_TYPE_HINT_COMBO);

  /* transparency */
  gtk_widget_set_app_paintable(popup->window, TRUE);
  g_signal_connect(G_OBJECT(popup->window), "screen-changed", G_CALLBACK(screen_changed), NULL);
  screen_changed (popup->window, NULL, NULL);

  /* add signal */
  gtk_container_add (GTK_CONTAINER (popup->scrolled), popup->flow);
  gtk_container_add (GTK_CONTAINER (popup->window), popup->scrolled);

  return;
}

static void
output (GtkWidget *fbox, GtkWidget *child, gpointer data)
{
  GtkWidget *lab;
  const gchar *st;
  GList *l;

  if (popup->count_child)
    {
      l = gtk_flow_box_get_selected_children (GTK_FLOW_BOX (popup->flow));
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
      output (w, NULL, NULL);
      return TRUE;
    }
  else if (SHIFT(Return))
    {
      /*confirm input, Print the input text to stdout en exit, returning success */
      GList *l;
      GtkLabel *lab;
      gchar *s;

      if (!popup->count_child)
        return TRUE;
      s = g_malloc (BUFSIZ);
      l = gtk_flow_box_get_selected_children (GTK_FLOW_BOX (popup->flow));
      lab = GTK_LABEL(gtk_bin_get_child(GTK_BIN(l->data)));
      g_sprintf (s, "%s ", gtk_label_get_text (lab));
      gtk_entry_set_text (GTK_ENTRY (top->entry), s);
      gtk_editable_set_position (GTK_EDITABLE (top->entry), -1);
      g_free (s);

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
      if (!opt->l)
        hor_page_next (NULL, NULL);
      else
        {
          ver_page_next ();
        }
      return TRUE;
    }
  else if (MOD1(k) || MOD1(p) || CONTROL(Up))
    {
      if (!opt->l)
        hor_page_back (NULL, NULL);
      else
        ver_page_back ();
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

static void
changed_cb (GtkWidget *widget, gpointer data)
{
  gboolean b;

  if (popup->completion_timeout)
    {
      g_source_remove (popup->completion_timeout);
      popup->completion_timeout = 0;
    }
  gtk_flow_box_unselect_all (GTK_FLOW_BOX (popup->flow));

  popup->child_first = NULL;
  popup->count_child = 0;

  gchar *tmp;
  GtkFlowBoxChild *b_child;

  b_child = gtk_flow_box_get_child_at_index (GTK_FLOW_BOX (popup->flow), 0);
  if (!b_child)
    return ;
  g_free (popup->key);

  tmp = g_utf8_normalize (gtk_entry_get_text (GTK_ENTRY (top->entry)),
                          -1, G_NORMALIZE_ALL);
  popup->key = g_utf8_casefold (tmp, -1);
  g_free (tmp);

  gtk_flow_box_invalidate_filter (GTK_FLOW_BOX (popup->flow));

  if (opt->l )
    {
      g_popup_resize ();
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
  GtkWidget *pop = (GtkWidget *) data;
  if (opt->n)
    gtk_widget_hide (pop);
  else
    gtk_main_quit ();
  return GDK_EVENT_PROPAGATE;
}

int
main (int argc, char *argv[])
{
  top = g_new0 (struct Top, 1);
  opt = g_new0 (_Option, 1);
  popup = g_new0 (_Popup, 1);
  popup->count_child= 0;
  GtkWidget *hbox;

  gtk_init (&argc, &argv);
  parse_opt (&argc, &argv);

  top->window= gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_type_hint (GTK_WINDOW(top->window), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_decorated(GTK_WINDOW(top->window), FALSE);
  gtk_window_set_resizable (GTK_WINDOW (top->window), FALSE);
  gtk_window_set_skip_pager_hint (GTK_WINDOW (top->window), FALSE);
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW (top->window), FALSE);
  gtk_widget_set_app_paintable(top->window, TRUE);
  g_signal_connect (top->window, "destroy",
                    G_CALLBACK (gtk_main_quit), &top->window);
  g_signal_connect(G_OBJECT(top->window), "screen-changed", G_CALLBACK(screen_changed), NULL);
  screen_changed(top->window, NULL, NULL);

  /* for sway */
  top->env_sway = getenv ("SWAYSOCK");

  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add (GTK_CONTAINER (top->window), hbox);

  top->prompt = gtk_label_new (opt->p ? opt->p : PROMPT);
  gtk_widget_set_name (top->prompt, "Prompt");
  gtk_box_pack_start (GTK_BOX (hbox), top->prompt, FALSE, FALSE, 0);

  top->entry = gtk_entry_new ();
  gtk_box_pack_start (GTK_BOX (hbox), top->entry, TRUE, TRUE, 0);
  g_signal_connect (top->entry, "key-press-event", G_CALLBACK (key_press_event_cb), NULL);
  g_signal_connect (top->entry, "changed", G_CALLBACK (changed_cb), NULL);

  completion ();

  set_style (top->entry);

  /* close popup window on lost focus */
  gtk_widget_add_events(top->entry, GDK_FOCUS_CHANGE_MASK);

  g_signal_connect (G_OBJECT(top->entry), "focus-out-event",
                    G_CALLBACK(focus_out_event_cb), popup->window);
  g_signal_connect_swapped (G_OBJECT(top->entry), "focus-in-event",
                           G_CALLBACK(gtk_widget_show_all),popup->window);

  read_input ();

  gtk_window_set_transient_for (GTK_WINDOW (popup->window), GTK_WINDOW (top->window));

  if (opt->l)
    {
      g_vertical ();
    }
  else
    {
      g_horizontal ();
    }
  gtk_widget_set_can_focus (popup->flow, TRUE);

  /* sway: dispara el event "focus-in-event"
   * and show popup-window on starup
   */
  if (top->env_sway)
      gtk_widget_hide (popup->window);

  gtk_main ();

  g_free (popup);
  g_free (opt);
  g_free (top);
  return 0;
}
