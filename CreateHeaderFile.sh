#!/bin/bash

# Clean includes library.
$(rm -rf includes/*);

# Acquire fileList (without directory location), fileListNoFilter (with directory location), fileListMod (directory list with '#include ' prefixed).
fileList=($(find . -name "*.h" -not -path "*boost*" -not -path "*Tests*" -not -path "*UnitTest++*" -type f -mtime -14 -printf '%f\n'));
fileListNoFilter=($(find . -name "*.h" -o -name "*.hpp" -not -path "*UnitTest++*" -not -path "*boost*"));
fileListMod=();
for ((i = 0; i < "${#fileList[*]}"; i++));
do
    fileListMod+=($"#include \""${fileList[i]}$"\"")
done

# Copy all headers to include directory.
for ((i = 0; i < "${#fileListNoFilter[*]}"; i++));
do
    cp "${fileListNoFilter[i]}" ./includes
done

# Copy the boost threadpool files manually.
cp -r ./boost/* ./includes/

# Create files.
echo "" > ./includes/AI.h
for ((i = 0; i < "${#fileList[*]}"; i++));
do
    echo "${fileListMod[i]}" >> ./includes/AI.h
done