gcc -g -o t4 t4.c layer.c wlr-layer-shell-unstable-v1-client-protocol.c xdg-shell.c -I. `pkg-config --cflags --libs gtk+-3.0 wayland-client gdk-wayland-3.0`

gcc -g -o layer layer.c wlr-layer-shell-unstable-v1-client-protocol.c xdg-shell.c -I. `pkg-config --cflags --libs gtk+-3.0 wayland-client gdk-wayland-3.0` -DGTK

