# t4-menu
menu system. little dmenu clone.


## Install:
depend: gtk+3

Edit config.mk

make

sudo make install

## keybinding:
  Next: Ctrl-n, Ctrl-j, Ctrl-Rigth, Tab, Down

  Previus: Ctr-p, Ctrl-k, Ctr-Left, Shift-Tab, Up

  Page Next: Alt-n, Alt-j

  Page Previus: Alt-p, Alt-k

  Confirm Selection: Return, Ctrl-Return, Ctrl-m

  Copy selection: Shift-Return.

##  Edit:
        gtkentry keybindings


## geometry:
  Precedence en axis x is W > x in all modes

  a) horizontal mode: (default)

    e.j stack right x > screen width.

    full width W > screen width.

  b) listing mode:

    Default height 2/3 screen. Default width 1/6 screen.

    For full height. H > screen.

    In bottom mode -y is ignored.

  With -w --windowid in X11 embed in app.

## Don't use geometry with wayland backend.
