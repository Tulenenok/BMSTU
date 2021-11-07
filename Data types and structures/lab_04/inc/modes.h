#ifndef LAB_04_MODES_H
#define LAB_04_MODES_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../inc/linked_list_stack.h"
#include "../inc/static_stack.h"

typedef struct
{
  static_stack_t static_stack;
  linked_list_stack_t linked_list_stack;
} stacks_t;

typedef enum
{
  EXIT = 0,
  CREATE_STACKS = 1,
  ADD_ELEM = 2,
  DEL_ELEM = 3,
  PRINT_STACKS = 4,
  IS_PALINDROME = 5,
} mode_t;

int mode_create_stacks(bool *is_stacks_create, stacks_t *stacks);

int mode_add_elem_to_stacks(bool is_stacks_create, stacks_t *stacks);

int mode_print_stacks(bool is_stacks_create, stacks_t *stacks);

int mode_del_elem_from_stacks(bool is_stacks_create, stacks_t *stacks);

int mode_is_palindrome(bool is_stacks_create, stacks_t *stacks);

#endif //LAB_04_MODES_H
