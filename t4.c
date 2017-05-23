#define _GNU_SOURCE       /* For strcasestr */
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtkx.h>     /* for gtk_plug */
#include <gtk/gtk.h>

#define WIDTH_SCREEN6(x) (x / 6)        /* default width height in line mode */
#define HEIGHT_SCREEN23(x) (2 * x / 3)
#define PROMPT "Launch: "

struct _Options
{
  guint x;
  guint y;
  guint W;
  guint H;
  char *w;
  gboolean l;
  gboolean b;
  char *p;
  gboolean v;
};

typedef struct _Options Options;
Options *options;

gint childindex;

gboolean
file_exists (const char *filename)
{
  struct stat statbuf;

  return stat (filename, &statbuf) == 0;
}

static GtkWidget *
make_label(const gchar *str)
{
  GtkWidget *lab;

  lab = gtk_label_new(str);
  gtk_widget_set_name (lab, "Item");
  gtk_widget_set_valign(lab, GTK_ALIGN_START);

  if (options->l)
  {
    gtk_label_set_xalign (GTK_LABEL(lab), 0);
    gtk_label_set_line_wrap(GTK_LABEL(lab), FALSE);
    gtk_label_set_ellipsize (GTK_LABEL(lab), PANGO_ELLIPSIZE_END);
  }
  else
  {
    gtk_widget_set_halign(lab, GTK_ALIGN_START);
  }
  gtk_widget_show(lab);

  return lab;
}

static int
read_input(GtkWidget *flow)
{
  GtkWidget *label;
  gint count = 0;
  gchar buf[BUFSIZ];

  for (; fgets(buf, BUFSIZ, stdin); count++)
  {
    if (buf[strlen (buf) - 1] == '\n')
      buf[strlen(buf) - 1] = '\0';
    label = make_label(buf);
    gtk_container_add(GTK_CONTAINER(flow), label);
    count++;
  }
  return count;
}

static gboolean
parse_opt (int *argc, char ***argv)
{
  GError *error = NULL;
  GOptionContext *context;

  GOptionEntry entries[] =
  {
    { "xposition",
      'x',
      0,
      G_OPTION_ARG_INT,
      &(options->x),
      "x position. If x > width screen, stack to rigth screen",
      NULL
    },
    { "yposition",
      'y',
      0,
      G_OPTION_ARG_INT,
      &(options->y),
      "y position. If y > height stack to bottom screen",
      NULL
    },
    { "width",
      'W',
      0,
      G_OPTION_ARG_INT,
      &(options->W),
      "width. Vertical mode, default 1/6 screen. W > width screen -> screen width",
      NULL
    },
    { "height",
      'H',
      0,
      G_OPTION_ARG_INT,
      &(options->H),
      "height. Vertical mode, default 2/3 screen. H > height screen -> screen height",
      NULL
    },
    { "line",
      'l',
      0,
      G_OPTION_ARG_NONE,
      &(options->l),
      "vertical mode: list items vertically",
      NULL
    },
    { "bottom",
      'b',
      0,
      G_OPTION_ARG_NONE,
      &(options->b),
      "bottom screen",
      NULL
    },
    {
      "prompt",
      'p',
      0,
      G_OPTION_ARG_STRING,
      &(options->p),
      "prompt. Define the prompt displayed to left of input field",
      NULL,
    },
    { "windowid",
      'w',
      0,
      G_OPTION_ARG_STRING,
      &(options->w),
      "embed into windowid.",
      NULL
    },
    { "version",
      'v',
      0,
      G_OPTION_ARG_NONE,
      &(options->v),
      "version",
      NULL
    },
  };

  context = g_option_context_new (NULL);
  g_option_context_add_main_entries (context, entries, NULL);
  g_option_context_set_ignore_unknown_options (context, TRUE);
  g_option_context_set_description (context, "Geometry: \n\tx > width screen: stack to right\n\
\tW > width screen: width screen\n\
\tH > height screen: height screen\n\
\nFont & Color:\nCopy PREFIX/share/t4/t4.css to CONFIGDIR/t4.css and edit.\n");

  if (!g_option_context_parse (context, argc, argv, &error))
  {
    g_print ("option parsing failed: %s\n", error->message);
  }

  if (options->v)
  {
    fprintf (stdout, "%s - version: %s\nbuild date: %s\n", NAME, VERSION,  BUILDDATE);
    fprintf (stdout, "%s\n","Copyright © 2017 Alberto Higashikadoguchi <athrun@arnet.com.ar>");
    /*fprintf (stdout, "%s\n", "Licence GPLv3+");*/
    exit (EXIT_SUCCESS);
  }

  g_option_context_free (context);
  return TRUE;
}

