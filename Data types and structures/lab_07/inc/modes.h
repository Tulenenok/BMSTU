#ifndef LAB_07_MODES_H
#define LAB_07_MODES_H

#include <stdio.h>
#include <stdlib.h>
#include "../inc/graph.h"

typedef enum
{
    EXIT = 0,
    INPUT_GRAPH_FROM_FILE = 1,
    INPUT_GRAPH_FROM_STDIN = 2,
    FIND = 3,
    PRINT_GRAPH = 4,
    REPORT = 5,
} mode_t;

void mode_input_graph_from_file(graph_t **graph);

void mode_input_graph_from_stdin(graph_t **graph);

void mode_free(graph_t *graph);

void mode_print_graph(graph_t *graph);

void mode_find(graph_t *graph);

void mode_report();

#endif //LAB_07_MODES_H
