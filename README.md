# t4-menu
menu system. little dmenu clone.

## Use:
  j4-dmenu-desktop --dmenu="t4 [options]"
  ls /usr/bin | t4 [options] | /bin/sh "$@"
  dmenu_path | t4 [options] | /bin/sh "$@"

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
  For sway view sample config for testing, copy to $HOME/sway/config.d/

## Font and Color settings
  Font: use pango form

  Color:
    from gtk-doc
    CSS allows to specify colors in various ways, using numeric values or names from a predefined list of colors.

    〈color〉 = currentColor | transparent | 〈color name〉 | 〈rgb color〉 | 〈rgba color〉 | 〈hex color〉 | 〈gtk color〉
    〈rgb color〉 = rgb( 〈number〉, 〈number〉, 〈number〉 ) | rgb( 〈percentage〉, 〈percentage〉, 〈percentage〉 )
    〈rgba color〉 = rgba( 〈number〉, 〈number〉, 〈number〉, 〈alpha value〉 ) | rgba( 〈percentage〉, 〈percentage〉, 〈percentage〉, 〈alpha value〉 )
    〈hex color〉 = #〈hex digits〉
    〈alpha value〉 = 〈number〉, clamped to values between 0 and 1
  (warning, no have default colors,set color, is totaly transparent)
