#include "../inc/take_time.h"

#include "../inc/matrix.h"
#include "../inc/index_matrix.h"

#define COUNT_FOR 1000

int multiply_sparse_method_with_time(bool is_matrix_input, bool is_vector_input, take_time_t *take_time) {
    if (!is_vector_input) {
        printf("\nVector was not input\n");
        return EXIT_SUCCESS;
    }

    if (!is_matrix_input) {
        printf("\nMatrix was not input\n");
        return EXIT_SUCCESS;
    }

    FILE *f_matrix = fopen("..\\shared\\matrix.txt", "r");
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

    FILE *f_vector = fopen("..\\shared\\vector.txt", "r");
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
        take_time->start = clock();
        multiply_index_matrix(&mat, &vec, &res);
        take_time->end = clock();

        take_time->time += ((long double) (take_time->end - take_time->start)) / CLOCKS_PER_SEC * 1000;

        if(i - i / 20 * 20 == 0)
            printf("-");
    }

    take_time->time /= take_time->count_return_for;
    printf("> OK\n");
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

    FILE *f_matrix = fopen("..\\shared\\matrix.txt", "r");
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

    FILE *f_vector = fopen("..\\shared\\vector.txt", "r");
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
        take_time->start = clock();
        multiply_matrix(&mat, &vec, &res);
        take_time->end = clock();

        take_time->time += ((double) (take_time->end - take_time->start)) / CLOCKS_PER_SEC * 1000;

        if(i - i / 20 * 20 == 0)
            printf("-");
    }

    take_time->time /= take_time->count_return_for;

    printf("> OK\n");

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

    FILE *f_matrix = fopen("..\\shared\\matrix.txt", "r");
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

    FILE *f_vector = fopen("..\\shared\\vector.txt", "r");
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

    FILE *f_matrix = fopen("..\\shared\\matrix.txt", "r");
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

    FILE *f_vector = fopen("..\\shared\\vector.txt", "r");
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

    return EXIT_SUCCESS;
}

