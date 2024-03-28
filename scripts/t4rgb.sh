#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

rgb_file="$SCRIPT_DIR/rgb.txt"
[[ ${rgb_file:?rgb.txt not found} ]]

select=$(sed -n 's/^[0-9 \t]*\([a-zA-Z0-9 ].*$\)/<span foreground="\1">██ <\/span>\1/p' ${rgb_file} | t4 -l 40 | cut -d ' ' -f 2-)

if [[ -z ${select} ]]; then
    exit 1
else
    sel=$(grep -o "[0-9\s][^a-zA-Z]*${select}$" ${rgb_file})
fi


if [[ $sel =~ \ *([0-9]*)\ *([0-9]*)\ *([0-9]*) ]]; then
    cred=${BASH_REMATCH[1]}
    cgreen=${BASH_REMATCH[2]}
    cblue=${BASH_REMATCH[3]}
fi

printf "%s\tRGB: %d,%d,%d\t#%02x%02x%02x\n" "${select}" $cred $cgreen $cblue $cred $cgreen $cblue
