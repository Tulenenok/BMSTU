#ifndef LAB_03_MATRIX_H
#define LAB_03_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    size_t rows;
    size_t columns;
    int **data;
} matrix_t;

int input_matrix_from_file(FILE* const f, matrix_t* matrix);

void free_classic_matrix(matrix_t* matrix);

void print_matrix_to_file(FILE* const f, const matrix_t* const matrix);

#endif //LAB_03_MATRIX_H