static GtkWidget *
scrolled_mk (void)
{
  GtkScrolledWindow *widget;

  widget = GTK_SCROLLED_WINDOW(gtk_scrolled_window_new (NULL, NULL));
  if (options->l)
  {
    gtk_scrolled_window_set_policy (widget, GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    gtk_widget_set_vexpand (GTK_WIDGET(widget), TRUE);
  }
  else
  {
    gtk_scrolled_window_set_policy (widget, GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
    gtk_widget_set_hexpand (GTK_WIDGET(widget), TRUE);
  }
  gtk_widget_show (GTK_WIDGET(widget));
  return GTK_WIDGET(widget);
}

/*
 *la orientacion se podria manejar con gtk_flow_box_set_(min-max)_children_per_line
 *gtk esta flojo de papeles con con la señal move-cursor {page-horizontal}
 *utilizamos este recurso para tener scroll-page horizontal
 */

static GtkWidget *
flowbox_mk (void)
{
  GtkWidget *widget;

  widget = gtk_flow_box_new ();
  if (options->l)
  {
    gtk_orientable_set_orientation (GTK_ORIENTABLE(widget), GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_valign (widget, GTK_ALIGN_START);
    gtk_widget_set_name (widget, "vertical");
  }
  else {
    gtk_orientable_set_orientation (GTK_ORIENTABLE(widget), GTK_ORIENTATION_VERTICAL);
    gtk_widget_set_halign (widget, GTK_ALIGN_START);
    gtk_widget_set_name (widget, "horizontal");
  }
  gtk_widget_show (widget);
  gtk_flow_box_set_selection_mode (GTK_FLOW_BOX(widget), GTK_SELECTION_BROWSE);
  return widget;
}

static gint
get_height (GtkWidget *w)
{
  gint he, hs, min, nat;
  GtkWidget *tmp;
  if (options->b)
  {
    tmp = gtk_bin_get_child (GTK_BIN(gtk_grid_get_child_at (GTK_GRID(gtk_bin_get_child (GTK_BIN(w))), 0, 0)));
    gtk_widget_get_preferred_height ( tmp, &min, &nat);
    hs = nat;
    tmp = gtk_grid_get_child_at (GTK_GRID(gtk_bin_get_child (GTK_BIN(w))), 0, 1);
    gtk_widget_get_preferred_height ( tmp, &min, &nat);
    he = nat;
  }
  else
  {
    tmp = gtk_grid_get_child_at (GTK_GRID(gtk_bin_get_child (GTK_BIN(w))), 0, 0);
    gtk_widget_get_preferred_height ( tmp, &min, &nat);
    he = nat;
    tmp = gtk_bin_get_child (GTK_BIN(gtk_grid_get_child_at (GTK_GRID(gtk_bin_get_child (GTK_BIN(w))), 0, 1)));
    gtk_widget_get_preferred_height ( tmp, &min, &nat);
    hs = nat;
  }
  return he + hs;
}

static void
geometry_vertical (GtkWidget *w, GdkRectangle *rect)
{
  gint h;
  GdkRectangle t;

  /* calcular de altura del widget */
  h = get_height (w);

  t.width = !options->W ? WIDTH_SCREEN6(rect->width) : (options->W < rect->width) ?
            options->W : WIDTH_SCREEN6(rect->width);
  t.x = !options->x ? 0 : options->x <= (rect->width - t.width) ? options->x : (rect->width - t.width);
  rect->width = t.width;
  rect->x = t.x;

  t.height = h < rect->height? h : rect->height;
  if (options->H)
    t.height = t.height < options->H ? t.height : options->H;
  else
    t.height = t.height < HEIGHT_SCREEN23(rect->height) ? t.height : HEIGHT_SCREEN23(rect->height);

  if (options->b)
  {
    t.y = (rect->height - t.height);
    rect->y = t.y;
  }
  else
  {
    t.y = !options->y ? 0 : options->y < (rect->height - 100) ? options->y : 0;
    rect->y = t.y;
    t.height = t.y + t.height > rect->height ? rect->height - t.y : t.height;
  }

  rect->height = t.height;
  return;
}

static void
geometry_horizontal (GtkWidget *w, GdkRectangle *rect)
{
  gint h, nat, min;
  GtkWidget *tmp;
  GdkRectangle t;
  /* calculo de altura del widget */
  tmp = gtk_grid_get_child_at (GTK_GRID(gtk_bin_get_child (GTK_BIN(w))),
                               2, 0);
  gtk_widget_get_preferred_height (tmp, &min, &nat);
  h = !nat ? 12 : nat;

  t.width = !options->W ? rect->width : options->W < rect->width ?
                                    options->W : rect->width;
  t.x = !options->x ? 0 : options->x < (rect->width - t.width) ?
                      options->x : (rect->width - t.width);

  rect->width = t.width;
  rect->x = t.x;

  if (options->b)
  {
     rect->y = rect->height - h;
  }
  else
  {
    t.y = !options->y ? 0 : options->y < (rect->height - h) ?
                        options->y : (rect->height - h);
    rect->y = t.y;
  }
  rect->height = h;
  return;
}

void
geo_mk (GtkWidget *w)
{
#if 0
  for select monitor
  gint num_monitors = gdk_display_get_n_monitors (display);
#endif
  GdkRectangle rect;
  GtkWidget *scr;
  GdkGeometry hints;
  GdkDisplay *display;
  GdkRectangle mon_rect;
  GdkMonitor *monitor;
  GdkWindow *gdk;

  if (options->w)
  {
    display = gdk_display_get_default ();
    gdk = gdk_x11_window_foreign_new_for_display (display, strtol(options->w,NULL, 0));
    gdk_window_get_root_origin (gdk, &mon_rect.x, &mon_rect.y);
    mon_rect.width = gdk_window_get_width (gdk);
    mon_rect.height = gdk_window_get_height (gdk);
  }
  else
  {
    display = gdk_display_get_default ();
    monitor = gdk_display_get_monitor (display, 0);
    gdk_monitor_get_workarea (monitor, &mon_rect);
  }

  rect = mon_rect;

  if (options->l)
  {
    geometry_vertical (w, &rect);
    if (options->b)
      scr = gtk_grid_get_child_at (GTK_GRID(gtk_bin_get_child (GTK_BIN(w))), 0, 0);
    else
      scr = gtk_grid_get_child_at (GTK_GRID(gtk_bin_get_child (GTK_BIN(w))), 0, 1);

    /* desabilitar el scroll si hay pocas opciones */
    if (rect.height <= 78)
      gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scr), GTK_POLICY_NEVER, GTK_POLICY_NEVER);
    else
      gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scr), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  }
  else
  {
    geometry_horizontal (w, &rect);
  }
  if (options->w)
  {
    rect.x = rect.x + mon_rect.x;
    rect.y = rect.y + mon_rect.y;
  }

  hints.min_height = rect.height;
  hints.min_width = rect.width;
  hints.max_height = rect.height;
  hints.max_width = rect.width;
  gtk_window_set_geometry_hints (GTK_WINDOW(w), NULL, &hints, GDK_HINT_POS | GDK_HINT_MAX_SIZE |
                                 GDK_HINT_MIN_SIZE);
  gtk_window_resize (GTK_WINDOW(w), rect.width, rect.height);
  gtk_window_move (GTK_WINDOW(w), rect.x, rect.y);
  return;
}

