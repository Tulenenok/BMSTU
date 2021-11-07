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

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

typedef struct
{
    int count_add;
    Node_t *data[MAX_COUNT_FREE_ADDRESSES];
} free_addresses_t;

void clean_stdin(void);

#endif //LAB_04_TOOLS_H
