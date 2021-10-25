#include "../inc/index_matrix.h"
#include "../inc/tools.h"

// matrix
// 9
// 3
// 3
// 1 2 3 4 5 6 7 8 9
// 0 0 0 1 1 1 2 2 2
// 0 1 2 0 1 2 0 1 2

// vector
// 3
// 3
// 3
// 1 2 3
// 0 1 2

int input_index_matrix_from_file(FILE *f, index_matrix_t *m)
{
    int rc;

    if((rc = input_size_of_matrix(f, &m->count_rows, &m->count_columns, false)))
        return rc;

    count_not_null_elems_in_file(f, m->count_rows, m->count_columns, &m->count_elems);

    rewind(f);
    input_size_of_matrix(f, &m->count_rows, &m->count_columns, false);

    if((rc = alloc_memory_for_array(m->count_elems, sizeof(int), &m->elems)))
        return ALLOCATE_MEMORY_ERROR;

    if((rc = alloc_memory_for_array(m->count_elems, sizeof(int), &m->rows)))
        return ALLOCATE_MEMORY_ERROR;

    if((rc = alloc_memory_for_array(m->count_elems, sizeof(int), &m->columns)))
        return ALLOCATE_MEMORY_ERROR;

    int t, curr_pos_in_matrix = 0;
    for(size_t i = 0; i < m->count_rows; i++)
        for(size_t j = 0; j < m->count_columns; j++)
        {
            if(INPUT_ONE_ELEM != fscanf(f, "%d", &t))
                return EXIT_FAILURE;
            if(t != 0)
            {
                m->elems[curr_pos_in_matrix] = t;
                m->rows[curr_pos_in_matrix] = (int)i;
                m->columns[curr_pos_in_matrix] = (int)j;
                curr_pos_in_matrix++;
            }
        }
    return EXIT_SUCCESS;
}

void print_index_matrix(FILE *f, index_matrix_t *m)
{
    fprintf(f, "A : ");
    for(size_t i = 0; i < m->count_elems; i++)
        fprintf(f, "%d ", m->elems[i]);

    fprintf(f, "\nAI : ");
    for(size_t i = 0; i < m->count_elems; i++)
        fprintf(f, "%d ", m->rows[i]);

    fprintf(f, "\nAJ : ");
    for(size_t i = 0; i < m->count_elems; i++)
        fprintf(f, "%d ", m->columns[i]);
}

// Функция проверяет принадлежит ли элемент заданному массиву
// Если да, то возвращает индекс искомого элемента, иначе -1
int is_number_in_array(size_t n, const int a[], int number)
{
    for(int i = 0; i < n; i++)
        if(a[i] == number)
            return i;
    return -1;
}

int count_not_null_elems_in_res_matrix(index_matrix_t *matrix, index_matrix_t *vector)
{
    int curr_row_matrix = 0, curr_sum = 0, count = 0;
    for(size_t i = 0; i < matrix->count_elems; i++)
    {
        if (matrix->rows[i] != curr_row_matrix) {
            if (curr_sum != 0)
                count++;

            curr_sum = 0;
            curr_row_matrix++;
        }

        int pos = is_number_in_array(vector->count_rows, vector->rows, matrix->columns[i]);
        if (pos != -1)
            curr_sum += matrix->elems[i] * vector->elems[pos];
    }
    if (curr_sum != 0)
        count++;
    return count;
}

int multiply_index_matrix(index_matrix_t *matrix, index_matrix_t *vector, index_matrix_t *result)
{
    if(matrix->count_columns != vector->count_rows)
        return INVALID_PARAMS_OF_MATRIX_AND_VECTOR;

    result->count_rows = matrix->count_rows;
    result->count_columns = vector->count_columns;

    int count_not_null_elems = count_not_null_elems_in_res_matrix(matrix, vector);
    if(alloc_memory_for_array(count_not_null_elems, sizeof(int), &result->elems))
        return ALLOCATE_MEMORY_ERROR;
    if(alloc_memory_for_array(count_not_null_elems, sizeof(int), &result->rows))
        return ALLOCATE_MEMORY_ERROR;
    if(alloc_memory_for_array(count_not_null_elems, sizeof(int), &result->columns))
        return ALLOCATE_MEMORY_ERROR;

    result->count_elems = (size_t)count_not_null_elems;

    int curr_row_matrix = 0, curr_row_result = 0, curr_sum = 0;

    for(size_t i = 0; i < matrix->count_elems; i++)
    {
        if(matrix->rows[i] != curr_row_matrix)
        {
            if(curr_sum != 0)
            {
                result->elems[curr_row_result] = curr_sum;
                result->rows[curr_row_result] = curr_row_matrix;
                result->columns[curr_row_result] = 0;
                curr_row_result++;
            }
            curr_sum = 0;
            curr_row_matrix++;
        }

        int pos = is_number_in_array(vector->count_rows, vector->rows, matrix->columns[i]);
        if(pos != -1)
            curr_sum += matrix->elems[i] * vector->elems[pos];
    }

    if(curr_sum != 0)
    {
        result->elems[curr_row_result] = curr_sum;
        result->rows[curr_row_result] = curr_row_matrix;
    }

    return EXIT_SUCCESS;
}

int test_multiply(void)
{
    FILE *f = fopen("C:\\projects\\C\\TSD\\lab_03\\test\\pos_01_in.txt", "r");

    index_matrix_t index_matrix;
    index_matrix_t index_vector;

    printf("MATRIX:\n");
    if(input_index_matrix_from_file(f, &index_matrix))
    {
        printf("UPSET");
        return -1;
    }

    print_index_matrix(stdout, &index_matrix);

    fclose(f);
    f = fopen("C:\\projects\\C\\TSD\\lab_03\\test\\pos_02_in.txt", "r");

    printf("\n\nVECTOR:\n");
    if(input_index_matrix_from_file(f, &index_vector))
    {
        printf("UPSET");
        return -1;
    }

    print_index_matrix(stdout, &index_vector);

    fclose(f);

    index_matrix_t res;
    if(multiply_index_matrix(&index_matrix, &index_vector, &res))
    {
        printf("I CANT DO THIS");
        return -1;
    }

    printf("\n\nRESULT OF MULTIPLY:\n");
    print_index_matrix(stdout, &res);

    free_index_matrix(&index_matrix);
    free_index_matrix(&index_vector);
    free_index_matrix(&res);
    return 0;
}

void free_index_matrix(index_matrix_t *m)
{
    free(m->elems);
    free(m->rows);
    free(m->columns);
}

int create_new_index_matrix(index_matrix_t *m, size_t count_elems)
{
    m->count_elems = count_elems;
    m->count_rows = count_elems;
    m->count_columns = count_elems;

    int rc;
    if((rc = alloc_memory_for_array(m->count_elems, sizeof(int), &m->elems)))
        return rc;
    if((rc = alloc_memory_for_array(m->count_rows, sizeof(int), &m->rows)))
        return rc;
    if((rc = alloc_memory_for_array(m->count_columns, sizeof(int), &m->columns)))
        return rc;
    return EXIT_SUCCESS;
}

void print_index_matrix_in_usual_format(FILE *f, index_matrix_t *m)
{
    size_t curr_i = 0;

    fprintf(f, "%zu %zu\n", m->count_rows, m->count_columns);

    for(size_t i = 0; i < m->count_rows; i++)
    {
        for (size_t j = 0; j < m->count_columns; j++)
        {
            if (m->rows[curr_i] == i && m->columns[curr_i] == j)
                fprintf(f, "%d ", m->elems[curr_i++]);
            else
                fprintf(f, "0 ");
        }
        fprintf(f, "\n");
    }
}
