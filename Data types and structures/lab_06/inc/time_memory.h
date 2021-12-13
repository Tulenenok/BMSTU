#ifndef LAB_06_TIME_MEMORY_H
#define LAB_06_TIME_MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../inc/tools.h"
#include "../inc/abl_tree.h"
#include "../inc/hash_table.h"
#include "../inc/binary_search_tree.h"

#define COUNT_COLS 4

typedef struct
{
    int count_measures;
    int *counts;
    int insert_tacts[COUNT_COLS];
    int find_tacts[COUNT_COLS];
    int memory[COUNT_COLS];
    int count_cmp[COUNT_COLS];
} report_t;

void create_report(int count_mea, int counts[]);

#endif //LAB_06_TIME_MEMORY_H
