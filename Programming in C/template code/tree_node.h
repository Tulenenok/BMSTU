#ifndef _TREE_NODE_H
#define _TREE_NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
    void *data;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

tree_node_t *create_tree_node(void *data);
tree_node_t *insert(tree_node_t *new_elem, tree_node_t *head, int (*cmp_data)(void *, void *));
void print_tree_node(tree_node_t *node, void *arg);

tree_node_t *find(tree_node_t *node, tree_node_t *head, int (*cmp_data)(void *, void *));
tree_node_t *find_with_while(tree_node_t *node, tree_node_t *head, int (*cmp_data)(void *, void *));

void pre_order(tree_node_t *head, void (*action)(tree_node_t *, void *), void *arg);
void in_order(tree_node_t *head, void (*action)(tree_node_t *, void *), void *arg);
void post_order(tree_node_t *head, void (*action)(tree_node_t *, void *), void *arg);

void to_dot_help_func(struct tree_node *tree, void *arg);
void export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree);

void free_tree_node(tree_node_t *node, void *arg);
void free_tree(tree_node_t *head);

#endif
