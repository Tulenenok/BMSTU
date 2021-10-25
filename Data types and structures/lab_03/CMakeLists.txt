cmake_minimum_required(VERSION 3.20)
project(lab_03 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_03 main.c src/sparse_matrix.c src/node.c src/tools.c src/modes.c src/matrix.c src/index_matrix.c)
