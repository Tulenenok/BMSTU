#include "../inc/graph.h"
#include "../inc/tools.h"

#define MAX_LEN_DIST 100000

#define DBG_PRINT                        \
do                                       \
{                                        \
    puts("\nTops array:");               \
    for(int i = 0; i < graph->n; i++)  \
        printf("%d ", tops_array[i]);    \
                                         \
    puts("\nDistance array:");           \
                                         \
    for(int i = 0; i < graph->n; i++)    \
        printf("%d ", dist_array[i]);    \
}                                        \
while(0)

graph_t *create_graph(int n)
{
    graph_t *new_graph = calloc(1, sizeof(graph_t));
    if(!new_graph)
        return NULL;

    new_graph->data = calloc(n, sizeof(int*));
    if(!new_graph->data)
    {
        free(new_graph);
        return NULL;
    }

    for(int i = 0; i < n; i++)
    {
        new_graph->data[i] = calloc(n, sizeof(int));
        if(!new_graph->data[i])
        {
            for(int j = 0; j < i; j++)
                free(new_graph->data[j]);
            free(new_graph->data);
            free(new_graph);
        }
    }

    return new_graph;
}

void free_graph(graph_t *graph)
{
    for(int i = 0; i < graph->n; i++)
        free(graph->data[i]);
    free(graph->data);
    free(graph);
}

graph_t *input_graph_from_file(FILE *f)
{
    int x;
    if(fscanf(f, "%d", &x) != INPUT_ONE_ELEM || x <= 0)
        return NULL;

    graph_t *new_graph = create_graph(x);
    if(new_graph == NULL)
        return NULL;

    new_graph->n = x;

    for(int i = 0; i < new_graph->n; i++)
        for(int j = 0; j < new_graph->n; j++)
        {
            if (fscanf(f, "%d", &x) != INPUT_ONE_ELEM || x < 0)
            {
                free_graph(new_graph);
                return NULL;
            }
            new_graph->data[i][j] = x;
        }

    return new_graph;
}

void print_graph_like_matrix(graph_t *graph)
{
    printf("%d\n", graph->n);
    for(int i = 0; i < graph->n; i++)
    {
        for (int j = 0; j < graph->n; j++)
            printf("%d ", graph->data[i][j]);
        printf("\n");
    }
}

void print_graph_like_dot(FILE *f, graph_t *graph)
{
    fprintf(f, "digraph new_graph {\n");

    for(int i = 0; i < graph->n; i++)
        for(int j = 0; j < graph->n; j++)
            if(graph->data[i][j] != 0)
                fprintf(f, "x%d->x%d [label=\"%d\"]\n", i + 1, j + 1, graph->data[i][j]);

    fprintf(f, "}\n");
}

void find_distances(int start_top, int max_distance, graph_t *graph, int *dist_array, int *tops_array)
{
    tops_array[0] = start_top;
    for(int i = 0; i < graph->n; i++)
        if(i != start_top)
            dist_array[i] = graph->data[start_top][i] != 0 ? graph->data[start_top][i] : MAX_LEN_DIST;

    int count_tops = 1;
    for(int i = 0; i < graph->n; i++)
    {
        int min_ind = index_min_elem(graph->n, dist_array, count_tops, tops_array);
        if(min_ind == -1 || count_tops == graph->n)
            break;

        tops_array[count_tops++] = min_ind;

        for(int j = 0; j < graph->n; j++)
            if(!is_elem_in_array(j, count_tops, tops_array))
                if(graph->data[min_ind][j] != 0)
                    dist_array[j] = dist_array[j] < dist_array[min_ind] + graph->data[min_ind][j] ? dist_array[j] : dist_array[min_ind] + graph->data[min_ind][j];
    }
}

graph_t *copy_graph(graph_t *graph)
{
    graph_t *copy_graph = create_graph(graph->n);
    if(!copy_graph)
        return NULL;

    for(int i = 0; i < copy_graph->n; i++)
        for(int j = 0; j < copy_graph->n; j++)
            copy_graph->data[i][j] = graph->data[i][j];

    return copy_graph;
}

//int *find_ways_for_print(int start_top, graph_t *graph, int *tops)
//{
//    int *result_data = calloc(graph->n * graph->n, sizeof(int));
//    for(int i = 0; i < graph->n; i++)
//        if(i == tops[i])
//            result_data[i][]
//}

long long int memory_graph(int count_elems)
{
    return count_elems * count_elems * sizeof(int);
}