static void
provider_add (GtkWidget *w)
{
  GtkCssProvider *provider;
  GdkScreen *screen;
  /*GdkDisplay *display;*/
  GError *e = NULL;
  gboolean l;
  provider = gtk_css_provider_new();
  char *file;
  char *h_config = g_build_filename(g_get_user_config_dir (), "t4", "t4.css", NULL);

  /*
   * Check to see if we are being run from the correct directory.
   */
  file = g_strdup_printf ("%s/%s/%s", DATAPREFIX,"t4", "t4.css");
  l = gtk_css_provider_load_from_path (provider, file, &e);
  e = NULL;
  if (file_exists(h_config))
    l = gtk_css_provider_load_from_path (provider, h_config, &e);

  if (!l)
    {
      fprintf (stderr, ("Failed to init gtk_css_provider_load_from_path: %s\n"), e->message);
      g_error_free (e);
      e = NULL;
   }

  screen = gtk_window_get_screen (GTK_WINDOW(w));
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_object_unref (provider);
}

gboolean
filter_func (GtkFlowBoxChild *child, gpointer data)
{
  GtkLabel *lab;
  const gchar *str, *filter;
  GtkLabel *dat = (GtkLabel*) data;

  filter = gtk_label_get_text(dat);
  lab = GTK_LABEL(gtk_bin_get_child (GTK_BIN(child)));
  str = gtk_label_get_text (lab);
  /*g_message ("label %s\n Filter: %s\n", str, filter);*/
  if (strcasestr (str, filter))
  {
    if (childindex == -1)
    {
      childindex = gtk_flow_box_child_get_index (child);
      /*g_message ("filter index: %i\n", childindex);*/
      gtk_flow_box_select_child (GTK_FLOW_BOX(gtk_widget_get_parent (GTK_WIDGET(child))), child);
      g_signal_emit_by_name (G_OBJECT(child), "activate");
    }
    return TRUE;
  }
  else
    return FALSE;
}

