#ifndef LIBR
#define LIBR

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    void *next;
    int elem;
} elem_t;

typedef struct
{
    int *first;
    int count;
} array_t;

typedef struct
{
    elem_t *first;
    int count;
} list_t;

void menu(void);
int create_stacks(array_t *arr, list_t *list);
void free_list(list_t *list);
void print_stack(array_t *arr);
void print_list(list_t *list);
int add_array(array_t * arr, int len);
int add_list(list_t *list, int len, array_t *arr);

#endif
