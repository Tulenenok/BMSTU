#ifndef LAB_02_NEW_VERSION_MODES_H
#define LAB_02_NEW_VERSION_MODES_H

#include "../inc/flats.h"

typedef enum {
    EXIT = 0,
    ADD_FLAT = 1,
    DELETE_FLAT = 2,
    BUBBLE_SORT_WITH_DATASET = 3,
    BUBBLE_SORT_WITH_KEYS = 4,
    QSORT_WITH_DATASET = 5,
    QSORT_WITH_KEYS = 6,
    PRINT_DATASET = 7,
    PRINT_KEYS = 8,
    PRINT_FILTER = 9,
    PRINT_TABLE_KEYS = 10,
    RELOAD_TABLE = 11,
    PRINT_REPORT = 12
} modes_t;

void mode_add_elem(flat_t *flats, int *count_flats);

void mode_delete_flat(flat_t flats[], int *count_flats);

void mode_bubble_sort_using_dataset(flat_t flats[], int count_flats);

void mode_bubble_sort_using_keys(flat_t flats[], key_t *keys, int count_flats, int *is_keys_create);

void mode_qsort_sort_using_dataset(flat_t flats[], int count_flats);

void mode_qsort_sort_using_keys(flat_t flats[], key_t keys[], int count_flats, int *is_keys_create);

void mode_print_filter(flat_t flats[], int count_flats);

void mode_print_dataset(flat_t flats[], int count_flats);

void mode_print_keys(flat_t flats[], key_t keys[], int count_flats, int *is_keys_create);

void mode_print_table_keys(flat_t flats[], key_t keys[], int count_flats, int *is_keys_create);

int mode_reload_dataset(FILE *f, flat_t flats[], int *count_flats, int *is_keys_create);

int mode_print_memory_time_report(FILE *f, flat_t flats[], key_t keys[], int *count_flats, int *is_keys_create);

#endif //LAB_02_NEW_VERSION_MODES_H
