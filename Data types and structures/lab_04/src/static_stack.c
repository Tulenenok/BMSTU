#include <assert.h>

#include "../inc/static_stack.h"

// Голова стека - всегда последний заполненный элемент массива

// Создать стек в виде статического массива максимальным размером size
// Возвращает созданный список
static_stack_t create_static_stack(int size)
{
    static_stack_t stack = { 0 };
    stack.max_count_elems = size;
    stack.count_elems = 0;
    return stack;
}

int add_elem_to_static_stack(char new_elem, static_stack_t *stack)
{
    assert(NULL != stack);

    if(stack->count_elems == stack->max_count_elems)
    {
        puts("The static stack is completely full, you cannot add an element");
        return FULL_STACK;
    }
    stack->data[stack->count_elems] = new_elem;
    stack->count_elems++;

    puts("The item add to the static stack           ----> SUCCESS");
    return EXIT_SUCCESS;
}

void print_static_stack(static_stack_t *stack)
{
    assert(NULL != stack);

    puts("STATIC STACK");
    printf("HEAD --> \n");
    for(int i = stack->count_elems; i > 0; i--)
        printf("         %c\n", stack->data[i - 1]);
    printf("\n\n");
}

void print_static_stack_like_word(static_stack_t *stack)
{
    assert(NULL != stack);

    printf("Word now: ");
    for(int i = 0; i < stack->count_elems; i++)
        printf("%c", stack->data[i]);
    printf("\n");
}

void del_elem_from_static_stack(static_stack_t *stack)
{
    if(EMPTY_STACK == stack->count_elems)
    {
        puts("Static stack is empty, nothing to delete");
        return ;
    }
    stack->count_elems--;
    printf("\nFrom static stack you delete      ----> %c", stack->data[stack->count_elems]);
}

bool is_palindrome_static_stack(static_stack_t *stack)
{
    for(int i = 0, j = stack->count_elems - 1; i < j; i++, j--)
        if(stack->data[i] != stack->data[j])
            return false;
    return true;
}

long unsigned memory_of_static_stack(static_stack_t *stack)
{
    return MAX_SIZE_OF_STACK;
}

int fill_static_stack_from_file(char filename[], static_stack_t *stack)
{
    FILE *f = fopen(filename, "r");
    if(!f)
    {
        printf("Error with create stack");
        return EXIT_FAILURE;
    }

    if(INPUT_ONE_ELEM != fscanf(f, "%d", &stack->count_elems) || stack->count_elems < 0 || stack->count_elems > MAX_SIZE_OF_STACK)
    {
        puts("Invalid size");
        fclose(f);
        return INVALID_INPUT_SIZE_STACK;
    }
    stack->max_count_elems = stack->count_elems;

    for(int i = 0; i < stack->count_elems; i++)
        if(INPUT_ONE_ELEM != fscanf(f, "%c", &stack->data[i]))
        {
            puts("Error in data");
            fclose(f);
            return INVALID_INPUT_ELEM;
        }

    fclose(f);
    return EXIT_SUCCESS;
}

void del_elem_static_stack_help_func(static_stack_t *stack)
{
    stack->count_elems--;
}

void add_elem_static_stack_help_func(char new_elem, static_stack_t *stack)
{
    stack->data[stack->count_elems] = new_elem;
    stack->count_elems++;
}