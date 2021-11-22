#ifndef LIST_H
#define LIST_H

#include "queue.h"
#include "report_time_memory.h"
#include "io.h"

Node_t* createelem(queue_type c);
Node_t* pushfront(Node_t *head, Node_t *elem);
Node_t* popfront(Node_t **head);
Node_t* popend(Node_t **head);
void freeall(Node_t *head);

void process_list(int n, int interval, times_t t1,
                  times_t t2, times_t t3, times_t t4, int flag);

Node_t *queuelist_push(Node_t *queue, queue_type c, Node_t **user_memory,
                       int *user_count, Node_t **free_memory,
                       int *free_count, int *second_use);

Node_t *queuelist_pop(Node_t **queue);

void queuelist_print(Node_t *queue);

#endif // LIST_H