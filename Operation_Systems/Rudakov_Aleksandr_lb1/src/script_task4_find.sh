#!/bin/bash

if [ -z "$1" ]; then
    echo "File name is not specified"
    exit 1
fi

path_to_file=$(realpath "$1")

find / -type l 2>/dev/null | while read -r link; do
    if [ "$(realpath "$link" 2>/dev/null)" = "$path_to_file" ]; then
        echo "$link"
    fi
done
