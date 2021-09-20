#!/bin/sh

keys="-std=c99 --coverage -Werror -Wall -Wpedantic -Wextra -Wvla -Wfloat-equal -Wconversion -Wvla -g3"

gcc ${keys} -c tools.c
gcc ${keys} -c big_double.c
gcc ${keys} -c big_double_tools.c
gcc ${keys} -c big_int.c
gcc ${keys} -c big_types.c
gcc ${keys} -c main.c
gcc --coverage -o app.exe tools.o big_double.o big_double_tools.o big_int.o big_types.o main.o -g3