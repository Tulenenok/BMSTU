#!/bin/sh

keys="-std=c99 --coverage -Werror -Wall -Wpedantic -Wextra -Wvla -Wfloat-equal -Wconversion -Wvla -g3"

gcc ${keys} -c tools.c
gcc ${keys} -c unit_tools.c
gcc --coverage -o app.exe tools.o unit_tools.o -g3

./app.exe

gcov tools.c -rf