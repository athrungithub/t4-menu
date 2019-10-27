#ifndef LAYER_H
#define LAYER_H

#include <gtk/gtk.h>

// struct zwlr_layer_surface_v1 *surface;

void layer_init (GtkWidget *win);
void layer_move (int x, int y);
void layer_set_keyboard (gboolean);

#endif
