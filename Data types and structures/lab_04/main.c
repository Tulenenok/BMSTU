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
#include "inc/modes.h"

void menu(mode_t mode, bool *is_stacks_create, stacks_t *stacks, free_addresses_t *free_add)
{
    setbuf(stdin, NULL);
    if(CREATE_STACKS == mode)
        mode_create_stacks(is_stacks_create, stacks);
    if(ADD_FEW_ELEMS == mode)
        mode_add_few_elems_to_stacks(*is_stacks_create, stacks);
    if(DEL_ELEMS == mode)
        mode_del_elems_from_stacks(*is_stacks_create, stacks, free_add);
    if(PRINT_STACKS == mode)
        mode_print_stacks(*is_stacks_create, stacks);
    if(IS_PALINDROME == mode)
        mode_is_palindrome(*is_stacks_create, stacks);
    if(PRINT_FREE_ADDRESSES == mode)
        mode_print_free_addresses(free_add);
    if(CONDUCT_RESEARCH == mode)
        mode_conduct_research();
}

int main()
{
    setbuf(stdout, NULL);

    stacks_t stacks = { 0 };
    bool is_stacks_create = false;
    free_addresses_t free_add = { 0 };

    while(true)
    {
        printf("Menu:\n"
               "    0 - EXIT\n"
               "    1 - create stacks\n"
               "    2 - add elems\n"
               "    3 - delete elems\n"
               "    4 - print stacks\n"
               "    5 - check 'is stacks palindrome'\n"
               "    6 - print free addresses\n"
               "    7 - conduct research about memory and time\n");
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

        menu(mode, &is_stacks_create, &stacks, &free_add);
        printf("\n");
    }
}
