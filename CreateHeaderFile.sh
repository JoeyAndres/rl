#!/bin/bash

fileList=($(find . -name "*.h" -not -path "*UnitTest++*" -not -path "*boost*" -not -path "*Tests*" -type f | sort));
fileListMod=()
for ((i = 0; i < "${#fileList[*]}"; i++))
do
    fileListMod+=($"#include \""${fileList[i]}$"\"")
    #echo "${fileListMod[i]}"
done

# Create if file don't exist, or erase it's contents otherwise.
AI_HEADER=$(cat AI_Header.txt)$'\n\n'
echo "$AI_HEADER" > AI.h

for ((i = 0; i < "${#fileListMod[*]}"; i++))
do
    # Append the includes.
    echo "${fileListMod[i]}" >> AI.h
done
