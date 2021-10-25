#include "../inc/matrix.h"
#include "../inc/tools.h"
#include <assert.h>

void free_data(int** data, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(data[i]);

    free(data);
}

void free_classic_matrix(matrix_t* matrix)
{
    free_data(matrix->data, matrix->rows);
}

int input_size(FILE* const f, matrix_t* matrix)
{
    assert(f && matrix);

    if (INPUT_ONE_ELEM != fscanf(f, "%zu", &matrix->rows) || matrix->rows <= 0)
        return -1;

    if (INPUT_ONE_ELEM != fscanf(f, "%zu", &matrix->columns) || matrix->columns <= 0)
        return -2;
    return EXIT_SUCCESS;
}

int** alloc_memory_for_matrix(const size_t r, const size_t c)
{
    int **data = malloc(r * sizeof(int*));
    if (!data)
        return NULL;

    for (size_t i = 0; i < r; i++)
    {
        data[i] = malloc(c * sizeof(int));
        if (!data[i])
        {
            free_data(data, r);
            return NULL;
        }
    }
    return data;
}

int fill_matrix_from_file(FILE *const f, matrix_t* matrix)
{
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->columns; j++)
            if (INPUT_ONE_ELEM != fscanf(f, "%d", &matrix->data[i][j]))
                return -1;

    if (ferror(f))
        return -2;

    return EXIT_SUCCESS;
}

int input_matrix_from_file(FILE* const f, matrix_t* matrix)
{
    int rc;
    if ((rc = input_size(f, matrix)))
        return rc;

    matrix->data = alloc_memory_for_matrix(matrix->rows, matrix->columns);
    if (!matrix->data)
        return -3;

    if ((rc = fill_matrix_from_file(f, matrix)))
    {
        free_classic_matrix(matrix);
        return rc;
    }

    return EXIT_SUCCESS;
}

void print_matrix_to_file(FILE* const f, const matrix_t* const matrix)
{
    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->columns; j++)
            fprintf(f, "%d ", matrix->data[i][j]);
        fprintf(f, "\n");
    }
}

