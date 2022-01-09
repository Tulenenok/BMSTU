#include <stdlib.h>
#include <stdio.h>

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

/// Вариант 1
/*
 * Матрица - одномерный динамический массив
 * +
 * +
 * +
 * -
 * -
 */

v_1_matrix_t *create_matrix_v_1(int r, int c)
{
    v_1_matrix_t *m = malloc(sizeof(v_1_matrix_t));
    if(!m)
        return NULL;

    m->r = r;
    m->c = c;

    m->data = malloc(r * c * sizeof(int));
    if(m->data)
        return m;

    free(m);
    return NULL;
}

void free_matrix_v_1(v_1_matrix_t *m)
{
    free(m->data);
    free(m);
}

void fill_matrix_v_1(v_1_matrix_t *m)
{
    for(int i = 0; i < m->r; i++)
        for(int j = 0; j < m->c; j++)
            m->data[i * m->c + j] = 1;
}

void print_matrix_v_1(v_1_matrix_t *m)
{
    for(int i = 0; i < m->r; i++, printf("\n"))
        for(int j = 0; j < m->c; j++)
            printf("%d ", m->data[i * m->c + j]);
}

/// Вариант 2

void free_matrix_v_2(matrix_t *m)
{
    for(int i = 0; i < m->r; i++)
        free(m->data[i]);
    free(m->data);
    free(m);
}

matrix_t *create_matrix_v_2(int r, int c)
{
    matrix_t *m = calloc(1, sizeof(matrix_t));
    if(!m)
        return NULL;
    m->r = r;
    m->c = c;

    m->data = calloc(m->r,  sizeof(int *));
    if(!m->data)
    {
        free(m);
        return NULL;
    }

    for(int i = 0; i < m->r; i++)
    {
        m->data[i] = calloc(m->c, sizeof(int));
        if(!m->data) {
            free_matrix_v_2(m);
            return NULL;
        }
    }

    return m;
}

void fill_matrix_v_2(matrix_t *m)
{
    for(int i = 0; i < m->r; i++)
        for(int j = 0; j < m->c; j++)
            m->data[i][j] = 2;
}

void print_matrix_v_2(matrix_t *m)
{
    for(int i = 0; i < m->r; i++, printf("\n"))
        for(int j = 0; j < m->c; j++)
            printf("%d ", m->data[i][j]);
}

/// Вариант 3
matrix_t *create_matrix_v_3(int r, int c)
{
    matrix_t *m = calloc(1, sizeof(matrix_t));
    if(!m)
        return NULL;
    m->r = r;
    m->c = c;

    m->data = calloc(m->r + 1, sizeof(int *));
    if(!m->data)
    {
        free(m);
        return NULL;
    }

    m->data[0] = calloc(m->r * m->c, sizeof(int));
    if(!m->data[0])
    {
        free(m->data);
        free(m);
        return NULL;
    }

    m->data[m->r] = m->data[0];

    for(int i = 0; i < m->r; i++)
        m->data[i] = m->data[m->r] + i * m->c;
    return m;
}

void free_matrix_v_3(matrix_t *m)
{
    free(m->data[m->r]);
    free(m->data);
    free(m);
}


int main(void)
{
    matrix_t *m = create_matrix_v_3(3, 3);
    fill_matrix_v_2(m);
    print_matrix_v_2(m);
    free_matrix_v_3(m);
}

