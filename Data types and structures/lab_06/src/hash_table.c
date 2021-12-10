#include "../inc/hash_table.h"
#include "../inc/tools.h"

int hash_func_1(int n, ...)
{
    va_list vl;
    va_start(vl, n);

    int elem = va_arg(vl, int);
    int count_elems_in_file = va_arg(vl, int);

    va_end(vl);
    return elem % count_elems_in_file;
}

hash_table_t *create_hash_table(int count, int arr_with_data[], int (*_hash_func)(int n, ...), bool comment)
{
    hash_table_t *new_table = malloc(sizeof(hash_table_t));

    new_table->count_indexes = count;
    new_table->count_collision = 0;
    new_table->array = malloc(count * sizeof(list_node_t));
    new_table->hash_func = _hash_func;

    for(int i = 0; i < count; i++)
    {
        new_table->array[i] = malloc(sizeof(list_node_t));
        new_table->array[i]->is_data_fill = false;
        new_table->array[i]->next = NULL;
    }

    for(int i = 0; i < count; i++)
        insert_to_hash_table(arr_with_data[i], new_table, comment);

    if(comment)
        puts("CREATE HASH TABLE ---> SUCCESS");

    return new_table;
}

hash_table_t *input_hash_table_from_file(FILE *f, int (*_hash_func)(int n, ...), bool comment)
{
    int count_elems = count_elems_in_file(f);

    if(count_elems == 0)
        return NULL;

    node_data_t *arr = malloc(count_elems * sizeof(int));
    int count_unique_elems = unique_elems_in_file(f, arr);

    hash_table_t *new_table = create_hash_table(count_unique_elems, arr, hash_func_1, true);
    free(arr);

    return new_table;
}

void print_hash_table(hash_table_t *table)
{
    printf("+------------+-------------+\n");
    printf("    Index    |    Value    \n");
    printf("+------------+-------------+\n");
    for(int i = 0; i < table->count_indexes; i++)
    {
        printf("    %2d       |    ", i);
        print_node_list(table->array[i]);
    }
    printf("+--------------------------+\n");
    printf("RESULT: count collisions = %d\n", table->count_collision);
    printf("+--------------------------+\n");
}

void insert_to_hash_table(node_data_t data, hash_table_t *table, bool comment)
{
    int hash = hash_func_1(2, data, table->count_indexes);
    if(hash >= table->count_indexes || hash < 0)
    {
        if(comment)
            printf("ERROR ---> invalid hash for element %d\n Elem was not added\n", data);
        return ;
    }

    if(table->array[hash]->is_data_fill == false)
    {
        table->array[hash]->data = data;
        table->array[hash]->is_data_fill = true;
    }
    else
    {
        push_back(data, &table->array[hash]);
        table->count_collision++;
    }
}

bool find_in_hash_table(node_data_t data, hash_table_t *table, bool comment)
{
    int hash = hash_func_1(2, data, table->count_indexes);
    if(hash >= table->count_indexes || hash < 0)
    {
        if(comment)
            printf("ERROR ---> invalid hash for element %d\n Elem was not find\n", data);
        return false;
    }

    node_t *try_find = find_data_in_node_list(data, table->array[hash]);
    if(NULL == try_find)
    {
        if(comment)
            printf("Value %d was not find\n", data);
        return false;
    }

    if(comment)
        printf("Value %d was found (index in table %d)\n", data, hash);

    return true;
}
