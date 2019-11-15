/* #include "xdg-shell-client-protocol.h" */
#include <wayland-client.h>
#include <gtk/gtk.h>
#include <gdk/gdkwayland.h>
#include "layer.h"

static GdkDisplay *disp;
static struct wl_display *wldisplay;
static struct zwlr_layer_shell_v1* shell;
static struct wl_registry *registry;
static struct  wl_surface *wl_surface;

static void nop() {}

static void add_interface(void* data, struct wl_registry* registry, uint32_t name,
        const char* interface, uint32_t version)
{
    if(strcmp(interface, zwlr_layer_shell_v1_interface.name) == 0) {
        shell = wl_registry_bind(registry, name, &zwlr_layer_shell_v1_interface, version);
    }
}

static void config_surface(void* data, struct zwlr_layer_surface_v1* surface,
        uint32_t serial, uint32_t _width, uint32_t _height)
{
    zwlr_layer_surface_v1_ack_configure(surface, serial);
}


struct zwlr_layer_surface_v1_listener surface_listener = {
    .configure = config_surface,
    .closed = nop,
};

struct wl_registry_listener listener = {
    .global = add_interface,
    .global_remove = nop
};

struct zwlr_layer_surface_v1 *
layer_init (GtkWidget *win)
{
    struct zwlr_layer_surface_v1 *surface;

    disp = gdk_display_get_default ();
    wldisplay = gdk_wayland_display_get_wl_display (disp);
    registry = wl_display_get_registry (wldisplay);
    wl_registry_add_listener (registry, &listener, NULL);
    wl_display_roundtrip (wldisplay);
    GdkWindow *gdk_win = gtk_widget_get_window (win);
    gdk_wayland_window_set_use_custom_surface (gdk_win);
    wl_surface = gdk_wayland_window_get_wl_surface (gdk_win);
    surface = zwlr_layer_shell_v1_get_layer_surface (shell, wl_surface, NULL,
            ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY, "t4");
    zwlr_layer_surface_v1_add_listener (surface, &surface_listener, NULL);

    wl_surface_commit (wl_surface);
    wl_display_roundtrip (wldisplay);
    return (surface);
}

void
layer_move (struct zwlr_layer_surface_v1 *surf, int x, int y)
{
    zwlr_layer_surface_v1_set_anchor(surf, ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP |
            ZWLR_LAYER_SURFACE_V1_ANCHOR_LEFT);
    zwlr_layer_surface_v1_set_margin(surf, y, 0, 0, x);
    return;
}

void layer_set_keyboard (struct zwlr_layer_surface_v1 *surf, gboolean opt)
{
    zwlr_layer_surface_v1_set_keyboard_interactivity (surf, opt);
    return;
}

#ifdef TEST
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

  if (KEY(Escape) || CONTROL(c) || CONTROL(g))
    {
      gtk_main_quit ();
      exit (-1);
    }
  return FALSE;
#undef MOD1
#undef SHIFT
#undef CONTROL
#undef KEY
}

int
main (int argc, char *argv[])
{
    GtkWidget *window;
    struct zwlr_layer_surface_v1 *surface;

    int width = 920, height = 22, x = 1000, y = 100;

    gtk_init (&argc, &argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size (GTK_WINDOW(window), width, height);
    /* gtk_window_set_resizable (GTK_WINDOW(window), FALSE); */
    gtk_window_set_decorated (GTK_WINDOW(window), FALSE);
    g_signal_connect (window, "destroy",
            G_CALLBACK (gtk_main_quit), window);
    g_signal_connect (window, "key-press-event", G_CALLBACK (key_press_event_cb), NULL);
    GtkWidget *entry = gtk_entry_new ();
    gtk_container_add (GTK_CONTAINER(window), entry);


    GtkWidget *n = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable (GTK_WINDOW(n), FALSE);
    gtk_window_set_transient_for (GTK_WINDOW(n), GTK_WINDOW(window));
    gtk_widget_realize (window);
    surface = layer_init (window);
    layer_set_keyboard (surface, TRUE);
    layer_move (surface, x, y);
    gtk_widget_show_all (window);
    gtk_widget_show (n);
    gtk_window_resize (GTK_WINDOW(window), width, height);
    gtk_main ();
    return 0;
}
#endif
