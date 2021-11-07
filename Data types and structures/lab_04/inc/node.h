#ifndef LAB_03_NODE_H
#define LAB_03_NODE_H

#include <stdio.h>
#include <stdlib.h>

#define ONLY_NULL_ELEM_IN_COLUMN -1

typedef struct Node_t
{
    struct Node_t *next;
    char data;
} Node_t;

void malloc_for_node_list(size_t count_elems, Node_t **head);

void free_for_node_list(Node_t *head);

char take_data_by_index(int index, Node_t *head);

Node_t *add_first_elem_to_node_list(char new_elem, Node_t *head);

Node_t *del_first_elem_from_node_list(Node_t *head);

void insert_data_to_node_list(char data, size_t index, Node_t *head);

void print_node_list(Node_t *head);

#endif //LAB_03_NODE_H
