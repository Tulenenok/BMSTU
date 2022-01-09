#ifndef EXAM_PREPARATION_MATRIX_H
#define EXAM_PREPARATION_MATRIX_H

typedef struct
{
    int r;
    int c;
    int *data;
} v_1_matrix_t;

typedef struct
{
    int r;
    int c;
    int **data;
} matrix_t;

v_1_matrix_t *create_matrix_v_1(int r, int c);
void free_matrix_v_1(v_1_matrix_t *m);

matrix_t *create_matrix_v_2(int r, int c);
void free_matrix_v_2(matrix_t *m);

matrix_t *create_matrix_v_3(int r, int c);
void free_matrix_v_3(matrix_t *m);

matrix_t *create_matrix_v_4(int r, int c);
void free_matrix_v_4(matrix_t *m);

void fill_matrix(matrix_t *m);
void print_matrix(matrix_t *m);
void fill_matrix_v_1(v_1_matrix_t *m);
void print_matrix_v_1(v_1_matrix_t *m);

#endif //EXAM_PREPARATION_MATRIX_H
