/*
 * 0 - выход (если есть какие-то данные, то спрашивать не нужно ли их сохранить)
 * 1 - Ввести матрицу с клавиатуры                                                    +
 * 2 - Считать матрицу из файла                                                       +
 * 3 - Ввести вектор с клавиатуры                                                     +
 * 4 - Считать вектор из файла                                                        +
 * 5 - Сгенерировать матрицу                                                          +
 * 6 - Сгенерировать вектор                                                           +
 * 7 - Сохранить матрицу в файл                                                       +
 * 8 - Сохранить вектор в файл                                                        +
 * 9 - Напечатать имеющиеся данные в обычном формате                                  +
 * 10 - Напечать имеющиеся данные в специальном формате                               +
 * 11 - Перемножить классическим методом                                              +
 * 12 - Перемножить быстрым методом                                                   +
 * 13 - Напечать отчет по памяти и времени
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "inc/modes.h"
#include "inc/tools.h"
#include "inc/index_matrix.h"

#define INVALID_FILENAME 3


int menu(mode_t mode, bool *matrix_read, bool *vector_read)
{
    int rc;

    if(INPUT_MATRIX_FROM_KEYBOARD == mode)
        rc = mode_input_matrix_from_keyboard(matrix_read);
    else if(INPUT_MATRIX_FROM_FILE == mode)
        rc = mode_input_matrix_from_file(matrix_read);
    else if(INPUT_VECTOR_FROM_KEYBOARD == mode)
        rc = mode_input_vector_from_keyboard(vector_read);
    else if(INPUT_VECTOR_FROM_FILE == mode)
        rc = mode_input_vector_from_file(vector_read);
    else if(GENERATE_MATRIX == mode)
        rc = mode_generate_matrix(matrix_read);
    else if(GENERATE_VECTOR == mode)
        rc = mode_generate_vector(vector_read);
    else if(SAVE_MATRIX == mode)
        mode_save_matrix(*matrix_read);
    else if(SAVE_VECTOR == mode)
        mode_save_vector(*vector_read);
    else if(PRINT_DATA_IN_CLASSIC_FORMAT == mode)
        mode_print_classic(*matrix_read, *vector_read);
    else if(PRINT_DATA_IN_SPARSE_FORMAT == mode)
        mode_print_sparse(*matrix_read, *vector_read);
    else if(MULTIPLY_SPARSE_METHOD == mode)
        mode_multiply_sparse_method(*matrix_read, *vector_read);
    else if(MULTIPLY_CLASSIC_METHOD == mode)
        mode_multiply_classic_method(*matrix_read, *vector_read);
    return EXIT_SUCCESS;
}

int main(void) {
    setbuf(stdout, NULL);

    int rc = 0;
    bool is_matrix_input = false;
    bool is_vector_input = false;

 //   clean_directory(SHARED_DIRECTORY);

    while(!rc)
    {
        printf("Menu:\n"
               "     0  - EXIT\n"
               "     1  - Input matrix from keyboard\n"
               "     2  - Input matrix from file\n"
               "     3  - Input vector from keyboard\n"
               "     4  - Input vector from file\n"
               "     5  - Generate matrix\n"
               "     6  - Generate vector\n"
               "     7  - Save matrix\n"
               "     8  - Save vector\n"
               "     9  - Print matrix and vector in classic format\n"
               "     10 - Print matrix and vector in sparse format\n"
               "     11 - Multiply matrix and vector use sparse method\n"
               "     12 - Multiply matrix and vector use classic method\n"
               "\nInput command >>>");

        mode_t mode = EXIT;
        if(1 != scanf("%d", &mode))
        {
            printf("Input mode:     ----> FAILURE\n");
            continue;
        }

        if (mode == EXIT)
            break;

        printf("\n");
        rc = menu(mode, &is_matrix_input, &is_vector_input);
        printf("\n");
    }
    return rc;
}
