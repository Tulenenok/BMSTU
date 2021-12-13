#include "../inc/time_memory.h"
#include "time.h"

int64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
    "rdtsc\n"
    "movl %%edx, %0\n"
    "movl %%eax, %1\n"
    : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

int time_find_tree(int count_elems, int data, tree_node_t *tree)
{
    int c = 0;
    int64_t t1b = tick();
    find(&c, tree, data, cmp_int);
    int64_t t1e = tick();

    return (int)(t1e - t1b);
}

int count_cmp_find_tree(int count_elems, int data, tree_node_t *tree)
{
    int c = 0;
    find(&c, tree, data, cmp_int);

    return c;
}

int count_cmp_find_abl_tree(int count_elems, int data, abl_node_t *tree)
{
    int c = 0;
    find_for_abl_tree(&c, tree, data);

    return c;
}

int count_cmp_hash_table(int count_elems, int data, hash_table_t *table)
{
    int c = 0;
    find_in_hash_table(&c, data, table, false);

    return c;
}

int find_in_file(int data, char *filename)
{
    FILE *f = fopen(filename, "r");
    int t;
    while(fscanf(f, "%d", &t) == INPUT_ONE_ELEM)
        if(t == data)
        {
            fclose(f);
            return 1;
        }
    fclose(f);
    return 0;
}
int time_find_file(int data, char *filename)
{
    int c = 0;
    int64_t t1b = tick();
    find_in_file(data, filename);
    int64_t t1e = tick();

    return (int)(t1e - t1b);
}

