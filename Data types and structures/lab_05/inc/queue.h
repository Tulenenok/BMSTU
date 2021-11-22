#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#define MAX_LEN_QUEUE       100000
#define MAX_LEN_NAME        30
#define EPS                 1e-9

#define INVALID_INPUT_NUMBER   5

typedef char queue_type;
typedef struct queue
{
    char name[MAX_LEN_NAME];
    void *address_low_border;
    void *address_up_border;
    void *tail;
    void *head;

    int count_elems;
    int size_of_elems;

    int count_requests;
    int middle_len;
    int len_now;
    int sum_time;
    int requests_to_input;
    int requests_to_output;
} queue_t;

typedef struct node
{
    struct node *next;
    char data;
} Node_t;

typedef struct
{
    double min;
    double max;
} times_t;

queue_t create_queue(char name[], void *address_low_border, void *address_up_border, void *head, void *tail,
                     int count_elems, int size_of_elems);

void update_queue_pop(queue_t *q);
void update_queue_push(queue_t *q, char x);

#endif
