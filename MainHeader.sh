#!/bin/bash

# Recreate AI.h
rm -rf include/AI.h
touch include/AI.h

fileList=$(ls ./include | grep '\.h$')
#echo $fileList

for file in $fileList
do
    echo "#include \"${file}\"" >> include/AI.h
done
