#include "../inc/queue.h"
#include "../inc/queue_like_array.h"

queue_t create_queue(char name[], void *address_low_border, void *address_up_border, void *head, void *tail,
                     int count_elems, int size_of_elems)
{
    queue_t new_queue;
    strcpy(new_queue.name, name);

    new_queue.address_low_border = address_low_border;
    new_queue.address_up_border = address_up_border;
    new_queue.head = head;
    new_queue.tail = tail;

    new_queue.count_elems = count_elems;
    new_queue.size_of_elems = size_of_elems;

    new_queue.count_requests = 0;
    new_queue.middle_len = 0;
    new_queue.sum_time = 0;
    new_queue.len_now = 0;
    new_queue.requests_to_output = 0;
    new_queue.requests_to_input = 0;

    return new_queue;
}

void update_queue_pop(queue_t *q)
{
    queue_array_pop(q);
    q->len_now--;
    q->middle_len += q->len_now;
    q->count_requests++;
    q->requests_to_output++;
}

void update_queue_push(queue_t *q, char x)
{
    queue_array_push(q, x);
    q->len_now++;
    q->middle_len += q->len_now;
    q->count_requests++;
    q->requests_to_input++;
}