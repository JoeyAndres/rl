#!/usr/bin/env bash

cd /home/tester/rl && mkdir build && cd build && cmake .. && make -j8 && ./test/testRunner
