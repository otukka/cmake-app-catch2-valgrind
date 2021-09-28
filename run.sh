#!/bin/bash

# Create build folder if not exists
if [[ ! -d "build" ]]; then
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    cd build
fi

# Build the app
make VERBOSE=1 || exit 1

# Build the tests
make test VERBOSE=1 || exit 1

# Run the app
./app

# Run valgrind memory leak tests to app
valgrind --leak-check=yes ./app

# Run valgrind memory leak tests to tests.
# Currently this leaks memory, because new allocated int isn't freed.
valgrind --leak-check=yes ./tests