#ifndef ARRAY_H
#define ARRAY_H

#include"queue.h"
#include "report_time_memory.h"

void process_with_array(int n, int interval, times_t t1, times_t t2, times_t t3, times_t t4);
void queue_array_push(queue_t *queue, char c_elem);
char queue_array_pop(queue_t *queue);
void queue_array_print(queue_t *queue);

#endif // ARRAY_H