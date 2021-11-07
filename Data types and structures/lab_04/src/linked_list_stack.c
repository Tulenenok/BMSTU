#include <assert.h>

#include "../inc/linked_list_stack.h"
#include "../inc/tools.h"

// Создать стек в виде односвязного списка максимальным размером size
// Выделяет память под заданное количество элементов
// Возвращает созданный список
linked_list_stack_t create_linked_list_stack(int size)
{
    linked_list_stack_t stack = { 0 };
    stack.max_count_elems = size;
    stack.count_elems = 0;
    stack.data = NULL;
    return stack;
}

int add_elem_to_linked_list_stack(char new_elem, linked_list_stack_t *stack)
{
    assert(NULL != stack);

    if(stack->count_elems == stack->max_count_elems)
    {
        puts("The linked stack is completely full, you cannot add an element");
        return FULL_STACK;
    }

    stack->data = add_first_elem_to_node_list(new_elem, stack->data);
    stack->count_elems++;

    puts("The item add to the linked list stack      ----> SUCCESS");
    return EXIT_SUCCESS;
}

void print_linked_list_stack(linked_list_stack_t *stack)
{
    puts("LINKED LIST STACK");
    printf("HEAD --> \n");
    print_node_list(stack->data);
    printf("\n");
}

void del_elem_from_linked_list_stack(linked_list_stack_t *stack)
{
    if(EMPTY_STACK == stack->count_elems)
    {
        printf("Linked list stack is empty, nothing to delete\n");
        return ;
    }

    printf("\nFrom linked list stack you delete ----> %c\n", stack->data->data);
    printf("Address of delete elem %p\n", stack->data);

    stack->data = del_first_elem_from_node_list(stack->data);
    stack->count_elems--;
}

bool is_palindrome_linked_list_stack(linked_list_stack_t *stack)
{
    Node_t *left = stack->data;
    for(int i = 0, j = stack->count_elems - 1; i < j; i++, j--, left = left->next)
        if(left->data != take_data_by_index(j, stack->data))
            return false;
    return true;
}