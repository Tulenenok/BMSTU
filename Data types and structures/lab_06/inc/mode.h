#ifndef LAB_06_MODE_H
#define LAB_06_MODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../inc/binary_search_tree.h"
#include "../inc/hash_table.h"
#include "../inc/abl_tree.h"

typedef enum
{
    EXIT = 0,
    INPUT_TREES = 1,
    INSERT_ELEM = 2,
    FIND_ELEM = 3,
    PRINT_TREES = 4,
    CHANGE_TABLE = 5,
    REPORT = 6,
} mode_t;

void mode_input(tree_node_t **bin_search_tree, hash_table_t **table, abl_node_t **abl_tree);

void mode_print(tree_node_t *tree, hash_table_t *table, abl_node_t *abl_tree);

void mode_free(tree_node_t *bin_search_tree, hash_table_t *table, abl_node_t *abl_tree);

void mode_insert_elems(tree_node_t **bin_search_tree, hash_table_t **table, abl_node_t **abl_tree);

void mode_find_elem(tree_node_t *bin_search_tree, hash_table_t *table, abl_node_t *abl_tree);

void mode_change_table(hash_table_t **table);

void mode_report(void);

#endif //LAB_06_MODE_H
