#ifndef LAB_06_TOOLS_H
#define LAB_06_TOOLS_H

#include <stdio.h>
#include <stdlib.h>

#define INPUT_ONE_ELEM 1
#define MAX_LEN_FILE 1000

int cmp_int(int x, int y);

void clean_stdin(void);

int count_elems_in_file(FILE *f);

int is_elem_in_arr(int elem, int l, int r, int arr[]);

int unique_elems_in_file(FILE *f, int arr[]);

#endif //LAB_06_TOOLS_H
