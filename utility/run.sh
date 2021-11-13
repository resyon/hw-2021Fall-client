#! /usr/bin/env bash

cd ..
if [ ! -d build ]; then
    mkdir build
fi

cd build
cmake ..
make

