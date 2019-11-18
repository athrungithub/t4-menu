# t4-menu
dmenu clone.

![](https://i.imgur.com/29FEPAa.png)

## Use:
launch with lists desktop files.

t4 [options]

With pipes works like dmenu and print selection to stdout.

j4-dmenu-desktop --dmenu=t4

dmenu_path | t4 | sh

ls /usr/bin | t4

## Install:
depend: gtk+3

optional: (for sway, wlr-layer-shell)
    wlroots

    wayland-clients

compile:
    meson

    ninja
    optional for sway wlr-layer-shell

    wayland-protocols

    wayland-scanner

git clone https://github.com/athrungithub/t4-menu

meson build

ninja -C build

sudo ninja -C build install

## Options:
  -b    prompt at bottom window.

  -x    x position.

  -y    y position.

  -W    wide window.

  -l    lines.

  -f    font.

  -p    prompt string.

  -t    terminal

  -w    windowid X11.

  -n    no exit on lost focus.

  -v    version.

  --nc  normal foreground color.

  --nb  normal background color.

  --fc  focused color.

  --fb  focused background color.

  --pc  prompt color.

  --pb  prompt background color.

  --ec  entry color.

  --eb  entry background color.


## Keybinding items:
  Diff with dmenu <tab> next item

  Next: C-n, M-l, C-Rigth, Tab, Down

  Previus: C-p, M-h, C-Left, Shift-Tab, Up

  Page Next: M-n, M-j, Page-Down

  Page Previus: M-p, M-k, Page-Up

  Home: M-g, Home

  End: M-G, End

  Return, C-j, C-m: Confirm Selection.

  C-Return: Confirm Selection and continues.

  Shift-Return: Copy selection to the input field.

  Escape, C-g, C-c: Exit without selecting an item, returning failure.
## Keybindig edit:
  C-b Left

  C-f Right

  M-b Move cursor to the start of the current word

  M-f Move cursor to the end of the current word

  C-a Home

  C-e End

  C-y Paste primary

  C-d Delete

  M-d Delete word

  C-k Delete line right

  C-u Delete line left

  C-h Backspace

## Geometry:
  Precedence W > x

  a) horizontal mode: (default)

    x > screen -> to right

    W > screen -> full wide

  b) listing mode:

    l > screen lines -> full height

## Don't use geometry position (x & y) with wayland backend.
  For sway view sample config for testing, copy to $HOME/sway/config.d/

  Important!. Set floating_minimun_size  75 x 12 (height font)
                  border none | border pixel 1

## Font and Color settings
  [ 〈font-style〉 || 〈font-variant〉 || 〈font-weight〉 || 〈font-stretch〉 ]? 〈font-size〉 〈font-family〉

  Color:
    from gtk-doc
    CSS allows to specify colors in various ways, using numeric values or names from a predefined list of colors.

    〈color〉 = currentColor | transparent | 〈color name〉 | 〈rgb color〉 | 〈rgba color〉 | 〈hex color〉 | 〈gtk color〉
    〈rgb color〉 = rgb( 〈number〉, 〈number〉, 〈number〉 ) | rgb( 〈percentage〉, 〈percentage〉, 〈percentage〉 )
    〈rgba color〉 = rgba( 〈number〉, 〈number〉, 〈number〉, 〈alpha value〉 ) | rgba( 〈percentage〉, 〈percentage〉, 〈percentage〉, 〈alpha value〉 )
    〈hex color〉 = #〈hex digits〉
    〈alpha value〉 = 〈number〉, clamped to values between 0 and 1

## Focus
  t4 no grab keyboard, for default is quit on lost focus

  Use -n for persistent. For example if use embed en X11 app.

## Embed X11
  w  windowid
