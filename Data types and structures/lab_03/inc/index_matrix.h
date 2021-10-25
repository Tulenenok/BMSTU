#ifndef LAB_03_INDEX_MATRIX_H
#define LAB_03_INDEX_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#define INVALID_PARAMS_OF_MATRIX_AND_VECTOR 13

typedef struct
{
    size_t count_elems;
    size_t count_rows;
    size_t count_columns;
    int *elems;
    int *rows;
    int *columns;
} index_matrix_t;

int input_index_matrix_from_file(FILE *f, index_matrix_t *m);

void print_index_matrix(FILE *f, index_matrix_t *m);

int multiply_index_matrix(index_matrix_t *matrix, index_matrix_t *vector, index_matrix_t *result);

int test_multiply(void);

void free_index_matrix(index_matrix_t *m);

int create_new_index_matrix(index_matrix_t *m, size_t count_elems);

void print_index_matrix_in_usual_format(FILE *f, index_matrix_t *m);

unsigned long size_of_index_matrix(index_matrix_t *m);

#endif //LAB_03_INDEX_MATRIX_H