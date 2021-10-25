#ifndef LAB_03_SPARSE_MATRIX_H
#define LAB_03_SPARSE_MATRIX_H

#include <stdlib.h>
#include <stdio.h>

#include "../inc/node.h"
#include "../inc/tools.h"

typedef struct
{
    size_t count_not_null;

    int *values;
    size_t *rows;
    Node_t *columns;
} sparse_matrix_t;

int input_sparse_matrix_from_file(FILE *f, sparse_matrix_t *matrix);

void print_sparse_matrix_to_file(FILE *f, sparse_matrix_t *matrix);

void free_matrix(sparse_matrix_t matrix);

#endif //LAB_03_SPARSE_MATRIX_H
