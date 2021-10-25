#ifndef LAB_03_NODE_H
#define LAB_03_NODE_H

#include <stdio.h>
#include <stdlib.h>

#define ONLY_NULL_ELEM_IN_COLUMN -1

typedef struct Node_t
{
    struct Node_t *next;
    int data;
} Node_t;

void malloc_for_node_list(size_t count_elems, Node_t **head);

void free_for_node_list(Node_t *head);

void insert_data_to_node_list_if_data_empty(int data, size_t index, Node_t *head);

void print_node_list(FILE *f, Node_t *head);

#endif //LAB_03_NODE_H
