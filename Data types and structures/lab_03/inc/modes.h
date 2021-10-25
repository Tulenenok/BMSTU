#ifndef LAB_03_MODES_H
#define LAB_03_MODES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR_WITH_FILE 2

typedef enum
{
    EXIT = 0,
    INPUT_MATRIX_FROM_KEYBOARD = 1,
    INPUT_MATRIX_FROM_FILE = 2,
    INPUT_VECTOR_FROM_KEYBOARD = 3,
    INPUT_VECTOR_FROM_FILE = 4,
    SAVE_MATRIX = 7,
    SAVE_VECTOR = 8,
    PRINT_DATA_IN_CLASSIC_FORMAT = 9,
    PRINT_M_FROM_FILE_LIKE_SP_M = 10,
    PRINT_M_FROM_STDIN_LIKE_SP_M = 11,
    MULTIPLY_SPARSE = 3,
    MULTIPLY_USUAL = 4
} mode_t;

int mode_print_matrix_from_file_to_sparse_matrix(char filename[], int *num_matrix);

int mode_print_matrix_from_stdin_to_sparse_matrix(int *num_matrix);

int mode_multiply_sparse();

int mode_input_matrix_from_file(bool *is_matrix_input);

int mode_input_matrix_from_keyboard(bool *is_matrix_input);

int mode_input_vector_from_keyboard(bool *is_vector_input);

int mode_input_vector_from_file(bool *is_vector_input);

void mode_save_matrix(bool is_matrix_input);

void mode_save_vector(bool is_vector_input);

void mode_print_classic(bool is_matrix_input, bool is_vector_input);

#endif //LAB_03_MODES_H
