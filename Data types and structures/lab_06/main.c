#include <stdio.h>

#include "inc/mode.h"
#include "inc/tools.h"

void menu(mode_t mode, tree_node_t **bin_search_tree, hash_table_t **table, abl_node_t **abl_tree)
{
    setbuf(stdin, NULL);

    if((*bin_search_tree == NULL || *table == NULL || *abl_tree == NULL) && mode != INPUT_TREES && mode != REPORT)
    {
        printf("ERROR : DATA WAS NOT INPUT\nUse commands input(1)\n");
        return ;
    }

    if(INPUT_TREES == mode)
        mode_input(bin_search_tree, table, abl_tree);

    else if(PRINT_TREES == mode)
        mode_print(*bin_search_tree, *table, *abl_tree);

    else if(INSERT_ELEM == mode)
        mode_insert_elems(bin_search_tree, table, abl_tree);

    else if(FIND_ELEM == mode)
        mode_find_elem(*bin_search_tree, *table, *abl_tree);

    else if(CHANGE_TABLE == mode)
        mode_change_table(table);

    else if(REPORT == mode)
        mode_report();

    else
        puts("Invalid command");
}

int main()
{
    system("chcp 65001");                      // для русских букв
    setbuf(stdout, NULL);

    tree_node_t *bin_search_tree = NULL;
    hash_table_t *table = NULL;
    abl_node_t *abl_tree = NULL;

    while(true)
    {
        printf("Menu:\n"
               "    0 - EXIT\n"
               "    1 - input data\n"
               "    2 - insert elem\n"
               "    3 - find elem\n"
               "    4 - print data\n"
               "    5 - change table\n"
               "    6 - report\n");
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
            mode_free(bin_search_tree, table, abl_tree);
            break;
        }


        menu(mode, &bin_search_tree, &table, &abl_tree);
        printf("\n");
    }
}