/*
 * Двоичным деревом поиска называют дерево, все вершины которого упорядочены,
 * каждая вершина имеет не более двух потомков (назовём их левым и правым),
 * и все вершины, кроме корня, имеют родителя.
 */

#ifndef LAB_06_BINARY_SEARCH_TREE_H
#define LAB_06_BINARY_SEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TREE_DATA_SPECIFIER "%d"

typedef int tree_data_t;

typedef struct tree_node tree_node_t;
struct tree_node
{
    tree_data_t data;
    struct tree_node *left;
    struct tree_node *right;
};

tree_node_t *create_tree_node(tree_data_t data);

tree_node_t *create_tree_from_file(FILE *f, int (*cmp)(tree_data_t, tree_data_t), bool comment_flag);

tree_node_t *insert(tree_node_t *tree, tree_node_t *new_node, int (*cmp)(tree_data_t, tree_data_t), bool comment_flag);

tree_node_t *find(int *count_cmp, tree_node_t *tree, tree_data_t data, int (*cmp)(tree_data_t, tree_data_t));

void print(tree_node_t *p,int level);

void print_bin_search_tree(tree_node_t *head, int down, int strelochka);

void free_bin_search_tree(tree_node_t *tree);

#endif //LAB_06_BINARY_SEARCH_TREE_H
