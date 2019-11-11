#! /usr/bin/env bash

# name=$(sed -n 's/^[0-9 \t]*\([a-zA-Z0-9 ].*$\)/<span foreground="\1">██ <\/span>\1/p' /usr/share/nvim/runtime/rgb.txt| t4 -l 40  | cut -d ' ' -f 2-) ; grep -hw "$name" /usr/share/nvim/runtime/rgb.txt

if [[ -f /usr/share/nvim/runtime/rgb.txt ]]; then
    rgb_file=/usr/share/nvim/runtime/rgb.txt
elif [[ -f /usr/share/emacs/26.3/etc/rgb.txt ]]; then
    rgb_file=/usr/share/emacs/26.3/etc/rgb.txt
elif [[ -f /usr/share/vim/vim81/rgb.txt ]]; then
    rgb_file=/usr/share/vim/vim81/rgb.txt
else
        echo "file rgb.txt not found"
        exit 1
fi

select=$(sed -n 's/^[0-9 \t]*\([a-zA-Z0-9 ].*$\)/<span foreground="\1">██ <\/span>\1/p' ${rgb_file} | t4 -l 40  | cut -d ' ' -f 2-)

if [[ -z ${select} ]]; then
    exit 1
else
    selected=$(grep -hw "${select}" ${rgb_file})
    echo ${selected}
fi
