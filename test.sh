#!/bin/bash


export PATH="/snap/bin/:$PATH"

cd build

valgrind --leak-check=yes ./app