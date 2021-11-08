#include <string.h>
#include "../inc/tools.h"

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void generate_stack(int size)
{
    char command[100] = "python ..\\generate\\gen.py";
    char args[50];
    sprintf(args, " %d", size);
    strcat(command, args);
    system(command);
}
