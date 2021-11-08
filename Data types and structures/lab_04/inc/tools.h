#ifndef LAB_04_TOOLS_H
#define LAB_04_TOOLS_H

#define INPUT_ONE_ELEM 1
#define EMPTY_STACK 0

#define INVALID_INPUT_SIZE_STACK 10
#define STACKS_ALREADY_CREATE 11
#define FULL_STACK 12
#define STACKS_IS_NOT_CREATE 13
#define INVALID_INPUT_ELEM 14

#define MAX_COUNT_FREE_ADDRESSES 1000

#define COUNT_FOR_IN_REPORT 10000
#define MAX_SIZE_OF_STACK 1000
#define COUNT_FOR_ONE_MEA 100
#define PRINT_ 100
#define COEF 1000

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

typedef struct
{
    int count_add;
    Node_t *data[MAX_COUNT_FREE_ADDRESSES];
} free_addresses_t;

typedef struct
{
    long double static_stack_del_time;
    long double linked_list_stack_del_time;
    long double static_stack_add_time;
    long double linked_list_stack_add_time;
    long double static_stack_pal_time;
    long double linked_list_stack_pal_time;
    long unsigned static_stack_memory;
    long unsigned linked_list_stack_memory;
} report_t;

typedef struct
{
    int count_reports;
    int *sizes;
    report_t *data;
} reports_t;

void clean_stdin(void);

void generate_stack(int size);

#endif //LAB_04_TOOLS_H
