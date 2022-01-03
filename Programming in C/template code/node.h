#ifndef _NODE_H
#define _NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    void *data;
    struct node *next;
} node_t;

struct list_t
{
    node_t *head;
    node_t *tail;
};

node_t *create_node(void *data);
void free_node(node_t *node);
void free_list(node_t *head);

node_t *push_front_node(node_t *new_node, node_t *head);
void push_front_node_2(node_t *new_node, node_t **head);
node_t *push_back_node(node_t *new_node, node_t *head);
int push_after_node(node_t *new_node, node_t *node, node_t *head);
node_t *push_before_node_2(node_t *new_node, node_t *node, node_t *head, void (*swap_data)(void *, void *));
node_t *push_before_node(node_t *new_node, node_t *node, node_t *head);

node_t *pop_node(void *data, node_t *head, int (*cmp_data)(const void *, const void *));

int cmp_int(const void *x, const void *y);
void print_node(node_t *node, void *arg);
void count_elems_in_list(node_t *node, void *arg);
void swap_data(void *x, void *y);

node_t *find_node(void *data, node_t *head, int (*cmp)(const void *, const void *));
void list_apply(node_t *head, void (*action)(node_t *, void *), void *arg);

#endif
