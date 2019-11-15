#ifndef LAYER_H
#define LAYER_H

#include <gtk/gtk.h>

#include "wlr-layer-shell-unstable-v1-client-protocol.h"

struct zwlr_layer_surface_v1 *layer_init (GtkWidget *win);
void layer_move (struct zwlr_layer_surface_v1 *surf, int x, int y);
void layer_set_keyboard (struct zwlr_layer_surface_v1 *surf, gboolean);

#endif
