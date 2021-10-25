#include <assert.h>
#include <stdbool.h>

#include "../inc/sparse_matrix.h"

#define NULL_ELEM 0

#define ERROR_ALLOCATION 13

void input_matrix_help_func(FILE *f, sparse_matrix_t *matrix)
{
    rewind(f);

    size_t r, c;
    fscanf(f, "%zu", &r);
    fscanf(f, "%zu", &c);

    int t;
    int matrix_i = 0;
    for(size_t i = 0; i < r; i++)
        for(size_t j = 0; j < c; j++)
        {
            fscanf(f, "%d", &t);
            if(NULL_ELEM != t)
            {
                matrix->values[matrix_i] = t;
                matrix->rows[matrix_i] = i;
                insert_data_to_node_list_if_data_empty(matrix_i, j, matrix->columns);
                matrix_i++;
            }
        }
}

int input_sparse_matrix_from_file(FILE *f, sparse_matrix_t *matrix)
{
    size_t r, c;
    int rc;

    if((rc = input_size_of_matrix(f, &r, &c, false)))
        return rc;

    if((rc = count_not_null_elems_in_file(f, r, c, &matrix->count_not_null)))
        return rc;

    matrix->values = calloc(matrix->count_not_null, sizeof(int));
    if(!matrix->values)
        return ERROR_ALLOCATION;

    printf("Take memory for values :     ----> SUCCESS\n");

    matrix->rows = calloc(matrix->count_not_null, sizeof(size_t));
    if(!matrix->rows)
        return ERROR_ALLOCATION;

    printf("Take memory for rows :       ----> SUCCESS\n");

    malloc_for_node_list(c, &matrix->columns);

    printf("Take memory for columns :    ----> SUCCESS\n");

    input_matrix_help_func(f, matrix);

    return EXIT_SUCCESS;
}

void print_sparse_matrix_to_file(FILE *f, sparse_matrix_t *matrix)
{
    printf("\nA (vector with not null elems) : ");
    print_int_array(f, matrix->count_not_null, matrix->values);

    fprintf(f, "\n");

    printf("AI (vector with rows of not null elems) : ");
    print_size_t_array(f, matrix->count_not_null, matrix->rows);

    fprintf(f, "\n");

    printf("AJ (vector with index row that begin column) : ");
    print_node_list(f, matrix->columns);

    fprintf(f, "\n");
}

void free_matrix(sparse_matrix_t matrix)
{
    free_for_node_list(matrix.columns);
}

int is_matrix_had_only_null_elems(sparse_matrix_t *matrix)
{
    if(!matrix->count_not_null)
        return true;
    return false;
}

int is_vector(sparse_matrix_t *x)
{
    return x->columns->next == NULL;
}
