#ifndef LAB_03_TOOLS_H
#define LAB_03_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN_STR 1000

#define INPUT_ONE_ELEM 1

#define INVALID_INPUT_COUNT_ROWS 10
#define INVALID_INPUT_COUNT_COLS 11
#define INVALID_MATRIX 12

#define ALLOCATE_MEMORY_ERROR 100

#define SHARED_DIRECTORY "C:\\projects\\C\\TSD\\lab_03\\shared\\"

void concatenate_strings(char str1[], char str2[], char *result_str);

int input_size_of_matrix(FILE *f, size_t *r, size_t *c, bool print_comments);

int input_matrix_from_file_and_save(FILE *fin, FILE *fout);

int input_vector_from_file_and_save(FILE *fin, FILE *fout);

void print_int_array(FILE *f, size_t n, int a[]);

void print_size_t_array(FILE *f, size_t n, size_t a[]);

int clean_directory(char dirname[]);

int save_matrix_in_file(FILE *f, int *const num_matrix, bool print_comments);

void find_filename_by_name(int n, char filename[]);

int alloc_memory_for_array(int count_elems, size_t size_elem, int **a);

int count_not_null_elems_in_file(FILE *const f, const size_t r, const size_t c, size_t *const count);

int input_matrix(int r, int c);

int input_vector(int r, int c);

int save_vector_to_file(void);

int save_matrix_to_file(void);

#endif //LAB_03_TOOLS_H
