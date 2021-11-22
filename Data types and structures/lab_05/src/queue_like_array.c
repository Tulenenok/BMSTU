#include "../inc/queue_like_array.h"
#include "time.h"
#include <stdio.h>

void queue_array_push(queue_t *queue, char c_elem)
{
    char *tail = queue->tail;

    if (queue->tail == queue->head && *((char*)queue->tail) != '\0')
        printf("WARNING Queue is full\n");
    else
    {
        *((char*)queue->tail) = c_elem;
        queue->tail = (queue->tail != queue->address_up_border) ? tail + 1 : queue->address_low_border;
    }
}

char queue_array_pop(queue_t *queue)
{
    char *head = queue->head;
    char tmp;

    if (queue->tail == queue->head && *((char*)queue->tail) == '\0')
        printf("WARNING Queue is empty!\n");
    else
    {
        tmp = *((char*)queue->head);
        *((char*)queue->head) = '\0';
        queue->head = (queue->head != queue->address_up_border) ? head + 1 : queue->address_low_border;
    }
    return tmp;
}

void queue_array_print(queue_t *queue)//, char *elem)
{
    if (queue->head == queue->tail && *((char*)queue->tail) == '\0')
        printf(" WARNING Queue is empty!\n");
    else
    {
        char *begin = queue->head;
        char *end = queue->tail;
        while (begin != end)
        {
            printf("%c\n", *begin);
            begin  = (begin != queue->address_up_border) ? begin + 1 : queue->address_low_border;
        }
    }
}

