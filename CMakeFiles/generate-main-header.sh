#!/bin/bash

INCLUDE_DIR="$1"
OUTPUT_DIR="$2"
SUB_HEADERS_PREFIX="$3"
LIB_DIR="$4"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [[ -z "$INCLUDE_DIR" ]]; then
exit 1
fi

if [[ -z "$OUTPUT_DIR" ]]; then
exit 1
fi

if [[ -z "$LIB_DIR" ]]; then
exit 1
fi

# Remove so it doesn't list itself.
rm -rf "${OUTPUT_DIR}"/rl

fileList1=`cd ${INCLUDE_DIR} && find -name "*.h" | tail -n +1 | cut -c 3-`
fileList2=`cd ${LIB_DIR} && find -name "*.h" | tail -n +1 | cut -c 3-`

# Include all files in $INCLUDE_DIR in one rl header file.
cat "${DIR}/license.h" >> "${OUTPUT_DIR}"/rl
echo -e "\n#pragma once\n" >> "${OUTPUT_DIR}"/rl
for file in $fileList1
do
    echo "#include \"${SUB_HEADERS_PREFIX}/${file}\"" >> "${OUTPUT_DIR}"/rl
done
for file in $fileList2
do
    echo "#include \"${SUB_HEADERS_PREFIX}/${file}\"" >> "${OUTPUT_DIR}"/rl
done

# Copy all files to INCLUDE_DIR to OUTPUT_DIR/rl_bits
rm -rf "${OUTPUT_DIR}/${SUB_HEADERS_PREFIX}"
mkdir -p "${OUTPUT_DIR}/${SUB_HEADERS_PREFIX}"
cp -a "$INCLUDE_DIR/." "${OUTPUT_DIR}/${SUB_HEADERS_PREFIX}"
cp -a "$LIB_DIR/." "${OUTPUT_DIR}/${SUB_HEADERS_PREFIX}"
find "${OUTPUT_DIR}/${SUB_HEADERS_PREFIX}" -type f ! -iname "*.h" -delete
