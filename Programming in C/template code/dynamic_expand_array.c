#include "dynamic_expand_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ALLOC_ERROR 100

dynamic_expand_array_t *create_dyn_exp_array(int _step)
{
    dynamic_expand_array_t *new = malloc(sizeof(dynamic_expand_array_t));
    if(!new)
        return NULL;

    new->n = 0;
    new->size_of_buf = 0;
    new->step = _step;
    new->data = NULL;

    return new;
}

void free_dyn_exp_array(dynamic_expand_array_t *arr)
{
    free(arr->data);
    free(arr);
}

int push_dyn_exp_array(dynamic_expand_array_t *arr, int new_elem)
{
    if(arr->data == NULL)
    {
        arr->data = malloc(sizeof(int));
        if(!arr->data)
            return ALLOC_ERROR;

        arr->size_of_buf = 1;
        arr->data[0] = new_elem;
        arr->n = 1;

        return EXIT_SUCCESS;
    }

    if(arr->n >= arr->size_of_buf)
    {
        int *t = realloc(arr->data, arr->size_of_buf * arr->step);
        if(!t)
            return ALLOC_ERROR;

        arr->data = t;
        arr->size_of_buf *= arr->step;
    }

    arr->data[arr->n] = new_elem;
    arr->n++;

    return EXIT_SUCCESS;
}

int pop_dyn_exp_array(dynamic_expand_array_t *arr, int index)
{
    assert(arr->n > 0 && index < arr->n);

    int t = arr->data[index];
    memmove(arr->data + index, arr->data + index + 1, (arr->n - index - 1) * sizeof(int));

    arr->n--;
    return t;
}

void print_dyn_exp_array(dynamic_expand_array_t *arr)
{
    for(int i = 0; i < arr->n; i++)
        printf("%d ", arr->data[i]);

    printf("\n");
}

int go_dyn_exp_array(void)
{
    dynamic_expand_array_t *arr = create_dyn_exp_array(2);
    push_dyn_exp_array(arr, 5);
    print_dyn_exp_array(arr);

    push_dyn_exp_array(arr, 2);
    print_dyn_exp_array(arr);

    push_dyn_exp_array(arr, 1);
    print_dyn_exp_array(arr);

    pop_dyn_exp_array(arr, 2);
    print_dyn_exp_array(arr);

    pop_dyn_exp_array(arr, 1);
    print_dyn_exp_array(arr);

    free_dyn_exp_array(arr);
}
