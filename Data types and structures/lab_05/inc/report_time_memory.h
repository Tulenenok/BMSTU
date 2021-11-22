#ifndef TIMEMEM_H
#define TIMEMEM_H

#include "queue.h"
#include "queue_like_array.h"
#include "queue_like_list.h"

double getime(times_t t);

int64_t tick(void);

void create_report();

#endif // TIMEMEM_H