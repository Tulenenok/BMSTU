#include <time.h>
#include "../inc/modes.h"

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

    printf("\nUsed memory for static stack: %lu\n", memory_of_static_stack(&stacks->static_stack));
    printf("Used memory for linked list stack: %lu\n", memory_of_linked_list_stack(&stacks->linked_list_stack));

    return EXIT_SUCCESS;
}

int mode_del_elems_from_stacks(bool is_stacks_create, stacks_t *stacks, free_addresses_t *free_add)
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
        del_elem_from_linked_list_stack(&stacks->linked_list_stack, free_add);
    }

    return EXIT_FAILURE;
}

void mode_print_free_addresses(free_addresses_t *free_add)
{
    if(EMPTY_STACK == free_add->count_add)
    {
        puts("\nYou dont delete elems, nothing to print");
        return ;
    }

    puts("\nAddresses of all elems that you delete:");
    for(int i = 0; i < free_add->count_add; i++)
        printf("%p\n", free_add->data[i]);
    printf("\n");
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

void make_measurements(int i, int size_of_stack, reports_t *reports, stacks_t *stacks)
{
    clock_t start = clock();
    for(int j = 0; j < size_of_stack && j < COUNT_FOR_ONE_MEA; j++)
        del_elem_linked_list_stack_help_func(&stacks->linked_list_stack);
    clock_t end = clock();
    reports->data[i].linked_list_stack_del_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000 / COUNT_FOR_ONE_MEA;

    start = clock();
    for(int j = 0; j < size_of_stack && j < COUNT_FOR_ONE_MEA; j++)
        del_elem_static_stack_help_func(&stacks->static_stack);
    end = clock();
    reports->data[i].static_stack_del_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000 / COUNT_FOR_ONE_MEA;

    start = clock();
    for(int j = 0; j < size_of_stack && j < COUNT_FOR_ONE_MEA; j++)
        add_elem_linked_list_stack_help_func('a', &stacks->linked_list_stack);
    end = clock();
    reports->data[i].linked_list_stack_add_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000 / COUNT_FOR_ONE_MEA;

    start = clock();
    for(int j = 0; j < size_of_stack && j < COUNT_FOR_ONE_MEA; j++)
        add_elem_static_stack_help_func('a', &stacks->static_stack);
    end = clock();
    reports->data[i].static_stack_add_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000 / COUNT_FOR_ONE_MEA;

    start = clock();
    for(int j = 0; j < COUNT_FOR_ONE_MEA / 10 + 1; j++)
        is_palindrome_linked_list_stack(&stacks->linked_list_stack);
    end = clock();
    reports->data[i].linked_list_stack_pal_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000 / (COUNT_FOR_ONE_MEA / 10 + 1);

    start = clock();
    for(int j = 0; j < COUNT_FOR_ONE_MEA / 10 + 1; j++)
        is_palindrome_static_stack(&stacks->static_stack);
    end = clock();
    reports->data[i].static_stack_pal_time += ((double) (end - start)) / CLOCKS_PER_SEC * 1000 / (COUNT_FOR_ONE_MEA / 10 + 1);
}

void print_reports(reports_t *reports, bool print_add_del_inf)
{
    puts("\nRESULT OF THE EXPERIMENT:");
    puts("MEMORY");
    puts("Size of stack  | Memory for static stack | Memory for list stack");
    for(int i = 0; i < reports->count_reports; i++)
        printf("  %5d                  %lu                     %lu\n", reports->sizes[i], reports->data[i].static_stack_memory, reports->data[i].linked_list_stack_memory);

    puts("\nTIME");
    if(print_add_del_inf)
    {
        puts("Size of stack  | Add static stack | Add list stack | Del static stack | Del list stack");
        for (int i = 0; i < reports->count_reports; i++)
            printf("  %5d              %.5f           %.5f         %.5f         %.5f\n", reports->sizes[i],
                   (double)reports->data[i].static_stack_add_time,
                   (double)reports->data[i].linked_list_stack_add_time,
                   (double)reports->data[i].static_stack_del_time,
                   (double)reports->data[i].linked_list_stack_del_time);
    }

    puts("\nSize of stack  | Palindrome static stack | Palindrome list stack");
    for (int i = 0; i < reports->count_reports; i++)
        printf("  %5d                %.5f               %.5f\n",
               reports->sizes[i],
               (double)reports->data[i].static_stack_pal_time,
               (double)reports->data[i].linked_list_stack_pal_time);
    printf("\n");
}

int mode_conduct_research(void)
{
    int rc;
    int count_measurements = 0;
    printf("\nInput count of measurements that you want to do:");
    if(INPUT_ONE_ELEM != scanf("%d", &count_measurements) || count_measurements < 0)
    {
        puts("Invalid input count");
        return INVALID_INPUT_ELEM;
    }

    printf("\nInput all sizes of stack that you want to test:");

    reports_t reports = { count_measurements };
    reports.sizes = calloc(count_measurements, sizeof(int));
    reports.data = calloc(count_measurements, sizeof(report_t));
    for(int i = 0; i < count_measurements; i++)
    {
        int size_of_stack;
        if(INPUT_ONE_ELEM != scanf("%d", &size_of_stack) || size_of_stack < 0)
        {
            puts("Invalid size, pass this value");
            continue;
        }

        if(size_of_stack > MAX_SIZE_OF_STACK)
        {
            puts("Invalid size, size of stack more then max size of sys stack");
            puts("Аsk a smart programmer to change the program settings");
            continue;
        }

        generate_stack(size_of_stack);

        stacks_t stacks;
        if((rc = fill_static_stack_from_file("../shared/stack.txt", &stacks.static_stack)))
            return rc;

        if((rc = fill_linked_list_stack_from_file("../shared/stack.txt", &stacks.linked_list_stack)))
            return rc;

        reports.data[i].linked_list_stack_memory = memory_of_linked_list_stack(&stacks.linked_list_stack);
        reports.data[i].static_stack_memory = memory_of_static_stack(&stacks.static_stack);

        printf("\nSTART");
        for(int j = 0; j < COUNT_FOR_IN_REPORT; j++)
        {
            if(j - j / PRINT_ * PRINT_ == 0)
                printf("-");
            make_measurements(i, size_of_stack, &reports, &stacks);
        }
        printf("->END");

        reports.data[i].linked_list_stack_add_time /= COUNT_FOR_IN_REPORT;
        reports.data[i].linked_list_stack_del_time /= COUNT_FOR_IN_REPORT;
        reports.data[i].static_stack_add_time /= COUNT_FOR_IN_REPORT;
        reports.data[i].static_stack_del_time /= COUNT_FOR_IN_REPORT;
        reports.data[i].static_stack_pal_time /= COUNT_FOR_IN_REPORT;
        reports.data[i].static_stack_pal_time /= COUNT_FOR_IN_REPORT;

        reports.sizes[i] = size_of_stack;

        printf("\nResearch for size = %d     ----> SUCCESS\n", size_of_stack);

        free_for_node_list(stacks.linked_list_stack.data);
    }
    print_reports(&reports, true);
    free(reports.sizes);
    free(reports.data);

    return EXIT_SUCCESS;
}