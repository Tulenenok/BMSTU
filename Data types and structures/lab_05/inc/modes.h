#ifndef _MODES_H_
#define _MODES_H_

#include "../inc/report_time_memory.h"

typedef enum
{
    QUEUE_LIKE_ARRAY = 1,
    QUEUE_LIKE_LIST = 2,
    CHANGE_TIME = 3,
    PRINT_REPORT = 4,
} mode_t;

int check_number(int *const number, const int l, const int r);

void mode_change_time(times_t *t1, times_t *t2, times_t *t3, times_t *t4);

#endif