static void
output (GtkWidget *box, GtkWidget *child, gpointer data)
{
  GtkWidget *lab;
  const gchar *st;

  lab = GTK_WIDGET(gtk_bin_get_child(GTK_BIN(child)));
  st = gtk_label_get_text(GTK_LABEL(lab));
  if (childindex < 0)
  {
    st = gtk_label_get_text ((GtkLabel *)data);
  }
  g_print ("%s\n", st);
  gtk_main_quit();
}

/* callback */
static gboolean
flowbox_key_press_event_cb (GtkFlowBox *fb, GdkEvent *ev, GtkWidget *entry)
{
  guint key = GDK_KEY_VoidSymbol;
  GdkModifierType state;
  GtkWidget *top;

  gdk_event_get_keyval (ev, &key);
  gdk_event_get_state (ev, &state);
  top = gtk_widget_get_toplevel (GTK_WIDGET(fb));
  gtk_flow_box_unselect_all (fb);

#define KEY(x)      (key == GDK_KEY_ ## x)
#define CONTROL(x)  (KEY(x) && state & GDK_CONTROL_MASK)
#define SHIFT(x)    (KEY(x) && state & GDK_SHIFT_MASK)
#define MOD1(x)     (KEY(x) && state & GDK_MOD1_MASK)

  if (KEY(Escape) || (KEY(c) && CONTROL(c)))
  {
    gtk_main_quit ();
    return TRUE;
  }
  else if (KEY(Return) || (KEY(m) && CONTROL(m)))
  {
    GList *l;

    l = gtk_flow_box_get_selected_children (fb);
    output (GTK_WIDGET(fb), l->data, entry);
    return TRUE;
  }
  else if (CONTROL(n) || CONTROL(j))
  {
    gboolean b;
    g_signal_emit_by_name (fb, "move-cursor", GTK_MOVEMENT_VISUAL_POSITIONS, 1, &b);
    g_signal_emit_by_name (fb, "toggle-cursor-child");
    return TRUE;
  }
  else if (CONTROL(p) || CONTROL(k) || CONTROL(Tab))
  {
    gboolean b;
    g_signal_emit_by_name (fb, "move-cursor", GTK_MOVEMENT_VISUAL_POSITIONS, -1, &b);
    g_signal_emit_by_name (fb, "toggle-cursor-child");
    return TRUE;
  }
  else if (CONTROL(f) || CONTROL(Right))
  {
    gboolean b;
    g_signal_emit_by_name (fb, "move-cursor", GTK_MOVEMENT_PAGES, 1, &b);
    g_signal_emit_by_name (fb, "toggle-cursor-child");
    return TRUE;
  }
  else if (CONTROL(b) || CONTROL(Left))
  {
    gboolean b;
    g_signal_emit_by_name (fb, "move-cursor", GTK_MOVEMENT_PAGES, -1, &b);
    g_signal_emit_by_name (fb, "toggle-cursor-child");
    return TRUE;
  }
  else if (KEY(BackSpace) || CONTROL(h))
  {
    const char *get;
    gchar *str;

    get = gtk_label_get_text (GTK_LABEL(entry));
    if (get)
    {
      str = g_strdup (get);
      gint i = strlen (str);
      str[--i] = 0;
      gtk_label_set_text (GTK_LABEL(entry), str);
      g_free (str);
      childindex = -1;
      gtk_flow_box_set_filter_func (fb, filter_func, entry, NULL);
    }
    else
    {
      gtk_flow_box_invalidate_filter (fb);
      gtk_flow_box_select_child (fb, gtk_flow_box_get_child_at_index (fb, 0));
    }
    if (options->l)
    {
      geo_mk (top);
    }
    gtk_widget_grab_focus (GTK_WIDGET(fb));
    return TRUE;

  }
  else if (state != GDK_CONTROL_MASK && state != GDK_MOD1_MASK &&
          (GDK_KEY_exclam < key && key <  GDK_KEY_exclamdown))
  {
      const char *get;
      char *str;

      get = gtk_label_get_text (GTK_LABEL(entry));
      str = g_strdup (get);
      g_snprintf (str, 1024, "%s%c", get, key);
      gtk_label_set_text (GTK_LABEL(entry), str);
      g_free (str);
      childindex = -1;
      gtk_flow_box_set_filter_func (fb, filter_func, entry, NULL);
      if (options->l)
      {
        geo_mk (top);
      }
      gtk_widget_grab_focus (GTK_WIDGET(fb));
      return TRUE;
  }
  return FALSE;

#undef MOD1
#undef SHIFT
#undef CONTROL
#undef KEY
}

