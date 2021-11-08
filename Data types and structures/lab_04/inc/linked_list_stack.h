#ifndef LAB_04_LINKED_LIST_STACK_H
#define LAB_04_LINKED_LIST_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node.h"
#include "tools.h"

typedef struct
{
    int max_count_elems;
    int count_elems;
    Node_t *data;
} linked_list_stack_t;

linked_list_stack_t create_linked_list_stack(int size);

int add_elem_to_linked_list_stack(char new_elem, linked_list_stack_t *stack);

void print_linked_list_stack(linked_list_stack_t *stack);

void del_elem_from_linked_list_stack(linked_list_stack_t *stack, free_addresses_t *free_add);

bool is_palindrome_linked_list_stack(linked_list_stack_t *stack);

long unsigned memory_of_linked_list_stack(linked_list_stack_t *stack);

int fill_linked_list_stack_from_file(char filename[], linked_list_stack_t *stack);

void del_elem_linked_list_stack_help_func(linked_list_stack_t *stack);

void add_elem_linked_list_stack_help_func(char new_elem, linked_list_stack_t *stack);

#endif
