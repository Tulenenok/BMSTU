#include <assert.h>

#include "../inc/linked_list_stack.h"

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

void del_elem_from_linked_list_stack(linked_list_stack_t *stack, free_addresses_t *free_add)
{
    if(EMPTY_STACK == stack->count_elems)
    {
        printf("Linked list stack is empty, nothing to delete\n");
        return ;
    }

    printf("\nFrom linked list stack you delete ----> %c\n", stack->data->data);
    printf("Address of delete elem %p\n", stack->data);

    free_add->data[free_add->count_add] = stack->data;
    free_add->count_add++;

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

long unsigned memory_of_linked_list_stack(linked_list_stack_t *stack)
{
    return stack->count_elems * sizeof(Node_t);
}

int fill_linked_list_stack_from_file(char filename[], linked_list_stack_t *stack)
{
    FILE *f = fopen(filename, "r");
    if(!f)
    {
        printf("Error with create stack");
        return EXIT_FAILURE;
    }

    if(INPUT_ONE_ELEM != fscanf(f, "%d", &stack->count_elems) || stack->count_elems < 0)
    {
        puts("Invalid size");
        fclose(f);
        return INVALID_INPUT_SIZE_STACK;
    }
    stack->max_count_elems = stack->count_elems;

    malloc_for_node_list(stack->count_elems, &stack->data);

    Node_t *cur = stack->data;
    for(int i = 0; i < stack->count_elems; i++, cur = cur->next)
        if(INPUT_ONE_ELEM != fscanf(f, "%c", &cur->data))
        {
            puts("Error in data");
            fclose(f);
            return INVALID_INPUT_ELEM;
        }

    fclose(f);
    return EXIT_SUCCESS;
}

void del_elem_linked_list_stack_help_func(linked_list_stack_t *stack)
{
    stack->data = del_first_elem_from_node_list(stack->data);
    stack->count_elems--;
}

void add_elem_linked_list_stack_help_func(char new_elem, linked_list_stack_t *stack)
{
    stack->data = add_first_elem_to_node_list(new_elem, stack->data);
    stack->count_elems++;
}