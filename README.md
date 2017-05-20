# t4-menu
menu system. little dmenu clone.

I love dmenu.i like wm wayland backend ...


## Install:
depend: gtk+3

Edit config.mk

make

sudo make install

## keybinding:
  Next: Ctrl-n, Ctrl-j, Rigth, Down

  Previus: Ctr-p, Ctrl-k, Left, Up
  
  Page Next: Ctr-f.
  
  Page Previus: Ctrl-b.
  
  Edit:
  
  delete previous char: Ctrl-h.
  
  delete previuos word: Ctrl-u.
  
  For custom keybind copy DATADIR/share/t4/t4.css to CONFIGDIR/t4/t4.css.
  
  And edit colors and font and keybindings.

## geometry:
  Precedence en axis x is W > x in all modes
  
  a) horizontal mode: (default)
  
    e.j stack right x > screen width.
        
    complete width W > screen width.
  
  b) listing mode:
  
    Default height 2/3 screen. Default width 1/6 screen.
    
    For full height. H > screen.
    
    In bottom mode -y is ignored.
  
  With -w --windowid in X11 embed in app.
  
