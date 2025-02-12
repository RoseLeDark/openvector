#!/bin/bash

meson build
ninja -C build
ninja -C build test
./build/run_tests
