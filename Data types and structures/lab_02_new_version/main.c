#include <stdio.h>
#include "inc/flats.h"
#include "inc/code_errors.h"
#include "inc/modes.h"

int main(void)
{
    modes_t mode = ADD_FLAT;

    setbuf(stdout, NULL);

    FILE *f = fopen("C:\\projects\\C\\TSD\\lab_02_new_version\\data\\data.txt", "r");
    if (!f)
        return ERROR_OPEN_FILE ;


    flat_t flats[MAX_SIZE];
    key_t keys[MAX_SIZE];

    int count_flats;
    if (!(count_flats = read_data_from_file(f, flats)))
    {
        printf("Input data                ----> FAILURE\n");
        return INVALID_DATA;
    }
    printf("Input data                ----> SUCCESS\n");

    int is_keys_create = 0;
    while (mode != 0)
    {
        printf("\nMenu:\n"
               "    0 - EXIT\n"
               "    1 - Add flat\n"
               "    2 - Delete flat\n"
               "    3 - Usual sort using dataset, key = s\n"
               "    4 - Usual sort using keys, key = s\n"
               "    5 - Quick sort using dataset, key = s\n"
               "    6 - Quick sort using keys, key = s\n"
               "    7 - Print dataset\n"
               "    8 - Print keys\n"
               "    9 - Print filter dataset (old flats with 2 count_rooms without animals in price <range>)\n"
               "    10 - Print table according to array of keys\n"
               "    11 - Reload dataset from file\n"
               "    12 - Print memory and time report\n"
               "\n"
               "Input command:");

        if (scanf("%d", &mode) != 1)
            break;

        char t;
        scanf("%c", &t);

        if(EXIT == mode)
            break;

        if (ADD_FLAT == mode)
            mode_add_elem(flats, &count_flats);

        if (DELETE_FLAT == mode)
            mode_delete_flat(flats, &count_flats);

        if (BUBBLE_SORT_WITH_DATASET == mode)
            mode_bubble_sort_using_dataset(flats, count_flats);

        if (BUBBLE_SORT_WITH_KEYS == mode)
            mode_bubble_sort_using_keys(flats, keys, count_flats, &is_keys_create);

        if (QSORT_WITH_DATASET == mode)
            mode_qsort_sort_using_dataset(flats, count_flats);

        if (QSORT_WITH_KEYS == mode)
            mode_qsort_sort_using_keys(flats, keys, count_flats, &is_keys_create);

        if (PRINT_FILTER == mode)
            mode_print_filter(flats, count_flats);

        if (PRINT_DATASET == mode)
            mode_print_dataset(flats, count_flats);

        if (PRINT_KEYS == mode)
            mode_print_keys(flats, keys, count_flats, &is_keys_create);

        if (PRINT_TABLE_KEYS == mode)
            mode_print_table_keys(flats, keys, count_flats, &is_keys_create);

        int rc = 0;
        if (RELOAD_TABLE == mode)
            if((rc = mode_reload_dataset(f, flats, &count_flats, &is_keys_create)))
                return rc;

        if (PRINT_REPORT == mode)
            if((rc = mode_print_memory_time_report(f, flats, keys, &count_flats, &is_keys_create)))
                return rc;
    }

    fclose(f);
    return EXIT_SUCCESS;
}
