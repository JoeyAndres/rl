#!/bin/bash

INCLUDE_DIR="$1"
OUTPUT_DIR="$2"
SUB_HEADERS_PREFIX="$3"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [[ -z "$INCLUDE_DIR" ]]; then
INCLUDE_DIR="./"  # Default to current directory.
fi

if [[ -z "$OUTPUT_DIR" ]]; then
OUTPUT_DIR="./"  # Default to current directory.
fi

# Remove so it doesn't list itself.
rm -rf "${OUTPUT_DIR}"/rl

fileList=`ls "${INCLUDE_DIR}" | grep '\.h$'`
#echo $fileList

cat "${DIR}/license.h" >> "${OUTPUT_DIR}"/rl
echo -e "\n#pragma once\n" >> "${OUTPUT_DIR}"/rl
for file in $fileList
do
    echo "#include \"${SUB_HEADERS_PREFIX}/${file}\"" >> "${OUTPUT_DIR}"/rl
done
