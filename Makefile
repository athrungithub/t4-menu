# t4 - simple dmenu clone
#
.POSIX:
WAYLAND_PROTOCOLS=$(shell pkg-config --variable=pkgdatadir wayland-protocols)
WAYLAND_SCANNER=$(shell pkg-config --variable=wayland_scanner wayland-scanner)

include config.mk

SRC = t4.c \
      wlr-layer-shell-unstable-v1-client-protocol.c \
      xdg-shell.c layer.c desktop.c

OBJ = $(SRC:.c=.o)

all: options protocol t4

wlr-layer-shell-unstable-v1-client-protocol.c: xdg-shell.c
	$(WAYLAND_SCANNER) private-code \
	wlr-layer-shell-unstable-v1.xml $@

wlr-layer-shell-unstable-v1-client-protocol.h: xdg-shell.h
	$(WAYLAND_SCANNER) client-header \
	  wlr-layer-shell-unstable-v1.xml $@

xdg-shell.c:
	$(WAYLAND_SCANNER) private-code \
        $(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@

xdg-shell.h:
	$(WAYLAND_SCANNER) client-header \
        $(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@

protocol: wlr-layer-shell-unstable-v1-client-protocol.h \
    wlr-layer-shell-unstable-v1-client-protocol.c \
    xdg-shell.h \
    xdg-shell.c

options:
	@echo t4 build options:
	@echo "CFLAGS   = $(T4_CFLAGS)"
	@echo "LDFLAGS  = $(T4_LDFLAGS)"
	@echo "CC       = $(CC)"

.c.o:
	@echo CC -c $<
	@$(CC) $(T4_CFLAGS) -c $<

$(OBJ): config.mk

t4: $(OBJ)
	@echo CC -o $@
	@$(CC) $(T4_CFLAGS) -o $@ $(OBJ) $(T4_LDFLAGS)

tags: $(SRC)
	@echo tags file
	@ctags_with_dep.sh $< $(T4_CFLAGS)

clean:
	@echo cleaning
	@rm -f $(NAME) $(OBJ) \
	    wlr-layer-shell-unstable-v1-client-protocol.c \
	    wlr-layer-shell-unstable-v1-client-protocol.h \
	    xdg-shell.c xdg-shell.h


install: all
	@echo installing executable file to $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@cp -f $(NAME) $(DESTDIR)$(PREFIX)/bin
	@chmod 755 $(DESTDIR)$(PREFIX)/bin/$(NAME)

uninstall:
	@echo removing executable file from $(DESTDIR)$(PREFIX)/bin
	@rm -f $(DESTDIR)$(PREFIX)/bin/$(NAME)

.PHONY: all options clean dist install uninstall
