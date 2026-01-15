#!/bin/bash

mkdir test_dir7
echo "A directory test_dir7 has been created"

get_dir_size() {
    echo "Directory size: $(du -sh test_dir7 | cut -f1)"
}

echo "Adding files to the directory..."
for i in {1..10}; do
    dd if=/dev/zero of=test_dir7/file$i bs=4K count=1 &>/dev/null
    get_dir_size
done

echo "Deleting files from the directory..."
for i in {1..10}; do
    rm test_dir7/file$i
    get_dir_size
done

rmdir test_dir7
echo "The test_dir7 directory has been deleted"