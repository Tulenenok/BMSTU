#!/bin/sh

keys="-std=c99 --coverage -Werror -Wall -Wpedantic -Wextra -Wvla -Wfloat-equal -Wconversion -Wvla -g3"

gcc ${keys} -c tools.c
gcc ${keys} -c big_int.c
gcc ${keys} -c unit_big_int.c
gcc --coverage -o app.exe tools.o big_int.o unit_big_int.o -g3

./app.exe

gcov big_int.c -rf