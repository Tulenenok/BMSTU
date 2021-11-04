#ifndef LAB_03_TAKE_TIME_H
#define LAB_03_TAKE_TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
    int count_return_for;
    clock_t start;
    clock_t end;
    long double time;
} take_time_t;

int multiply_sparse_method_with_time(bool is_matrix_input, bool is_vector_input, take_time_t *take_time, double *density);

int multiply_classic_method_with_time(bool is_matrix_input, bool is_vector_input, take_time_t *take_time);

int multiply_sparse_method_with_memory(bool is_matrix_input, bool is_vector_input, unsigned long *memory);

int multiply_classic_method_with_memory(bool is_matrix_input, bool is_vector_input, unsigned long *memory);

#endif //LAB_03_TAKE_TIME_H
