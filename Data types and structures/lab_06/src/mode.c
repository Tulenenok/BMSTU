#include "../inc/mode.h"
#include "../inc/tools.h"

 // дописать динамическое считывание имени файла
 void mode_input(tree_node_t **bin_search_tree, hash_table_t **table)
 {
    if(NULL != *bin_search_tree)
    {
        puts("INPUT DATA ---> FAILURE (data was input yet)");
        return ;
    }

     char *filename = "C:\\projects\\C\\TSD\\lab_06\\shared\\data.txt";
     FILE *f = fopen(filename, "r");
     if (!f)
     {
         puts("Error with file");
         return ;
     }

     *bin_search_tree = create_tree_from_file(f, cmp_int, false);
     if(!*bin_search_tree)
         puts("INPUT BIN SEARCH TREE FROM FILE ---> FAILURE");
     else
         puts("INPUT BIN SEARCH TREE FROM FILE ---> SUCCESS");

     rewind(f);

     *table = input_hash_table_from_file(f, hash_func_1, false);
     if(!*table)
         puts("INPUT HASH TABLE FROM FILE ---> FAILURE");
     else
         puts("INPUT HASH TABLE FROM FILE ---> SUCCESS");

     fclose(f);
 }

void mode_print(tree_node_t *tree, hash_table_t *table)
{
    if(NULL == tree)
    {
        puts("Empty, nothing to print");
        return ;
    }
    puts("\n                                  BIN SEARCH TREE");
    puts("--------------------------------------------------------------------------------------------------");
    print_bin_search_tree(tree, 0, 0);
    puts("--------------------------------------------------------------------------------------------------");

    puts("\n                                     HASH TABLE");
    puts("--------------------------------------------------------------------------------------------------");
    print_hash_table(table);
    puts("--------------------------------------------------------------------------------------------------");
}

void mode_free_trees(tree_node_t *bin_search_tree)
{
    free_bin_search_tree(bin_search_tree);
}

void mode_insert_elems(tree_node_t **bin_search_tree, hash_table_t **table)
{
    tree_data_t new_data;

    printf("Input data of new element (int number):");
    if(INPUT_ONE_ELEM != scanf(TREE_DATA_SPECIFIER, &new_data))
    {
        puts("Invalid input data");
        return ;
    }

    int count_cmp = 0;
    tree_node_t *rc = find(&count_cmp, *bin_search_tree, new_data, cmp_int);
    if(NULL != rc)
    {
        printf("INSERT element ----> FAILURE (such an element already exists)");
        return ;
    }

    tree_node_t *new_node = create_tree_node(new_data);
    *bin_search_tree = insert(*bin_search_tree, new_node, cmp_int, true);

    insert_to_hash_table(new_data, *table, true);
}

void mode_find_elem(tree_node_t *bin_search_tree, hash_table_t *table)
{
    if(NULL == bin_search_tree)
    {
        puts("FIND ELEM ---> FAILURE (tree is empty)");
        return ;
    }

    int find_data;
    printf("Input data, that you want to find:");
    if(INPUT_ONE_ELEM != scanf(TREE_DATA_SPECIFIER, &find_data))
    {
        puts("Invalid input data");
        return ;
    }

    int count_cmp;
    tree_node_t *result_of_find = find(&count_cmp, bin_search_tree, find_data, cmp_int);
    if(NULL == result_of_find)
    {
        puts("FIND IN TREE ---> FAILURE");
        puts("Node with this data was not find\n");
    } else
    {
        puts("FIND IN TREE ---> SUCCESS");
        printf("Count of cmp = %d", count_cmp);

        puts("\n                                  FIND TREE");
        puts("--------------------------------------------------------------------------------------------------");
        print_bin_search_tree(result_of_find, 0, 0);
        puts("--------------------------------------------------------------------------------------------------\n");
    }

    if(find_in_hash_table(find_data, table, true))
        puts("FIND IN TABLE ---> SUCCESS");
    else
        puts("FIND IN TABLE ---> FAILURE");
}
