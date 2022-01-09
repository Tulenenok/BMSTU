#ifndef EXAM_PREPARATION_DYNAMIC_EXPAND_ARRAY_H
#define EXAM_PREPARATION_DYNAMIC_EXPAND_ARRAY_H

typedef struct
{
    int n;
    int size_of_buf;
    int step;
    int *data;
} dynamic_expand_array_t;

dynamic_expand_array_t *create_dyn_exp_array(int _step);

void free_dyn_exp_array(dynamic_expand_array_t *arr);

int push_dyn_exp_array(dynamic_expand_array_t *arr, int new_elem);

int pop_dyn_exp_array(dynamic_expand_array_t *arr, int index);

void print_dyn_exp_array(dynamic_expand_array_t *arr);

int go_dyn_exp_array(void);

#endif //EXAM_PREPARATION_DYNAMIC_EXPAND_ARRAY_H
