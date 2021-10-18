cmake_minimum_required(VERSION 3.20)
project(lab_02_new_version C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_02_new_version main.c src/flats.c src/modes.c src/tools.c)
