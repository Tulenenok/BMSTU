cmake_minimum_required(VERSION 3.20)
project(lab_07 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_07 main.c src/graph.c inc/graph.h src/tools.c inc/tools.h src/modes.c inc/modes.h)
