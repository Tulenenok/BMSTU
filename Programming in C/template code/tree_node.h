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


#endif
