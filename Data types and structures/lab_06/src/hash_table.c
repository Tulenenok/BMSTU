#include "../inc/hash_table.h"
#include "../inc/tools.h"

#define MAX_COUNT_LOOP 100

int hash_func_1(int n, ...)
{
    va_list vl;
    va_start(vl, n);

    int elem = abs(va_arg(vl, int));
    int count_elems_in_file = va_arg(vl, int);

    va_end(vl);
    return elem % count_elems_in_file;
}

hash_table_t *create_hash_table(int count_elems, int count_indexes, int arr_with_data[], int (*_hash_func)(int n, ...), bool comment)
{
    hash_table_t *new_table = malloc(sizeof(hash_table_t));

    new_table->count_indexes = count_indexes != 1 ? count_indexes : count_indexes + 1;
    new_table->count_collision = 0;
    new_table->array = malloc(new_table->count_indexes * sizeof(list_node_t));
    new_table->hash_func = _hash_func;

    for(int i = 0; i < new_table->count_indexes; i++)
    {
        new_table->array[i] = malloc(sizeof(list_node_t));
        new_table->array[i]->is_data_fill = false;
        new_table->array[i]->next = NULL;
    }

    for(int i = 0; i < count_elems; i++)
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

    hash_table_t *new_table = create_hash_table(count_unique_elems, count_unique_elems, arr, hash_func_1, comment);
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
    printf("        avg count cmp    = %lf\n", average_count_of_cmp(table));
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

bool find_in_hash_table(int *count_cmp, node_data_t data, hash_table_t *table, bool comment)
{
    int hash = hash_func_1(2, data, table->count_indexes);
    if(hash >= table->count_indexes || hash < 0)
    {
        if(comment)
            printf("ERROR ---> invalid hash for element %d\n Elem was not find\n", data);
        return false;
    }

    node_t *try_find = find_data_in_node_list(count_cmp, data, table->array[hash]);
    if(NULL == try_find)
    {
        if(comment)
            printf("Value %d was not find\nCount of cmp = %d\n", data, *count_cmp);
        return false;
    }

    if(comment)
        printf("Value %d was found (index in table %d)\nCount of cmp = %d\n", data, hash, *count_cmp);

    return true;
}

double average_count_of_cmp(hash_table_t *table)
{
    int count_elems = 0, count_cmp = 0;
    for(int i = 0; i < table->count_indexes; i++)
    {
        list_node_t t = table->array[i];
        for (int j = 1; t && t->is_data_fill == true; t = t->next, count_elems++, j++)
            count_cmp += j;
    }
    return (double)count_cmp / count_elems;
}

int sum_of_ar_pr(int x)
{
    int sum = 0;
    for(int i = 1; i <= x; i++)
        sum += i;
    return sum;
}

void print_array(int n, int arr[], char *name)
{
    printf("%s\n", name);
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

double avg_count_cmp_for_array(int count_indexes, int count_elems, int arr_with_data[], int (*hash_func)(int n, ...))
{
    int *index_arr = calloc(count_indexes, sizeof(int));
    for(int i = 0; i < count_elems; i++)
        index_arr[hash_func_1(2, arr_with_data[i], count_indexes)]++;

    int sum_cmp = 0;
    for(int i = 0; i < count_indexes; i++)
        sum_cmp += sum_of_ar_pr(index_arr[i]);

    free(index_arr);

    return (double)sum_cmp / count_elems;
}

hash_table_t *change_table(double new_max_avg_count_cmp, hash_table_t *table)
{
    int count_elems = 0, count_cmp = 0;
    int arr_with_data[MAX_COUNT_ELEMS];

    for(int i = 0; i < table->count_indexes; i++)
    {
        list_node_t t = table->array[i];
        for (int j = 1; t && t->is_data_fill == true; t = t->next, count_cmp += j, j++)
            arr_with_data[count_elems++] = t->data;
    }

    double now_avg = (double)count_cmp / count_elems;
    int new_count_indexes = table->count_indexes;

    while(now_avg > new_max_avg_count_cmp)
        now_avg = avg_count_cmp_for_array(++new_count_indexes, count_elems, arr_with_data, table->hash_func);

    hash_table_t *new_table = create_hash_table(count_elems, new_count_indexes, arr_with_data, table->hash_func, false);

    return new_table;
}

void free_table(hash_table_t *table)
{
    for(int i = 0; i < table->count_indexes; i++)
        free_for_node_list(table->array[i]);

    free(table);
}
