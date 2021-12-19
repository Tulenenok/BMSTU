#include <time.h>
#include <string.h>
#include <stdint.h>

#include "../inc/modes.h"
#include "../inc/tools.h"

void mode_input_graph_from_file(graph_t **graph)
{
    if(*graph)               //  если граф существовал, его надо почистить
        free_graph(*graph);

    char *filename = GRAPH_FILE;
    FILE *f = fopen(filename, "r");
    if(!f)
    {
        puts("Invalid filename");
        puts("INPUT GRAPH FROM FILE ---> FAILURE");
        return ;
    }

    *graph = input_graph_from_file(f);
    if(!*graph)
    {
        puts("Error with data in file");
        puts("INPUT GRAPH FROM FILE ---> FAILURE");
        return ;
    }

    fclose(f);
    puts("INPUT GRAPH FROM FILE ---> SUCCESS");

    return ;
}

void mode_free(graph_t *graph)
{
    if(NULL != graph)
        free_graph(graph);
}

void mode_print_graph(graph_t *graph)
{
    if(graph == NULL)
    {
        puts("ERROR: graph was not input (use mode 1)");
        return ;
    }

    puts("----------------------------------------GRAPH----------------------------------------");
    print_graph_like_matrix(graph);
    puts("-------------------------------------------------------------------------------------");

    FILE *f = fopen(DOT_FILE, "w");
    if(!f)
    {
        printf("Invalid filename for dot");
        return ;
    }

    print_graph_like_dot(f, graph);

    fclose(f);

    system("dot -Tsvg -o ..\\results\\graph.svg ..\\results\\graph.dot");
}

void mode_find(graph_t *graph)
{
    if(NULL == graph)
    {
        puts("ERROR: graph was not input (use mode 1)");
        return ;
    }

    int start_top = 0;
    printf("Input start top (int number from 1 to %d):", graph->n);

    if(scanf("%d", &start_top) != INPUT_ONE_ELEM || start_top > graph->n || start_top <= 0)
    {
        puts("Invalid start top");
        return ;
    }

    int max_distance = 0;
    printf("Input max distance (int number from 1 to inf):");
    if(scanf("%d", &max_distance) != INPUT_ONE_ELEM || max_distance <= 0)
    {
        puts("Invalid max distance");
        return ;
    }

    int *dist_array = calloc(graph->n, sizeof(int));
    int *tops_array = calloc(graph->n, sizeof(int));

    find_distances(start_top - 1, max_distance, graph, dist_array, tops_array);

    puts("\n-------------------------FIND DISTANCES---------------------------------");
    printf("\n     ");
    for(int i = 1; i <= graph->n; i++)
        printf("   x%d   ", i);

    printf("\nx%d   ", start_top);

    for(int i = 0; i < graph->n; i++)
        printf("   %2d   ", dist_array[i]);

    puts("\n\n------------------------------------------------------------------------");

    printf("\nAll tops that can be reached from x%d:\n", start_top);
    for(int i = 0, j = 1; i < graph->n; i++)
        if(dist_array[i] <= max_distance)
            printf("    %d) x%d  [dist = %d]\n", j++, i + 1, dist_array[i]);

    puts("\n------------------------------------------------------------------------");

    printf("\nWays from x%d:\n", start_top);
    for(int i = 0; i < graph->n; i++)
        printf("%d ", tops_array[i]);

    puts("\n------------------------------------------------------------------------");
    free(dist_array);
    free(tops_array);
}

void create_time_report(int count_mea, int count_elems[])
{
    srand(time(NULL));
    printf("\nTIME(in processor clock cycles)\n");
    printf("+----------------------------+\n");
    printf("| COUNT TOPS |   USED TIME   |\n");
    printf("+----------------------------+\n");
    for(int i = 0; i < count_mea; i++)
    {
        generate_matrix(count_elems[i], count_elems[i]);
        int start_top = rand() % count_mea;
        int max_distance = rand() % 1000;

        char filename[MAX_LEN_FILENAME] = "..\\data\\graph_";
        char tail[50];
        sprintf(tail, "%d.txt", count_elems[i]);
        strcat(filename, tail);

        FILE *f = fopen(filename, "r");
        if(!f)
        {
            printf("ERROR WITH FILE\n");
            return;
        }

        graph_t *graph = input_graph_from_file(f);

        int *dist_array = calloc(graph->n, sizeof(int));
        int *tops_array = calloc(graph->n, sizeof(int));

        int64_t begin = tick();
        find_distances(start_top, max_distance, graph, dist_array, tops_array);
        int64_t end = tick();

        printf("| %10d |  %11lld  |\n", count_elems[i], end - begin);
        printf("+----------------------------+\n");

        free_graph(graph);
        free(dist_array);
        free(tops_array);
        fclose(f);
    }
}

void mode_report()
{
    int count_measurements = 0;
    printf("Input count of measurements that you want to do:");
    if(INPUT_ONE_ELEM != scanf("%d", &count_measurements) || count_measurements < 0)
    {
        puts("Invalid input count");
        return ;
    }

    int *count_elems = calloc(count_measurements, sizeof(int));

    printf("Input all count of elems that you want to test:");
    for(int i = 0, j = 0; i < count_measurements; i++)
    {
        if (INPUT_ONE_ELEM != scanf("%d", &count_elems[j]) || &count_elems[j] < 0)
        {
            puts("Invalid count, pass this value");
            count_measurements--;
            continue;
        }
        j++;
    }

    printf("\nMEMORY\n");
    printf("+----------------------------+\n");
    printf("| COUNT TOPS |  USED MEMORY  |\n");
    printf("+----------------------------+\n");
    for(int i = 0; i < count_measurements; i++)
        printf("| %10d |  %11lld  |\n", count_elems[i], memory_graph(count_elems[i]));
    printf("+----------------------------+\n");

    create_time_report(count_measurements, count_elems);
    free(count_elems);
}