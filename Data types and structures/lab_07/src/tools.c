#include <string.h>

#include "../inc/tools.h"
void clean_stdin(void)
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int is_elem_in_array(int elem, int n, int arr[])
{
    for(int i = 0; i < n; i++)
        if(arr[i] == elem)
            return 1;
    return 0;
}

int index_min_elem(int n, int arr[], int n_blocked, int blocked_indexes[])
{
    int min_ind = -1;
    for(int i = 0; i < n; i++)
        if(!is_elem_in_array(i, n_blocked, blocked_indexes))
        {
            min_ind = i;
            break;
        }

    if(min_ind == -1)
        return -1;

    for(int i = 0; i < n; i++)
        if(!is_elem_in_array(i, n_blocked, blocked_indexes) && arr[i] < arr[min_ind])
            min_ind = i;

    return min_ind;
}

void generate_matrix(int c, int r)
{
    char command[100] = "python ..\\gen\\gen_matrix.py";
    char args[50];
    sprintf(args, " %d %d", c, r);
    strcat(command, args);
    system(command);
}

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