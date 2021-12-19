/*
 * Найти все вершины графа, к которым от
 * заданной вершины можно добраться по пути не длиннее А.
 */

#include <stdio.h>
#include <stdbool.h>

#include "inc/modes.h"
#include "inc/tools.h"

void menu(mode_t mode, graph_t **graph)
{
    if(INPUT_GRAPH_FROM_FILE == mode)
        mode_input_graph_from_file(graph);

    else if(PRINT_GRAPH == mode)
        mode_print_graph(*graph);

    else if(FIND == mode)
        mode_find(*graph);

    else if(REPORT == mode)
        mode_report();

    else
        puts("Invalid command");
}

int main()
{
    setbuf(stdout, NULL);

    graph_t *graph = NULL;

    while(true)
    {
        printf("Menu:\n"
               "    0 - EXIT\n"
               "    1 - input graph from file\n"
               "    2 - print graph\n"
               "    3 - find\n"
               "    4 - report\n");
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
            mode_free(graph);
            break;
        }

        menu(mode, &graph);
        printf("\n");
    }
}