#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# TODO(jandres): Ignore runtime/references error atm. Have a story to convert these to smart pointers or something.
python ${DIR}/cpplint.py \
--recursive \
--extensions=h,cpp \
${DIR}/../include/ ${DIR}/../src/ ${DIR}/../test/
