#!/bin/bash

if [ -z "$1" ]; then
    echo "File name is not specified"
    exit 1
fi

path_to_file=$(realpath "$1")

ls -R / 2>/dev/null | while read -r line; do
    if [[ "$line" =~ :$ ]]; then
        current_dir="${line%:}"
    elif [[ -n "$line" ]]; then
        file_path="$current_dir/$line"
        if [ -L "$file_path" ]; then
            link_target=$(realpath "$file_path" 2>/dev/null)
            if [ "$link_target" = "$path_to_file" ]; then
                echo "$file_path"
            fi
        fi
    fi
done