#!/bin/bash
gcc -std=c99 --coverage -Werror -Wall -Wpedantic -Wextra -Wvla -Wfloat-equal -Wconversion -Wvla -c -g3 main.c
gcc -std=c99 --coverage -Werror -Wall -Wpedantic -Wextra -Wvla -Wfloat-equal -Wconversion -Wvla -c -g3 big_double.c
gcc -std=c99 --coverage -Werror -Wall -Wpedantic -Wextra -Wvla -Wfloat-equal -Wconversion -Wvla -c -g3 big_double_tools.c
gcc --coverage -o app.exe big_double_tools.c big_double.o main.o -g3
./app.exe
gcov main.c big_double.c big_double_tools.c -rf
