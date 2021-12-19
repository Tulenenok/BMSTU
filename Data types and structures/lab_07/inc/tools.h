#ifndef LAB_07_TOOLS_H
#define LAB_07_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INPUT_ONE_ELEM 1
#define MAX_LEN_FILENAME 1000
#define DOT_FILE "..\\results\\graph.dot"
#define GRAPH_FILE "..\\data\\graph.txt"

void clean_stdin(void);

int index_min_elem(int n, int arr[], int n_blocked, int blocked_indexes[]);

int is_elem_in_array(int elem, int n, int arr[]);

void generate_matrix(int c, int r);

int64_t tick(void);

#endif //LAB_07_TOOLS_H
