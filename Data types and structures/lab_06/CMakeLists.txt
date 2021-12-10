cmake_minimum_required(VERSION 3.20)
project(lab_06 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_06 main.c src/binary_search_tree.c inc/binary_search_tree.h src/abl_tree.c inc/abl_tree.h src/mode.c inc/mode.h src/tools.c inc/tools.h src/hash_table.c inc/hash_table.h src/node.c inc/node.h)
