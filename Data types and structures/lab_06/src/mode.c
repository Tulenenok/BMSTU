#include "../inc/mode.h"
#include "../inc/tools.h"
#include "../inc/time_memory.h"

 // дописать динамическое считывание имени файла
 void mode_input(tree_node_t **bin_search_tree, hash_table_t **table, abl_node_t **abl_tree)
 {
    if(NULL != *bin_search_tree)
    {
        puts("INPUT DATA ---> FAILURE (data was input yet)");
        return ;
    }

     char *filename = "C:\\projects\\C\\TSD\\lab_06\\shared\\bad_test.txt";
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

     rewind(f);

     *abl_tree = input_abl_tree_from_file(f);
     if(!*abl_tree)
         puts("INPUT ABL TREE FROM FILE ---> FAILURE");
     else
         puts("INPUT ABL TREE FROM FILE ---> SUCCESS");

     fclose(f);
 }

void mode_print(tree_node_t *tree, hash_table_t *table, abl_node_t *abl_tree)
{
    if(NULL == tree)
    {
        puts("Empty, nothing to print");
        return ;
    }
    puts("\n--------------------------------------BIN SEARCH TREE---------------------------------------------");
    print_bin_search_tree(tree, 0, 0);
    puts("--------------------------------------------------------------------------------------------------");

    puts("\n------------------------------------------ABL TREE------------------------------------------------");
    print_abl_tree(abl_tree, 0, 0);
    puts("--------------------------------------------------------------------------------------------------");

    puts("\n-----------------------------------------HASH TABLE-----------------------------------------------");
    print_hash_table(table);
    puts("--------------------------------------------------------------------------------------------------");
}

void mode_free(tree_node_t *bin_search_tree, hash_table_t *table, abl_node_t *abl_tree)
{
    if(bin_search_tree != NULL)
        free_bin_search_tree(bin_search_tree);
    if(table != NULL)
        free_table(table);
    if(abl_tree != NULL)
        free_abl_tree(abl_tree);
}

void mode_insert_elems(tree_node_t **bin_search_tree, hash_table_t **table, abl_node_t **abl_tree)
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
    *abl_tree = insert_to_abl_tree(new_data, *abl_tree);
}

void mode_find_elem(tree_node_t *bin_search_tree, hash_table_t *table, abl_node_t *abl_tree)
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
    puts("\n+-----------------------------------RESULT FIND FOR BIN TREE-------------------------------------+");
    if(NULL == result_of_find)
    {
        puts("Node with this data was not find\n");
        puts("FIND IN TREE ---> FAILURE");
    } else
    {
        printf("Count of cmp = %d", count_cmp);

        puts("\nFIND NEXT PART OF TREE");
        print_bin_search_tree(result_of_find, 0, 0);
        puts("\nFIND IN TREE ---> SUCCESS");
        puts("+------------------------------------------------------------------------------------------------+\n");
    }

    count_cmp = 0;
    abl_node_t *rs_of_find = find_for_abl_tree(&count_cmp, abl_tree, find_data);
    puts("\n+-----------------------------------RESULT FIND FOR ABL TREE-------------------------------------+");
    if(NULL == rs_of_find)
    {
        puts("Node with this data was not find\n");
        puts("FIND IN ABL TREE ---> FAILURE");
    } else
    {
        printf("Count of cmp = %d", count_cmp);

        puts("\nFIND NEXT PART OF TREE");
        print_abl_tree(rs_of_find, 0, 0);
        puts("\nFIND IN ABL TREE ---> SUCCESS");
        puts("+------------------------------------------------------------------------------------------------+\n");
    }

    count_cmp = 0;
    puts("+-----------------------------------RESULT FIND FOR HASH TABLE-----------------------------------+");
    if(find_in_hash_table(&count_cmp, find_data, table, true))
        puts("\nFIND IN TABLE ---> SUCCESS");
    else
        puts("\nFIND IN TABLE ---> FAILURE");
    puts("+------------------------------------------------------------------------------------------------+\n");
}

void mode_change_table(hash_table_t **table) {
    double count_avg = average_count_of_cmp(*table);
    double new_count_of_avg;

    printf("Not average count of cmp in table = %f\n", count_avg);
    printf("Input new average count of cmp (int):");
    if (INPUT_ONE_ELEM != scanf("%lf", &new_count_of_avg))
    {
        printf("Invalid input (must be int number)\n");
        return;
    }

    if (new_count_of_avg < 1) {
        printf("Invalid input ---> (int)avg count of arg can't be < 1\n");
        return;
    }

    hash_table_t *new_table = change_table((double)(int)new_count_of_avg, *table);
    if(new_table == NULL)
    {
        puts("CHANGE TABLE ---> FAILURE");
        return ;
    }

    free_table(*table);
    *table = new_table;

    print_hash_table(new_table);
    puts("CHANGE TABLE ---> SUCCESS");
}

void mode_report(void)
{
    int count_measurements = 0;
    printf("Input count of measurements that you want to do:");
    if(INPUT_ONE_ELEM != scanf("%d", &count_measurements) || count_measurements < 0)
    {
        puts("Invalid input count");
        return ;
    }

    report_t *report = malloc(sizeof(report_t));
    report->counts = malloc(count_measurements * sizeof(int));

    printf("Input all count of elems that you want to test:");
    for(int i = 0, j = 0; i < count_measurements; i++)
    {
        if (INPUT_ONE_ELEM != scanf("%d", &report->counts[j]) || &report->counts[j] < 0)
        {
            puts("Invalid count, pass this value");
            count_measurements--;
            continue;
        }
        j++;
    }

    report->count_measures = count_measurements;
    for(int i = 0; i < report->count_measures; i++)
    {
        char filename[80];
        sprintf(filename, "..\\shared\\gen_%d.txt", report->counts[i]);
        printf("%s\n", filename);
        gen_file_with_int_numbers(report->counts[i], filename);
    }

    create_report(count_measurements, report->counts);
}