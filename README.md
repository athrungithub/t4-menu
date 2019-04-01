# t4-menu
menu system. little dmenu clone.

![im](https://imgur.com/29FEPA)

## Use:
  j4-dmenu-desktop --dmenu="t4 [options]". https://github.com/enkore/j4-dmenu-desktop
  
  ls /usr/bin | t4 [options] | /bin/sh "$@"
  
  dmenu_path | t4 [options] | /bin/sh "$@"

## Install:
depend: gtk+3

make
sudo make install

## keybinding items:
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
##  Edit:
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

## geometry:
  Precedence W > x

  a) horizontal mode: (default)
  
    x > screen -> to right
  
    W > screen -> full wide

  b) listing mode:
    
    l > screen lines -> full height

## Don't use geometry position (x & y) with wayland backend.
  For sway view sample config for testing, copy to $HOME/sway/config.d/
  
  Important!. Set floating_minimun_size  75 x 12 (height font)

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