int
main (int argc, char **argv)
{
  GtkWidget *filter, *label, *grid, *flowbox, *scrolled, *window;
  guint count;

  options = g_new0 (Options, 1);
  options->l = FALSE;
  options->v = FALSE;
  char *s;

  gtk_init (&argc, &argv);

  parse_opt (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_type_hint (GTK_WINDOW(window), GDK_WINDOW_TYPE_HINT_DIALOG);
  gtk_window_set_decorated (GTK_WINDOW(window), FALSE);
  gtk_window_set_skip_taskbar_hint (GTK_WINDOW(window), TRUE);
  gtk_window_set_skip_pager_hint (GTK_WINDOW(window), TRUE);
  gtk_window_set_title (GTK_WINDOW(window), "t4");
  g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), &window);

  grid = gtk_grid_new ();
  gtk_widget_show (grid);

  if (options->p)
    s = g_strconcat (options->p, " :", NULL);
  else
    s = PROMPT;
  label = gtk_label_new (s);
  /*gtk_widget_set_name (label, "Prompt");*/
  gtk_widget_show (label);

  filter = gtk_label_new (NULL);
  gtk_label_set_width_chars (GTK_LABEL(filter), 10);
  gtk_label_set_max_width_chars (GTK_LABEL(filter), 80);
  gtk_label_set_xalign (GTK_LABEL(filter), 0);
  gtk_widget_show (filter);

  flowbox = flowbox_mk ();

  scrolled = scrolled_mk ();

  gtk_container_add (GTK_CONTAINER(scrolled), flowbox);

  provider_add(window);
  count = read_input (flowbox);
  if (!count)
  {
    GtkWidget *lab;
    lab = make_label ("");
    gtk_container_add (GTK_CONTAINER(flowbox), lab);
  }

  gtk_grid_attach (GTK_GRID(grid), label, 0, 0, 1, 1);
  gtk_grid_attach_next_to (GTK_GRID(grid), filter, label,GTK_POS_RIGHT, 1, 1);

  if (options->l)
  {
    gtk_widget_set_hexpand (filter, TRUE);
    gtk_widget_set_halign (filter, GTK_ALIGN_FILL);
    gtk_widget_set_hexpand (scrolled, TRUE);
    gtk_flow_box_set_min_children_per_line (GTK_FLOW_BOX(flowbox), 1);
    gtk_flow_box_set_max_children_per_line (GTK_FLOW_BOX(flowbox), 1);
    gtk_flow_box_set_vadjustment (GTK_FLOW_BOX (flowbox),
                                gtk_scrolled_window_get_vadjustment (GTK_SCROLLED_WINDOW (scrolled)));
    if (options->b)
    {
      gtk_grid_insert_row (GTK_GRID(grid), 0);
      gtk_grid_attach (GTK_GRID(grid), scrolled, 0, 0, 2, 1);
    }
    else {
      gtk_grid_attach (GTK_GRID(grid), scrolled, 0, 1, 2, 1);
    }
  }
  else
  {
    gtk_flow_box_set_min_children_per_line (GTK_FLOW_BOX(flowbox), 1);
    gtk_flow_box_set_max_children_per_line (GTK_FLOW_BOX(flowbox), 1);
    gtk_flow_box_set_hadjustment (GTK_FLOW_BOX (flowbox),
                                gtk_scrolled_window_get_hadjustment (GTK_SCROLLED_WINDOW (scrolled)));
    gtk_grid_attach_next_to (GTK_GRID(grid), scrolled, filter, GTK_POS_RIGHT, 1, 1);
  }

  g_signal_connect (G_OBJECT(flowbox), "key-press-event",
                    G_CALLBACK(flowbox_key_press_event_cb), filter);

  gtk_widget_show (grid);
  gtk_container_add (GTK_CONTAINER(window), grid);

  /*provider_add(window);*/

  gtk_widget_show (label);
  gtk_widget_show (filter);
  gtk_widget_show (flowbox);
  gtk_widget_show (scrolled);
  gtk_widget_show (grid);
  gtk_widget_show (window);

  gtk_widget_set_can_focus (flowbox, TRUE);

  geo_mk (window);

  gtk_main ();

  return 0;
}
