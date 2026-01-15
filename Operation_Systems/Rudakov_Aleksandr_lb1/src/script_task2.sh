#!/bin/bash

if [ -z "$1" ]; then
    echo "File name is not specified"
    exit 1
fi

inode=$(ls -i "$1" | awk '{print $1}')

ls -iR / 2>/dev/null | awk -v inode="$inode" '
    /:$/ { 
        sub(/:$/, "", $0); 
        dir = $0; 
        next 
    }
    {
        if ($1 == inode) {
            if (substr(dir, length(dir), 1) == "/")
                filepath = dir $2;
            else
                filepath = dir "/" $2;
            
            print filepath;
        }
    }
'