int helper_find_in_file(int *c, int data, char *filename)
{
    FILE *f = fopen(filename, "r");
    int t;
    while(fscanf(f, "%d", &t) == INPUT_ONE_ELEM)
    {
        (*c)++;
        if (t == data)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
int count_cmp_find_file(int data, char *filename)
{
    int c = 0;
    helper_find_in_file(&c, data, filename);

    return c;
}

int time_abl_find_tree(int count_elems, int data, abl_node_t *tree)
{
    int c = 0;
    int64_t t1b = tick();
    find_for_abl_tree(&c, tree, data);
    int64_t t1e = tick();

    return (int)(t1e - t1b);
}

int time_hash_find_table(int count_elems, int data, hash_table_t *table)
{
    int c = 0;
    int64_t t1b = tick();
    find_in_hash_table(&c, data, table, false);
    int64_t t1e = tick();

    return (int)(t1e - t1b) / 2;
}

int time_insert_tree(int new_data, tree_node_t *tree)
{
    int64_t t1b = tick();
    tree_node_t *new_node = create_tree_node(new_data);
    insert(tree, new_node, cmp_int, false);
    int64_t t1e = tick();

    return (int)(t1e - t1b);
}

int time_insert_abl_tree(int new_data, abl_node_t *tree)
{
    int64_t t1b = tick();
    insert_to_abl_tree(new_data, tree);
    int64_t t1e = tick();

    return (int)(t1e - t1b);
}

int time_insert_hash_table(int new_data, hash_table_t *table)
{
    int64_t t1b = tick();
    insert_to_hash_table(new_data, table, false);
    int64_t t1e = tick();

    return (int)(t1e - t1b);
}

int take_data(int count_elems, int data[], char *filename)
{
    FILE *f = fopen(filename, "r");
    if(!f)
        return EXIT_FAILURE;

    for(int i = 0; i < count_elems; i++)
        if(fscanf(f, "%d", &data[i]) != INPUT_ONE_ELEM)
            return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void conduct_for_find(int count_mea, int counts[])
{
    puts("FIND ELEM");
    puts("+-----------------------------------------------------------------------------+");
    puts("|           |     TREE     |    ABL TREE    |    HASH TABLE    |     FILE     |");
    puts("+-----------------------------------------------------------------------------+");
    for(int i = 0; i < count_mea; i++)
    {
        int count_elems = counts[i];

        char filename[80];
        sprintf(filename, "..\\shared\\gen_%d.txt", count_elems);

        int data[count_elems];
        if(take_data(count_elems, data, filename))
            continue;

        int random_elem = data[abs(rand()) % count_elems];

        FILE *f = fopen(filename, "r");
        tree_node_t *tree = create_tree_from_file(f, cmp_int, false);
        rewind(f);
        hash_table_t *table = input_hash_table_from_file(f, hash_func_1, false);
        rewind(f);
        abl_node_t *abl_tree = input_abl_tree_from_file(f);
        fclose(f);

        printf("|   %4d    |     %4d     |    %8d    |    %10d    |    %7d   |\n",
               counts[i],
               time_find_tree(count_elems, random_elem, tree) * count_elems / 1000,
               time_abl_find_tree(count_elems, random_elem, abl_tree) * count_elems / 1000,
               time_hash_find_table(count_elems, random_elem, table) * count_elems / 1000,
               time_find_file(random_elem, filename) * count_elems / 1000);
        puts("+-----------------------------------------------------------------------------+");

        free_abl_tree(abl_tree);
        //       free_table(table);
//        free_bin_search_tree(tree);
    }
}

void conduct_for_insert(int count_mea, int counts[])
{
    puts("INSERT ELEM");
    puts("+--------------------------------------------------------------+");
    puts("|           |     TREE     |    ABL TREE    |    HASH TABLE    |");
    puts("+--------------------------------------------------------------+");
    for(int i = 0; i < count_mea; i++)
    {
        int count_elems = counts[i];

        char filename[80];
        sprintf(filename, "..\\shared\\gen_%d.txt", count_elems);

        int data[count_elems];
        if(take_data(count_elems, data, filename))
            continue;

        int random_elem = abs(rand());

        FILE *f = fopen(filename, "r");
        tree_node_t *tree = create_tree_from_file(f, cmp_int, false);
        rewind(f);
        hash_table_t *table = input_hash_table_from_file(f, hash_func_1, false);
        rewind(f);
        abl_node_t *abl_tree = input_abl_tree_from_file(f);
        fclose(f);

        printf("|   %4d    |     %4d     |    %8d    |    %10d    |\n",
               counts[i],
               time_insert_tree(random_elem, tree) * count_elems / 1000,
               time_insert_abl_tree(random_elem, abl_tree) * count_elems / 1000,
               time_insert_hash_table(random_elem, table) * count_elems / 1000);
        puts("+--------------------------------------------------------------+");

        free_abl_tree(abl_tree);
        //       free_table(table);
//        free_bin_search_tree(tree);
    }
}

void memory_tree(int *memory, tree_node_t *tree)
{
    if (tree == NULL)
        return;
    memory_tree(memory, tree->left);
    memory_tree(memory, tree->right);

    *memory += sizeof(*tree);
}

void memory_abl_tree(int *memory, abl_node_t *tree)
{
    if (tree == NULL)
        return;
    memory_abl_tree(memory, tree->left);
    memory_abl_tree(memory, tree->right);

    *memory += sizeof(*tree);
}

int size_of_node_list(node_t *n)
{
    int m = 0;
    for(node_t  *cur = n; cur; cur = cur->next)
        m += sizeof(*cur);
    return m;
}
void memory_table(int *memory, hash_table_t *table)
{
    for(int i = 0 ; i < table->count_indexes; i++)
        *memory += size_of_node_list(table->array[i]);
    *memory += sizeof(int) * 2;
}

int memory_file(const char* file_name){
    int64_t _file_size = 0;
    FILE* fd = fopen(file_name, "rb");
    if(fd == NULL){
        _file_size = -1;
    }
    else{
        while(getc(fd) != EOF)
            _file_size++;
        fclose(fd);
    }
    return (int)_file_size;
}

void conduct_for_memory(int count_mea, int counts[])
{
    puts("MEMORY");
    puts("+-----------------------------------------------------------------------------+");
    puts("|           |      TREE      |    ABL TREE    |    HASH TABLE    |     FILE     |");
    puts("+-----------------------------------------------------------------------------+");
    for(int i = 0; i < count_mea; i++)
    {
        int count_elems = counts[i];

        char filename[80];
        sprintf(filename, "..\\shared\\gen_%d.txt", count_elems);

        FILE *f = fopen(filename, "r");
        tree_node_t *tree = create_tree_from_file(f, cmp_int, false);
        rewind(f);
        hash_table_t *table = input_hash_table_from_file(f, hash_func_1, false);
        rewind(f);
        abl_node_t *abl_tree = input_abl_tree_from_file(f);
        fclose(f);

        int t, abl_t, tab;
        memory_tree(&t, tree);
        memory_table(&tab, table);
        memory_abl_tree(&abl_t, abl_tree);
        printf("|   %6d    |     %4d     |    %8d    |    %10d    |    %7d   |\n",
               counts[i],
               t * count_elems / 100,
               t * count_elems / 100,
               tab * count_elems / 100,
               memory_file(filename) * count_elems / 100);
        puts("+-----------------------------------------------------------------------------+");

        free_abl_tree(abl_tree);
    }
}

void conduct_for_count_cmp(int count_mea, int counts[])
{
    puts("COUNT CMP");
    puts("+-----------------------------------------------------------------------------+");
    puts("|           |     TREE     |    ABL TREE    |    HASH TABLE    |     FILE     |");
    puts("+-----------------------------------------------------------------------------+");
    for(int i = 0; i < count_mea; i++)
    {
        int count_elems = counts[i];

        char filename[80];
        sprintf(filename, "..\\shared\\gen_%d.txt", count_elems);

        int data[count_elems];
        if(take_data(count_elems, data, filename))
            continue;

        int random_elem = data[abs(rand()) % count_elems];

        FILE *f = fopen(filename, "r");
        tree_node_t *tree = create_tree_from_file(f, cmp_int, false);
        rewind(f);
        hash_table_t *table = input_hash_table_from_file(f, hash_func_1, false);
        rewind(f);
        abl_node_t *abl_tree = input_abl_tree_from_file(f);
        fclose(f);

        printf("|   %4d    |     %4d     |    %8d    |    %10d    |    %7d   |\n",
               counts[i],
               count_cmp_find_tree(count_elems, random_elem, tree)  * count_elems / 100,
               count_cmp_find_abl_tree(count_elems, random_elem, abl_tree),
               count_cmp_hash_table(count_elems, random_elem, table),
               count_cmp_find_file(random_elem, filename));
        puts("+-----------------------------------------------------------------------------+");

        free_abl_tree(abl_tree);
        //       free_table(table);
//        free_bin_search_tree(tree);
    }
}

void create_report(int count_mea, int counts[])
{
    srand(time(NULL));

    conduct_for_find(count_mea, counts);
//    conduct_for_insert(count_mea, counts);
    conduct_for_memory(count_mea, counts);
    conduct_for_count_cmp(count_mea, counts);
}