void process_with_array(int n, int interval, times_t t1, times_t t2, times_t t3, times_t t4)//, int flag)
{
    char *queue_array_1 = (queue_type *)calloc(MAX_LEN_QUEUE, sizeof(queue_type));
    queue_t queue_1 = create_queue("1 queue", queue_array_1, queue_array_1 + MAX_LEN_QUEUE,
                                   queue_array_1, queue_array_1, MAX_LEN_QUEUE, sizeof(queue_type));
    for (int i = 0; i < queue_1.count_elems; i++)
        queue_array_1[i] = '\0';

    char *queue_array_2 = (queue_type *)calloc(MAX_LEN_QUEUE, sizeof(queue_type));
    queue_t queue_2 = create_queue("2 queue", queue_array_2, queue_array_2 + MAX_LEN_QUEUE,
                                   queue_array_2, queue_array_2, MAX_LEN_QUEUE, sizeof(queue_type));
    for (int i = 0; i < queue_2.count_elems; i++)
        queue_array_2[i] = '\0';


    int out_queue2 = 0, request_in_1 = 0, request_out_1 = 0, request_in_2 = 0, request_out_2 = 0, reqshow = 0;
    double time = 0, time_request_1 = 0, time_request_2 = 0, timereqobr = 0, all_time_queue_1 = 0, all_time_queue_2 = 0;

    time_t r_time_1 = clock();

    int type_queue = 0;

    puts("                                         PROCESS  ---  START");
    puts("-----------------------------------------------------------------------------------------------------");
    puts("|  Done tasks 1 queue  |  Len 1 queue  |  Middle len 1 queue  |  Len 2 queue  |  Middle len 2 queue |");
    puts("-----------------------------------------------------------------------------------------------------");

    while (request_out_1 < n + 1)
    {
        if ((queue_1.tail == queue_1.head && *((char*)queue_1.tail) != '\0') ||
            (queue_2.tail == queue_2.head && *((char*)queue_2.tail) != '\0'))
        {
            printf("Queue is full.\n");
            break;
        }

        if (fabs(time_request_1 - 0) < EPS)
            time_request_1 = getime(t1);

        if (fabs(time_request_2 - 0) < EPS)
            time_request_2 = getime(t2);

        if (fabs(timereqobr - 0) < EPS)
        {
            if (!(queue_1.tail == queue_1.head && *((char*)queue_1.tail) == '\0'))
            {
                timereqobr = getime(t3);
                type_queue = 1;
                update_queue_pop(&queue_1);
                all_time_queue_1 += timereqobr;
            }
            else if (!(queue_2.tail == queue_2.head && *((char*)queue_2.tail) == '\0'))
            {
                timereqobr = getime(t4);
                type_queue = 2;
                update_queue_pop(&queue_2);
                all_time_queue_2 += timereqobr;
            }
        }
        else if (type_queue == 2 && !(queue_2.tail == queue_2.head && *((char*)queue_2.tail) == '\0'))
        {
            update_queue_push(&queue_2, '2');
            all_time_queue_2 -= timereqobr;
            timereqobr = 0;
            out_queue2++;
            continue;
        }

        double time_min = 0;

        if (fabs(timereqobr - 0) < EPS)
            time_min = (time_request_1 - time_request_2 < EPS) ? time_request_1 : time_request_2;
        else
        {
            time_min = (time_request_2 - timereqobr < EPS) ? time_request_2 : timereqobr;
            time_min = (time_request_1 - time_min < EPS) ? time_request_1 : time_min;
        }

        if (fabs(time_min - timereqobr) < EPS)
        {
            timereqobr = 0;
            if (type_queue == 1)
                request_out_1++;
            if (type_queue == 2)
                request_out_2++;
        }

        if (request_out_1 == n)
            break;

        if (fabs(time_min - time_request_1) < EPS)
        {
            update_queue_push(&queue_1, '1');
            request_in_1++;
        }

        if (fabs(time_min - time_request_2) < EPS)
        {
            update_queue_push(&queue_2, '2');
            request_in_2++;
        }

        time_request_1 -= time_min;
        time_request_2 -= time_min;

        if (timereqobr >= time_min)
            timereqobr -= time_min;
        time += time_min;

        if (request_out_1 % interval == 0 && request_out_1 != reqshow)
        {
            reqshow = request_out_1;
            printf("|  %18d  |  %11d  |  %18lf  |  %11d  |  %18lf |\n", request_out_1,
                   queue_1.len_now, (queue_1.count_requests > 0) ? (double)queue_1.middle_len / (double)queue_1.count_requests : -1,
                   queue_2.len_now, (queue_2.count_requests > 0) ? (double)queue_2.middle_len / (double)queue_2.count_requests : -1);
            puts("-----------------------------------------------------------------------------------------------------");
        }
    }
    puts("                                         PROCESS  ---  END");

    puts("\nRESULT");
    time_t rtime2 = clock();
    int timerealall = rtime2 - r_time_1;

    double avetime_in1 = (t1.max + t1.min) / 2, avetime_out1 = (t3.max + t3.min) / 2, avetime_in2 = (t2.max + t2.min) / 2;
    double total_avetime_in1 = n * avetime_in1, total_avetime_out1 = n * avetime_out1;
    double totalwork = all_time_queue_1 + all_time_queue_2, timewithoutwork = time - totalwork;

    double timemodel = (total_avetime_in1 - total_avetime_out1 > EPS) ? total_avetime_in1 : total_avetime_out1;
    double wait_in1 = time / avetime_in1, wait_in2 = time / avetime_in2;
    double per_out = (fabs(timemodel - 0) > EPS) ? fabs(100 * (time - timemodel) / timemodel) : 0;
    double per_in1 = (fabs(wait_in1 - 0) > EPS) ? fabs(100 * (request_in_1 - wait_in1) / wait_in1) : 0;
    double per_in2 = (fabs(wait_in2 - 0) > EPS) ? fabs(100 * (request_in_2 - wait_in2) / wait_in2) : 0;

    puts("-------------------------------------------------------------------");
    puts("|  Total time  |  Real time  |  Time without work  |  Error rate  |");
    puts("-------------------------------------------------------------------");
    printf("|  %9lf |  %9d  |  %17lf  |  %9lf%%  |\n", time, timerealall, fabs(timewithoutwork), per_out);
    puts("-------------------------------------------------------------------");

    puts("");

    puts("-------------------------------------------------------------------------------------------------------------------");
    puts("|         |  Middle time  |  Count tasks input  |  Count tasks output  | Count tasks throw  |  Error rate input   |");
    puts("-------------------------------------------------------------------------------------------------------------------");
    printf("| Queue 1 |  %11lf  |  %17d  |  %18d  |         -          |  %16lf%%  |\n",
           avetime_in1, request_in_1, request_out_1, per_in1);
    puts("-------------------------------------------------------------------------------------------------------------------");
    printf("| Queue 2 |  %11lf  |  %17d  |  %18d  |  %16d  |  %16lf%%  |\n",
           avetime_in2, request_in_2, request_out_2, out_queue2, per_in2);
    puts("-------------------------------------------------------------------------------------------------------------------");

    free(queue_array_1);
    free(queue_array_2);
}