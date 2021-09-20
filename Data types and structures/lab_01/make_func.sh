#!/bin/sh

YELLOW="\033[33m" 

./make_debug.sh

cd ./func_tests || exit 1
./all_test.sh
cd ..

echo -e "${YELLOW}   ${YELLOW}"
gcov main.c

./make_clean.sh
