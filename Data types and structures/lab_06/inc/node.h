#ifndef LAB_06_NODE_H
#define LAB_06_NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NODE_DATA_SPECIFIER "%d"

typedef int node_data_t;
typedef struct node_t
{
    struct node_t *next;
    bool is_data_fill;
    node_data_t data;
} node_t;

node_t *create_node(node_data_t data);

void free_for_node_list(node_t *head);

void insert_data_to_node_list(node_data_t data, size_t index, node_t *head);

node_t *find_data_in_node_list(int *count_cmp, node_data_t data, node_t *head);

void push_back(node_data_t data, node_t **head);

void print_node_list(node_t *head);

#endif //LAB_06_NODE_H
