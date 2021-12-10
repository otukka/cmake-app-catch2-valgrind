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
make VERBOSE=1
build=$?

# Build the tests
make test VERBOSE=1
test=$?

# Run the app
./app
app=$?

# Run valgrind memory leak tests to app
valgrind --leak-check=yes ./app
valgrind=$?


# Run valgrind memory leak tests to tests.
# Currently this leaks memory, because new allocated int isn't freed.
valgrind --leak-check=yes ./tests
valgrindtest=$?


RED='\033[0;31m'
GREEN='\033[0;32m'
NORMAL='\033[0m' # No Color

echo -n "build:         " && if [ "$build" == 0 ];          then echo -e ${GREEN}"PASS"${NORMAL}; else echo -e ${RED}"FAIL"${NORMAL}; fi;
echo -n "test:          " && if [ "$test" == 0 ];           then echo -e ${GREEN}"PASS"${NORMAL}; else echo -e ${RED}"FAIL"${NORMAL}; fi;
echo -n "app:           " && if [ "$app" == 0 ];            then echo -e ${GREEN}"PASS"${NORMAL}; else echo -e ${RED}"FAIL"${NORMAL}; fi;
echo -n "valgrind:      " && if [ "$valgrind" == 0 ];       then echo -e ${GREEN}"PASS"${NORMAL}; else echo -e ${RED}"FAIL"${NORMAL}; fi;
echo -n "valgrindtest:  " && if [ "$valgrindtest" == 0 ];   then echo -e ${GREEN}"PASS"${NORMAL}; else echo -e ${RED}"FAIL"${NORMAL}; fi;