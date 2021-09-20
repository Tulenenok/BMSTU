#!/bin/sh

keys="-std=c99 --coverage -Werror -Wall -Wpedantic -Wextra -Wvla -Wfloat-equal -Wconversion -Wvla -g3"

gcc ${keys} -c tools.c
gcc ${keys} -c big_double_tools.c
gcc ${keys} -c big_double.c
gcc ${keys} -c unit_big_double_tools.c
gcc --coverage -o app.exe tools.o big_double_tools.o big_double.o unit_big_double_tools.o -g3

./app.exe

gcov big_double_tools.c -rf