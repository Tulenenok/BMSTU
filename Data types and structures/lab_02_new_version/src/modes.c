#include "../inc/modes.h"
#include <assert.h>

void mode_add_elem(flat_t flats[], int *count_flats)
{
    if (input_flat(flats, (*count_flats)++, 1))
    {
        printf("Add flat                  ----> FAILURE\n");
        (*count_flats)--;
    } else
        printf("Add flat                  ----> SUCCESS\n");
}

void mode_delete_flat(flat_t flats[], int *count_flats)
{
    if (del_flat(flats, count_flats))
        printf("Delete flat               ----> FAILURE\n");
    else
        printf("Delete flat               ----> SUCCESS\n");
}

void mode_bubble_sort_using_dataset(flat_t flats[], int count_flats)
{
    clock_t start, end;
    double time;

    start = clock();
    bubble_sort_flats(flats, count_flats);
    end = clock();

    printf("Sort flats                ----> SUCCESS\n");

    time = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    printf("Time = %lf ms", time);
    printf("\nMemory = %ld B\n", (&flats[count_flats] - &flats[0]) * sizeof(flats[0]));
}

void mode_bubble_sort_using_keys(flat_t flats[], key_t keys[], int count_flats, int *is_keys_create)
{
    clock_t start, end;
    double time;

    start = clock();
    create_key_table(flats, keys, count_flats), (*is_keys_create)++;
    bubble_sort_keys(keys, count_flats);
    end = clock();

    printf("Sort flats                ----> SUCCESS\n");

    time = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Time = %lf ms", time);
    printf("\nMemory = %ld B\n", (&flats[count_flats] - &flats[0]) * sizeof(flats[0]) + (&keys[count_flats] - &keys[0]) * sizeof(keys[0]));
}

void mode_qsort_sort_using_dataset(flat_t flats[], int count_flats)
{
    clock_t start, end;
    double time;

    start = clock();
    qsort(flats, count_flats, sizeof(flats[0]), flat_area_cmp);
    end = clock();

    printf("Sort flats                ----> SUCCESS\n");

    time = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Time = %lf ms", time);
    printf("\nMemory = %ld B\n", (&flats[count_flats] - &flats[0]) * sizeof(flats[0]));
}

void mode_qsort_sort_using_keys(flat_t flats[], key_t keys[], int count_flats, int *is_keys_create)
{
    clock_t start, end;
    double time;

    start = clock();
    create_key_table(flats, keys, count_flats), (*is_keys_create)++;
    qsort(keys, count_flats, sizeof(keys[0]), key_area_cmp);
    end = clock();

    printf("Sort flats                ----> SUCCESS\n");

    time = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    printf("time = %lf ms", time);
    printf("\nmemory = %ld B\n", (&flats[count_flats] - &flats[0]) * sizeof(flats[0]) + (&keys[count_flats] - &keys[0]) * sizeof(keys[0]));
}

void mode_print_filter(flat_t flats[], int count_flats)
{
    int n1 = key(flats, count_flats);
    if (n1 == 0)
        printf("Empty result.\n");
    if (n1 < 0)
        printf("Print filter              ----> FAILURE.\n");
}

void mode_print_dataset(flat_t flats[], int count_flats)
{
    print_dataset(flats, count_flats);
}

void mode_print_keys(flat_t flats[], key_t keys[], int count_flats, int *is_keys_create)
{
    assert(is_keys_create);

    if (!*is_keys_create)
    {
        create_key_table(flats, keys, count_flats);
        (*is_keys_create)++;
    }
    print_keys(keys, count_flats);
}

void mode_print_table_keys(flat_t flats[], key_t keys[], int count_flats, int *is_keys_create)
{
    assert(is_keys_create);

    if (!*is_keys_create)
        create_key_table(flats, keys, count_flats), (*is_keys_create)++;
    print_according_to_tb(flats, keys, count_flats);
}

int mode_reload_dataset(FILE *f, flat_t flats[], int *count_flats, int *is_keys_create)
{
    rewind(f);
    *is_keys_create = 0;
    if (!(*count_flats = read_data_from_file(f, flats)))
    {
        printf("Reload data               ----> FAILURE");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int mode_print_memory_time_report(FILE *f, flat_t flats[], key_t keys[], int *count_flats, int *is_keys_create)
{
    clock_t start, end;
    double time;

    double t_b_d, t_b_k, t_q_d, t_q_k;
    long m_b_d, m_b_k, m_q_d, m_q_k;

    rewind(f);
    if (!(*count_flats = read_data_from_file(f, flats)))
    {
        printf("Input data                ----> FAILURE");
        return EXIT_FAILURE;
    }

    start = clock();
    bubble_sort_flats(flats, *count_flats);
    end = clock();

    t_b_d = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    m_b_d = (&flats[*count_flats] - &flats[0]) * sizeof(flats[0]);

    rewind(f);
    if (!(*count_flats = read_data_from_file(f, flats)))
    {
        printf("Input data                ----> FAILURE");
        return EXIT_FAILURE;
    }

    start = clock();
    create_key_table(flats, keys, *count_flats), (*is_keys_create)++;
    bubble_sort_keys(keys, *count_flats);
    end = clock();

    t_b_k = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    m_b_k = (&flats[*count_flats] - &flats[0]) * sizeof(flats[0]) + (&keys[*count_flats] - &keys[0]) * sizeof(keys[0]);

    rewind(f);
    if (!(*count_flats = read_data_from_file(f, flats)))
    {
        printf("Input data                ----> FAILURE");
        return EXIT_FAILURE;
    }

    start = clock();
    qsort(flats, *count_flats, sizeof(flats[0]), flat_area_cmp);
    end = clock();

    t_q_d = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    m_q_d = (&flats[*count_flats] - &flats[0]) * sizeof(flats[0]);

    rewind(f);
    if (!(*count_flats = read_data_from_file(f, flats)))
    {
        printf("Input data                ----> FAILURE");
        return EXIT_FAILURE;
    }

    start = clock();
    create_key_table(flats, keys, *count_flats), (*is_keys_create)++;
    qsort(keys, *count_flats, sizeof(keys[0]), key_area_cmp);
    end = clock();

    t_q_k = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
    m_q_k = (&flats[*count_flats] - &flats[0]) * sizeof(flats[0]) + (&keys[*count_flats] - &keys[0]) * sizeof(keys[0]);

    printf("\nResults (%d flats):\n\n"
           "             bub. sort (dataset)     bub. sort (keys)     qsort (dataset)     qsort (keys)\n"
           "time (ms)    %-23.6lf %-20.6lf %-19.6lf %-19.6lf\n"
           "memory (B)   %-23ld %-20ld %-19ld %-19ld\n", *count_flats, t_b_d, t_b_k, t_q_d, t_q_k, m_b_d, m_b_k, m_q_d, m_q_k);
    return EXIT_SUCCESS;
}