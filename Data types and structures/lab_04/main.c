/*
 * Реализовать операции работы со стеком, который представлен в виде статического массива
 * и в виде односвязного линейного списка;
 * Оценить преимущества и недостатки каждой реализации: получить представление о механизмах выделения и
 * освобождения памяти при работе со стеком.
 *
 * Операции: добавление, удаление элементов и вывод текущего состояния стека.
 *
 * Используя стек, определить, является ли строка палиндромом
 */


/*
 * При реализации стека списком в вывод текущего состояния стека добавить просмотр адресов элементов стека и
 * создать свой список или массив свободных областей (адресов освобождаемых элементов) с выводом его на экран.
 */

#include <stdio.h>
#include <stdlib.h>
#include "inc/modes.h"
#include "inc/tools.h"

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void menu(mode_t mode, bool *is_stacks_create, stacks_t *stacks)
{
    setbuf(stdin, NULL);
    if(CREATE_STACKS == mode)
        mode_create_stacks(is_stacks_create, stacks);
    if(ADD_ELEM == mode)
        mode_add_elem_to_stacks(*is_stacks_create, stacks);
    if(DEL_ELEM == mode)
        mode_del_elem_from_stacks(*is_stacks_create, stacks);
    if(PRINT_STACKS == mode)
        mode_print_stacks(*is_stacks_create, stacks);
    if(IS_PALINDROME == mode)
        mode_is_palindrome(*is_stacks_create, stacks);
}

int main()
{
    setbuf(stdout, NULL);

    int rc;
    stacks_t stacks = { 0 };
    bool is_stacks_create = false;

    while(true)
    {
        printf("Menu:\n"
               "    0 - EXIT\n"
               "    1 - create stacks\n"
               "    2 - add elem\n"
               "    3 - delete elem\n"
               "    4 - print stacks\n"
               "    5 - check 'is stacks palindrome'\n");
        printf("Input command:");

        mode_t mode = EXIT;
        if (INPUT_ONE_ELEM != scanf("%d", &mode)) {
            printf("Input mode:     ----> FAILURE\n");
            clean_stdin();
            continue;
        }

        if(EXIT == mode)
        {
            free_for_node_list(stacks.linked_list_stack.data);
            break;
        }

        menu(mode, &is_stacks_create, &stacks);
        printf("\n");
    }
}
