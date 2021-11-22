cmake_minimum_required(VERSION 3.20)
project(lab_05 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_05 src/queue.c inc/queue.h src/queue_like_array.c inc/queue_like_array.h src/queue_like_list.c inc/queue_like_list.h src/report_time_memory.c inc/report_time_memory.h main.c src/modes.c inc/modes.h)
