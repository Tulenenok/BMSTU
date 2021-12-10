#ifndef LAB_06_HASH_TABLE_H
#define LAB_06_HASH_TABLE_H

#include <stdarg.h>

#include "node.h"

typedef node_t* list_node_t;
typedef struct
{
    int count_indexes;
    int count_collision;
    list_node_t *array;
    int (*hash_func)(int n, ...);                  // n - количество параметров
} hash_table_t;

int hash_func_1(int n, ...);

hash_table_t *create_hash_table(int count, int arr_with_data[], int (*_hash_func)(int n, ...), bool comment);

hash_table_t *input_hash_table_from_file(FILE *f, int (*_hash_func)(int n, ...), bool comment);

void insert_to_hash_table(node_data_t data, hash_table_t *table, bool comment);

void print_hash_table(hash_table_t *table);

bool find_in_hash_table(node_data_t data, hash_table_t *table, bool comment);

#endif //LAB_06_HASH_TABLE_H
