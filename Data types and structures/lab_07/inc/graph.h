#ifndef LAB_07_GRAPH_H
#define LAB_07_GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int n;                   // количество вершин
    int **data;              // матрица смежности (длины ребер)
} graph_t;

graph_t *create_graph(int n);

graph_t *input_graph_from_file(FILE *f, int comment);

void free_graph(graph_t *graph);

void print_graph_like_matrix(graph_t *graph);

void print_graph_like_dot(FILE *f, graph_t *graph);

void find_distances(int start_top, int max_distance, graph_t *graph, int *dist_array, int *tops_array);

graph_t *copy_graph(graph_t *graph);

long long int memory_graph(int count_elems);

#endif //LAB_07_GRAPH_H
