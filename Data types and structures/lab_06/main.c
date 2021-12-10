#include <stdio.h>

#include "inc/mode.h"
#include "inc/tools.h"
#include "inc/hash_table.h"

void menu(mode_t mode, tree_node_t **bin_search_tree, hash_table_t **table)
{
    setbuf(stdin, NULL);

    if(INPUT_TREES == mode)
        mode_input(bin_search_tree, table);

    else if(PRINT_TREES == mode)
        mode_print(*bin_search_tree, *table);

    else if(INSERT_ELEM == mode)
        mode_insert_elems(bin_search_tree, table);

    else if(FIND_ELEM == mode)
        mode_find_elem(*bin_search_tree, *table);

    else
        puts("Invalid command");
}

int main()
{
    system("chcp 65001");                      // для русских букв
    setbuf(stdout, NULL);

    tree_node_t *bin_search_tree = NULL;
    hash_table_t *table = NULL;

    while(true)
    {
        printf("Menu:\n"
               "    0 - EXIT\n"
               "    1 - input data\n"
               "    2 - insert elem\n"
               "    3 - find elem\n"
               "    4 - print data\n"
               "    5 - report\n");
        printf("Input command:");

        mode_t mode = EXIT;
        if (INPUT_ONE_ELEM != scanf("%d", &mode))
        {
            printf("Input mode:     ----> FAILURE\n");
            clean_stdin();
            continue;
        }

        if(EXIT == mode)
        {
            mode_free_trees(bin_search_tree);
            break;
        }

        menu(mode, &bin_search_tree, &table);
        printf("\n");
    }
}