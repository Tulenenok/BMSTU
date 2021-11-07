#include "../inc/modes.h"

#include "../inc/tools.h"

int mode_create_stacks(bool *is_stacks_create, stacks_t *stacks)
{
    assert(NULL != stacks);

    if(*is_stacks_create)
    {
        printf("\nYou have already created stacks\n");
        return STACKS_ALREADY_CREATE;
    }

    printf("\nInput max size for stack:");
    int size = -1;
    if(INPUT_ONE_ELEM != scanf("%d", &size) || size <= 0 || size > MAX_SIZE_OF_STACK)
    {
        printf("Invalid input size\n");
        printf("Size of stack must be int number that >= 0 and < %d (max size of stack)\n", MAX_SIZE_OF_STACK);
        return INVALID_INPUT_SIZE_STACK;
    }

    stacks->static_stack = create_static_stack(size);
    stacks->linked_list_stack = create_linked_list_stack(size);

    *is_stacks_create = true;
    printf("Create stacks            ----> SUCCESS");
    return EXIT_SUCCESS;
}

int mode_add_elem_to_stacks(bool is_stacks_create, stacks_t *stacks)
{
    int rc;
    if(false == is_stacks_create)
    {
        puts("Stacks are not created");
        puts("Use command 1 to create");
        return STACKS_IS_NOT_CREATE;
    }

    char elem;
    printf("Input new elem:");
    if(INPUT_ONE_ELEM != scanf("%c", &elem))
    {
        puts("Invalid input input");
        return INVALID_INPUT_ELEM;
    }

    if((rc = add_elem_to_static_stack(elem, &stacks->static_stack)))
    {
        puts("Add elem to static stack        ---> FAILURE");
        return rc;
    }

    if((rc = add_elem_to_linked_list_stack(elem, &stacks->linked_list_stack)))
    {
        puts("Add elem to linked list stack   ---> FAILURE");
        return rc;
    }
    return EXIT_SUCCESS;
}

int mode_add_few_elems_to_stacks(bool is_stacks_create, stacks_t *stacks)
{
    int rc;
    if(false == is_stacks_create)
    {
        puts("Stacks are not created");
        puts("Use command 1 to create");
        return STACKS_IS_NOT_CREATE;
    }

    char elem;
    printf("Input string:");
    while(INPUT_ONE_ELEM == scanf("%c", &elem) && elem != '\n')
    {
        if(stacks->static_stack.count_elems == stacks->static_stack.max_count_elems)
        {
            puts("\nWARNING: Stacks full, add stopped");
            clean_stdin();
            return EXIT_SUCCESS;
        }
        if ((rc = add_elem_to_static_stack(elem, &stacks->static_stack))) {
            puts("Add elem to static stack        ---> FAILURE");
            return rc;
        }

        if ((rc = add_elem_to_linked_list_stack(elem, &stacks->linked_list_stack))) {
            puts("Add elem to linked list stack   ---> FAILURE");
            return rc;
        }
    }
    return EXIT_SUCCESS;
}

int mode_print_stacks(bool is_stacks_create, stacks_t *stacks)
{
    if(false == is_stacks_create)
    {
        puts("Stacks are not created");
        puts("Use command 1 to create");
        return STACKS_IS_NOT_CREATE;
    }

    printf("\nStacks contains %d\n", stacks->static_stack.count_elems);
    printf("Free %d\n", stacks->static_stack.max_count_elems - stacks->static_stack.count_elems);
    print_static_stack_like_word(&stacks->static_stack);
    printf("\n");

    print_static_stack(&stacks->static_stack);
    print_linked_list_stack(&stacks->linked_list_stack);

    return EXIT_SUCCESS;
}

int mode_del_elems_from_stacks(bool is_stacks_create, stacks_t *stacks)
{
    if(false == is_stacks_create)
    {
        puts("Stacks are not created");
        puts("Use command 1 to create");
        return STACKS_IS_NOT_CREATE;
    }

    int count_to_del;
    puts("How many elems do you want to delete?");
    printf("Input count:");
    if(INPUT_ONE_ELEM != scanf("%d", &count_to_del) || count_to_del < 0)
    {
        printf("Invalid input");
        return INVALID_INPUT_ELEM;
    }

    if(count_to_del > stacks->static_stack.count_elems)
    {
        puts("WARNING:");
        puts("The number entered is greater than the number of elements in the stacks");
        puts("All stack elements have been removed");
    }

    count_to_del = count_to_del * (count_to_del <= stacks->static_stack.count_elems) + stacks->static_stack.count_elems * (count_to_del > stacks->static_stack.count_elems);
    for(int i = 0; i < count_to_del; i++)
    {
        del_elem_from_static_stack(&stacks->static_stack);
        del_elem_from_linked_list_stack(&stacks->linked_list_stack);
    }

    return EXIT_FAILURE;
}

int mode_is_palindrome(bool is_stacks_create, stacks_t *stacks)
{
    if(false == is_stacks_create)
    {
        puts("Stacks are not created");
        puts("Use command 1 to create");
        return STACKS_IS_NOT_CREATE;
    }

    if(EMPTY_STACK == stacks->static_stack.count_elems)
    {
        printf("Stacks is empty, nothing to check");
        return EMPTY_STACK;
    }

    printf("\n");
    print_static_stack_like_word(&stacks->static_stack);

    if(is_palindrome_static_stack(&stacks->static_stack))
        puts("Static stack is palindrome");
    else
        puts("Static stack is not palindrome");

    if(is_palindrome_linked_list_stack(&stacks->linked_list_stack))
        puts("Linked list stack is palindrome");
    else
        puts("Linked list is not palindrome");

    return EXIT_SUCCESS;
}