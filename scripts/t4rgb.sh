#! /usr/bin/env bash

# name=$(sed -n 's/^[0-9 \t]*\([a-zA-Z0-9 ].*$\)/<span foreground="\1">██ <\/span>\1/p' /usr/share/nvim/runtime/rgb.txt| t4 -l 40  | cut -d ' ' -f 2-) ; grep -hw "$name" /usr/share/nvim/runtime/rgb.txt

for tmp in /usr/share/nvim /usr/share/emacs /usr/share/vim
do
   if  [[ -d ${tmp} ]]; then
       rgb_file=$(find ${tmp} -name rgb.txt)
       break
   else
       continue
   fi
done

[[ ${rgb_file:?rgb.txt not found} ]]

select=$(sed -n 's/^[0-9 \t]*\([a-zA-Z0-9 ].*$\)/<span foreground="\1">██ <\/span>\1/p' ${rgb_file} | t4 -n -l 40 | cut -d ' ' -f 2-)

if [[ -z ${select} ]]; then
    exit 1
else
    sel=$(grep -o "[0-9\s][^a-zA-Z]*${select}$" ${rgb_file})
fi

# use bash rematch
# while read cred cblue cgreen
# do
    # printf "%s\tRGB: %d,%d,%d\t#%02X%02X%02X\n" "${select}" $cred $cblue $cgreen $cred $cblue $cgreen
# done < <(echo "${sel}" | grep -o "^[ 0-9]*[^a-zA-Z]")

if [[ $sel =~ \ *([0-9]*)\ *([0-9]*)\ *([0-9]*) ]]; then
    cred=${BASH_REMATCH[1]}
    cgreen=${BASH_REMATCH[2]}
    cblue=${BASH_REMATCH[3]}
fi

printf "%s\tRGB: %d,%d,%d\t#%02x%02x%02x\n" "${select}" $cred $cgreen $cblue $cred $cgreen $cblue
