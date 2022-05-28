#!/bin/bash

# Create build folder if not exists
if [[ ! -d "build" ]]; then
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
else
    cd build
fi

if [[ $1 == "VERBOSE" ]]; then
VERBOSE="VERBOSE=1"
fi

# Build the app
make $VERBOSE
build=$?

if [ "$build" != 0 ]; then
    exit 1
fi

# Build the tests
make test $VERBOSE
test=$?

if [ "$test" != 0 ]; then
    exit 1
fi

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

echo -n "build              | " && if [ "$build" == 0 ];            then echo -e ${GREEN}"PASS"${NORMAL}; else echo -e ${RED}"FAIL"${NORMAL}; fi;
echo -n "run: app           | " && if [ "$app" == 0 ];              then echo -e ${GREEN}"PASS"${NORMAL}; else echo -e ${RED}"FAIL"${NORMAL}; fi;
echo -n "run: tests         | " && if [ "$test" == 0 ];             then echo -e ${GREEN}"PASS"${NORMAL}; else echo -e ${RED}"FAIL"${NORMAL}; fi;
echo -n "valgrind: app      | " && if [ "$valgrind" == 0 ];         then echo -e ${GREEN}"PASS"${NORMAL}; else echo -e ${RED}"FAIL"${NORMAL}; fi;
echo -n "valgrind: tests    | " && if [ "$valgrindtest" == 0 ];     then echo -e ${GREEN}"PASS"${NORMAL}; else echo -e ${RED}"FAIL"${NORMAL}; fi;

