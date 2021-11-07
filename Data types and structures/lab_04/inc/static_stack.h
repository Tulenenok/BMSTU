#ifndef LAB_04_STATIC_STACK_H
#define LAB_04_STATIC_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE_OF_STACK 1000

typedef struct
{
     int max_count_elems;
     int count_elems;
     char data[MAX_SIZE_OF_STACK];
} static_stack_t;

static_stack_t create_static_stack(int size);

int add_elem_to_static_stack(char new_elem, static_stack_t *stack);

void del_elem_from_static_stack(static_stack_t *stack);

void print_static_stack(static_stack_t *stack);

void print_static_stack_like_word(static_stack_t *stack);

bool is_palindrome_static_stack(static_stack_t *stack);

#endif
