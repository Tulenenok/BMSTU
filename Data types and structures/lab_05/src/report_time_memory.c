#include "../inc/report_time_memory.h"

double getime(times_t t)
{
    return (t.max - t.min) * (double)(rand()) / (double)RAND_MAX + t.min;
}

int64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
    "rdtsc\n"
    "movl %%edx, %0\n"
    "movl %%eax, %1\n"
    : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void create_report()
{
    Node_t *free_memory[MAX_LEN_QUEUE];
    Node_t *used_memory[MAX_LEN_QUEUE];
    int free_count = 0, used_count = 0, second_use = 0;

    char *queue_array_1 = (queue_type *)malloc(MAX_LEN_QUEUE * sizeof(queue_type));
    queue_t queue_1 = create_queue("1 queue", queue_array_1, queue_array_1 + MAX_LEN_QUEUE,
                                   queue_array_1, queue_array_1, MAX_LEN_QUEUE, sizeof(queue_type));;
    for (int i = 0; i < queue_1.count_elems; i++)
        queue_array_1[i] = '\0';

    Node_t *queue2 = NULL;

    int64_t t1b = tick();
    queue_array_push(&queue_1, '1');
    int64_t t1e = tick();

    int64_t t2b = tick();
    queue2 = queuelist_push(queue2, '2', used_memory, &used_count, free_memory, &free_count, &second_use);
    int64_t t2e = tick();

    int64_t t3b = tick();
    queue_array_pop(&queue_1);
    int64_t t3e = tick();

    int64_t t4b = tick();
    queuelist_pop(&queue2);
    int64_t t4e = tick();

    puts("RESULT TIME");
    puts("----------------------------------------");
    puts("|           |    ADD    |    DELETE    |");
    puts("----------------------------------------");
    printf("|   ARRAY   |   %5d   |    %6d    |\n", (int)(t1e - t1b), (int)(t3e - t3b));
    puts("----------------------------------------");
    printf("|   LIST    |   %5d   |    %6d    |\n", (int)(t2e - t2b), (int)(t4e - t4b));
    puts("----------------------------------------");

    puts("\nRESULT MEMORY");
    puts("-----------------------------------------");
    puts("|  COUNT ELEMS  |   ARRAY   |    LIST   |");
    puts("-----------------------------------------");

    int n = 10;
    for (int i = 0; i < 4; i++, n *= 10)
    {
        printf("|  %11d  |   %5d   |   %6d  |\n", n, (int) (sizeof(char) * n),
               (int) ((sizeof(Node_t)) * n));
        puts("-----------------------------------------");
    }
}