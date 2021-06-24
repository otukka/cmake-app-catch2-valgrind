#!/bin/bash

if [[ ! -d "build" ]]; then
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    cd build
fi





make VERBOSE=1 || exit 1


