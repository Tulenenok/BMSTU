#include "../inc/tools.h"

int cmp_int(int x, int y)
{
    return x - y;
}

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int count_elems_in_file(FILE *f)
{
    rewind(f);
    int count = 0, t;
    for(; fscanf(f, "%d", &t) == 1; count++);
    rewind(f);
    return count;
}

int is_elem_in_arr(int elem, int l, int r, int arr[])
{
    for(int i = l; i < r; i++)
        if(arr[i] == elem)
            return 1;
    return 0;
}

int unique_elems_in_file(FILE *f, int arr[])
{
    rewind(f);
    int i = 0, x;
    while(INPUT_ONE_ELEM == fscanf(f, "%d", &x))
        if(!is_elem_in_arr(x, 0, i, arr))
            arr[i++] = x;

    rewind(f);
    return i;
}
