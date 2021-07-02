#!/bin/bash


export PATH="/snap/bin/:$PATH"

if [[ ! -d "build" ]]; then
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    cd build
fi


echo -e "\n-\n-"
make || exit 1


echo -e "\n-\n-"
valgrind --leak-check=yes ./app


echo -e "\n-\n-"
valgrind --leak-check=yes ./tests