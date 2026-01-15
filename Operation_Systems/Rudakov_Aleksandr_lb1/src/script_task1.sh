#!/bin/bash

if [ -z "$1" ]; then
    echo "The output file name is not specified"
    exit 1
fi

out="$1"
> "$out"

file_types="- d b c l p s"

for type in $file_types; do
    ls -lR / 2>/dev/null | awk -v type="$type" '
        /:$/ { 
            sub(/:$/, "", $0); 
            dir = $0; 
            next 
        }
        {
            if (substr($1, 1, 1) == type) {
                if (substr(dir, length(dir), 1) == "/")
                    filepath = dir $NF;
                else
                    filepath = dir "/" $NF;
                print $1, $2, $3, $4, $5, $6, $7, $8, filepath >> "'"$out"'";
                exit
            }
        }
    '
done
