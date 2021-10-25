/*
 * 0 - выход (если есть какие-то данные, то спрашивать не нужно ли их сохранить)
 * 1 - Ввести матрицу с клавиатуры                                                    +
 * 2 - Считать матрицу из файла                                                       +
 * 3 - Ввести вектор с клавиатуры                                                     +
 * 4 - Считать вектор из файла                                                        +
 * 5 - Сгенерировать матрицу
 * 6 - Сгенерировать вектор
 * 7 - Сохранить матрицу в файл                                                       +
 * 8 - Сохранить вектор в файл                                                        +
 * 9 - Напечатать имеющиеся данные в обычном формате
 * 10 - Напечать имеющиеся данные в специальном формате
 * 11 - Перемножить классическим методом
 * 12 - Перемножить быстрым методом
 * 13 - Очистить имеющиеся данные
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
    else if(SAVE_MATRIX == mode)
        mode_save_matrix(*matrix_read);
    else if(SAVE_VECTOR == mode)
        mode_save_vector(*vector_read);
    else if (PRINT_DATA_IN_CLASSIC_FORMAT == mode)
        mode_print_classic(*matrix_read, *vector_read);

            else if(PRINT_M_FROM_FILE_LIKE_SP_M == mode)
    {
        char filename[MAX_LEN_STR];
        printf("Input filename:");

        if(scanf("%s", filename) != 1)
        {
            printf("Invalid input filename =((((");
            return INVALID_FILENAME;
        }

        return mode_print_matrix_from_file_to_sparse_matrix(filename, (int *)matrix_read);
    }
    else if(PRINT_M_FROM_STDIN_LIKE_SP_M == mode)
    {
        return mode_print_matrix_from_stdin_to_sparse_matrix((int *)matrix_read);
    }
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
               "     0 - EXIT\n"
               "     1 - Input matrix from keyboard\n"
               "     2 - Input matrix from file\n"
               "     3 - Input vector from keyboard\n"
               "     4 - Input vector from file\n"
               "     7 - Save matrix\n"
               "     8 - Save vector\n"
               "     1 - Input matrix from file, convert to a sparse format and print result\n"
               "     2 - Input matrix from stdin, convert to a sparse format and print result\n"
               "     3 - Multiply sparse matrix and sparse vector\n"
               "     4 - Multiply usual matrix and usual vector\n"
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
