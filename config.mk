# t4
NAME = t4
# t4-version
VERSION = `git describe --tags`
# build date
BUILDDATE = `date +%Y.%m.%d`

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man
DATAPREFIX = $(PREFIX)/share

CFLAGS  += -g -Wall
LDFLAGS ?= -Wall
CFLAGS  += $(shell pkg-config --cflags gtk+-3.0) \
	$(shell pkg-config --cflags gdk-3.0) \
	$(shell pkg-config --cflags wayland-client) \
	$(shell pkg-config --cflags gdk-wayland-3.0) \
	$(shell pkg-config --cflags wlroots)

LDFLAGS += $(shell pkg-config --libs gtk+-3.0) \
	$(shell pkg-config --libs gdk-3.0) \
	$(shell pkg-config --libs wayland-client) \
	$(shell pkg-config --libs gdk-wayland-3.0) \
	$(shell pkg-config --libs wlroots)

# flags
CPPFLAGS = -DVERSION=\"${VERSION}\" -DNAME=\"${NAME}\" \
		   -DDATAPREFIX=\"${DATAPREFIX}\" -DBUILDDATE=\"${BUILDDATE}\" -D_DEFAULT_SOURCE
T4_CFLAGS = $(INCS) $(CPPFLAGS) $(CFLAGS)
T4_LDFLAGS = $(LIBS) $(LDFLAGS)

# compiler and linker
#CC = c99
