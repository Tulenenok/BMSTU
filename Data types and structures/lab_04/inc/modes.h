#ifndef LAB_04_MODES_H
#define LAB_04_MODES_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../inc/linked_list_stack.h"
#include "../inc/static_stack.h"
#include "../inc/tools.h"

typedef struct
{
  static_stack_t static_stack;
  linked_list_stack_t linked_list_stack;
} stacks_t;

typedef enum
{
  EXIT = 0,
  CREATE_STACKS = 1,
  ADD_FEW_ELEMS = 2,
  DEL_ELEMS = 3,
  PRINT_STACKS = 4,
  IS_PALINDROME = 5,
  PRINT_FREE_ADDRESSES = 6,
  CONDUCT_RESEARCH = 7,
} mode_t;

int mode_create_stacks(bool *is_stacks_create, stacks_t *stacks);

int mode_add_elem_to_stacks(bool is_stacks_create, stacks_t *stacks);

int mode_print_stacks(bool is_stacks_create, stacks_t *stacks);

int mode_del_elems_from_stacks(bool is_stacks_create, stacks_t *stacks, free_addresses_t *free_add);

int mode_is_palindrome(bool is_stacks_create, stacks_t *stacks);

int mode_add_few_elems_to_stacks(bool is_stacks_create, stacks_t *stacks);

void mode_print_free_addresses(free_addresses_t *free_add);

int mode_conduct_research(void);

#endif //LAB_04_MODES_H
