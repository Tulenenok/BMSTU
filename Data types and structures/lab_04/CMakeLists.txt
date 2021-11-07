cmake_minimum_required(VERSION 3.20)
project(lab_04 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_04 main.c src/node.c src/static_stack.c inc/static_stack.h src/linked_list_stack.c inc/linked_list_stack.h src/tools.c inc/tools.h src/modes.c inc/modes.h)
