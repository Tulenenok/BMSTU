#ifndef LAB_02_NEW_VERSION_FLATS_H
#define LAB_02_NEW_VERSION_FLATS_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STR 30
#define COLUMNS 10
#define MAX_SIZE 1000
#define MAX_OUTPUT_COUNT 10

typedef struct
{
    int is_decorate;
} new_flat_t;

typedef struct
{
    int year;
    int owners;
    int residents;
    int was_animals;
} old_flat_t;

typedef struct
{
    char address[MAX_STR];
    int s;
    int count_rooms;
    int price;
    int is_it_old;
    union
    {
        new_flat_t new_flat;
        old_flat_t old_flat;
    } type;
} flat_t;

typedef struct
{
    int ind;
    int s;
} key_t;

int read_data_from_file(FILE *f, flat_t fl[]);

void add_flat(char data[][MAX_STR], flat_t fl[], int i);

int input_flat(flat_t fl[], int i, int need_write_to_table);
int del_flat(flat_t fl[], int *sz);

void bubble_sort_flats(flat_t fl[], size_t k);
void bubble_sort_keys(key_t tb[], size_t k);

int flat_area_cmp(const void *a, const void *b);
int key_area_cmp(const void *a, const void *b);

int key(flat_t fl[], int sz);
void create_key_table(flat_t fl[], key_t tb[], int sz);

void print_dataset(flat_t fl[], int sz);
void print_according_to_tb(flat_t fl[], key_t tb[], int n);
void print_keys(key_t tb[], int n);

#endif
