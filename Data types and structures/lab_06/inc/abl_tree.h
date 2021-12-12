/*
 * АВЛ-дерево ― сбалансированное двоичное дерево поиска.
 * Для каждой его вершины высоты её двух поддеревьев различаются не более чем на 1.
 */

#ifndef LAB_06_ABL_TREE_H
#define LAB_06_ABL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct abl_node abl_node_t;
struct abl_node
{
    int data;
    int height;
    abl_node_t* left;
    abl_node_t* right;
};

abl_node_t *create_abl_node(int _data, int _height, abl_node_t *_left, abl_node_t *_right);

abl_node_t *input_abl_tree_from_file(FILE *f);

abl_node_t *insert_to_abl_tree(int k, abl_node_t *tree);

void free_abl_node(abl_node_t *node);

void free_abl_tree(abl_node_t *tree);

void print_abl_tree(abl_node_t *head, int down, int arrow);

abl_node_t *find_for_abl_tree(int *count_cmp, abl_node_t *tree, int data);

#endif
