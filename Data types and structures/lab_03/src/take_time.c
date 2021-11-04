#include "../inc/take_time.h"

#include "../inc/matrix.h"
#include "../inc/index_matrix.h"

#define COUNT_FOR 500

int multiply_sparse_method_with_time(bool is_matrix_input, bool is_vector_input, take_time_t *take_time, double *density) {
    if (!is_vector_input) {
        printf("\nVector was not input\n");
        return EXIT_SUCCESS;
    }

    if (!is_matrix_input) {
        printf("\nMatrix was not input\n");
        return EXIT_SUCCESS;
    }

    FILE *f_matrix = fopen("C:\\projects\\C\\TSD\\lab_03\\shared\\matrix.txt", "r");
    if (!f_matrix) {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    index_matrix_t mat;
    if (input_index_matrix_from_file(f_matrix, &mat)) {
        printf("ERROR WITH MATRIX\n");
        fclose(f_matrix);
        return EXIT_FAILURE;
    }

    fclose(f_matrix);

    FILE *f_vector = fopen("C:\\projects\\C\\TSD\\lab_03\\shared\\vector.txt", "r");
    if (!f_vector) {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    index_matrix_t vec;
    if (input_index_matrix_from_file(f_vector, &vec)) {
        printf("ERROR WITH VECTOR\n");
        fclose(f_vector);
        return EXIT_FAILURE;
    }

    fclose(f_vector);

    if(mat.count_columns != vec.count_rows)
    {
        printf("Invalid sizes of matrix and vector");
        return EXIT_FAILURE;
    }

    index_matrix_t res;

    take_time->count_return_for = COUNT_FOR;
    take_time->time = 0;

    printf("WAIT");
    for(int i = 0; i < take_time->count_return_for; i++)
    {
        long double new_time = 0;
        time_multiply_index_matrix(&mat, &vec, &res, &new_time);
        take_time->time += (new_time / take_time->count_return_for);

        free_index_matrix(&res);

        if(i - i / 20 * 20 == 0)
            printf("-");
    }
    printf("> OK\n");

    *density = (double)mat.count_elems / ((double)mat.count_rows * (double)mat.count_columns) * 100;

    printf("\nSize of matrix %zu x %zu", mat.count_rows, mat.count_columns);
    printf("\nSize of vector %zu x 1", vec.count_rows);
    printf("\nDensity %f\n", *density);

    free_index_matrix(&mat);
    free_index_matrix(&vec);

    return EXIT_SUCCESS;
}

int multiply_classic_method_with_time(bool is_matrix_input, bool is_vector_input, take_time_t *take_time)
{
    if(!is_vector_input)
    {
        printf("\nVector was not input\n");
        return EXIT_SUCCESS;
    }

    if(!is_matrix_input)
    {
        printf("\nMatrix was not input\n");
        return EXIT_SUCCESS;
    }

    FILE *f_matrix = fopen("C:\\projects\\C\\TSD\\lab_03\\shared\\matrix.txt", "r");
    if(!f_matrix)
    {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    matrix_t mat;
    if( input_matrix_from_file(f_matrix, &mat))
    {
        printf("ERROR WITH MATRIX\n");
        fclose(f_matrix);
        return EXIT_FAILURE;
    }

    fclose(f_matrix);

    FILE *f_vector = fopen("C:\\projects\\C\\TSD\\lab_03\\shared\\vector.txt", "r");
    if(!f_vector)
    {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    matrix_t vec;
    if(input_matrix_from_file(f_vector, &vec) || vec.rows == 0 ||vec.columns != 1)
    {
        printf("ERROR WITH VECTOR\n");
        fclose(f_vector);
        return EXIT_FAILURE;
    }

    fclose(f_vector);

    if(mat.columns != vec.rows)
    {
        printf("Invalid sizes of matrix and vector");
        return EXIT_FAILURE;
    }

    matrix_t res;

    take_time->count_return_for = COUNT_FOR;
    take_time->time = 0;
    printf("WAIT");
    for(int i = 0; i < take_time->count_return_for; i++)
    {
        long double new_time = 0;
        time_multiply_matrix(&mat, &vec, &res, &new_time);
        take_time->time += (new_time / take_time->count_return_for);

        free_classic_matrix(&res);

        if(i - i / 20 * 20 == 0)
            printf("-");
    }

    printf("> OK\n");

    free_classic_matrix(&mat);
    free_classic_matrix(&vec);

    return EXIT_SUCCESS;
}

int multiply_classic_method_with_memory(bool is_matrix_input, bool is_vector_input, unsigned long *memory)
{
    if(!is_vector_input)
    {
        printf("\nVector was not input\n");
        return EXIT_SUCCESS;
    }

    if(!is_matrix_input)
    {
        printf("\nMatrix was not input\n");
        return EXIT_SUCCESS;
    }

    FILE *f_matrix = fopen("C:\\projects\\C\\TSD\\lab_03\\shared\\matrix.txt", "r");
    if(!f_matrix)
    {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    matrix_t mat;
    if( input_matrix_from_file(f_matrix, &mat))
    {
        printf("ERROR WITH MATRIX\n");
        fclose(f_matrix);
        return EXIT_FAILURE;
    }

    fclose(f_matrix);

    FILE *f_vector = fopen("C:\\projects\\C\\TSD\\lab_03\\shared\\vector.txt", "r");
    if(!f_vector)
    {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    matrix_t vec;
    if(input_matrix_from_file(f_vector, &vec) || vec.rows == 0 ||vec.columns != 1)
    {
        printf("ERROR WITH VECTOR\n");
        fclose(f_vector);
        return EXIT_FAILURE;
    }

    fclose(f_vector);

    matrix_t res;
    if(mat.columns != vec.rows)
    {
        printf("Invalid sizes of matrix and vector");
        return EXIT_FAILURE;
    }
    multiply_matrix(&mat, &vec, &res);
    free_classic_matrix(&res);

    *memory = size_of_matrix(&mat) + size_of_matrix(&vec) + size_of_matrix(&res);

    free_classic_matrix(&mat);
    free_classic_matrix(&vec);

    return EXIT_SUCCESS;
}

int multiply_sparse_method_with_memory(bool is_matrix_input, bool is_vector_input, unsigned long *memory) {
    if (!is_vector_input) {
        printf("\nVector was not input\n");
        return EXIT_SUCCESS;
    }

    if (!is_matrix_input) {
        printf("\nMatrix was not input\n");
        return EXIT_SUCCESS;
    }

    FILE *f_matrix = fopen("C:\\projects\\C\\TSD\\lab_03\\shared\\matrix.txt", "r");
    if (!f_matrix) {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    index_matrix_t mat;
    if (input_index_matrix_from_file(f_matrix, &mat)) {
        printf("ERROR WITH MATRIX\n");
        fclose(f_matrix);
        return EXIT_FAILURE;
    }

    fclose(f_matrix);

    FILE *f_vector = fopen("C:\\projects\\C\\TSD\\lab_03\\shared\\vector.txt", "r");
    if (!f_vector) {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    index_matrix_t vec;
    if (input_index_matrix_from_file(f_vector, &vec)) {
        printf("ERROR WITH VECTOR\n");
        fclose(f_vector);
        return EXIT_FAILURE;
    }

    fclose(f_vector);

    index_matrix_t res;

    if(mat.count_columns != vec.count_rows)
    {
        printf("Invalid sizes of matrix and vector");
        return EXIT_FAILURE;
    }
    multiply_index_matrix(&mat, &vec, &res);
    free_index_matrix(&res);

    *memory = size_of_index_matrix(&mat) + size_of_index_matrix(&vec) + size_of_index_matrix(&res);

    free_index_matrix(&mat);
    free_index_matrix(&vec);

    return EXIT_SUCCESS;
}

