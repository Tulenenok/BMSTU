#include "../inc/queue_like_list.h"

Node_t* createelem(queue_type c)
{
    Node_t *elem = malloc(sizeof(Node_t));
    if (elem)
    {
        elem->data = c;
        elem->next = NULL;
    }

    return elem;
}

Node_t* pushfront(Node_t *head, Node_t *elem)
{
    elem->next = head;
    return elem;
}

Node_t* popfront(Node_t **head)
{
    Node_t *cur = NULL;
    if (head)
    {
        cur = *head;
        *head = (*head)->next;
    }
    return cur;
}

Node_t* popend(Node_t **head)
{
    Node_t *end = NULL;
    if (*head != NULL)
    {
        Node_t *cur = *head;
        if (cur->next)
        {
            for ( ; cur->next->next; cur = cur->next)
                ;
            end = cur->next;
            cur->next = NULL;
        }
        else
        {
            end = cur;
            *head = NULL;
        }
    }

    return end;
}

void freeall(Node_t *head)
{
    Node_t *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}


Node_t *queuelist_push(Node_t *queue, queue_type c, Node_t **user_memory,
                       int *user_count, Node_t **free_memory,
                       int *free_count, int *second_use)
{
    Node_t *item = NULL;
    item = createelem(c);
    if (item)
    {
        user_memory[*(user_count++)] = item;
        int sign = 0;
        for (int i = 0; i < *user_count; ++i)
        {
            if (item == free_memory[i])
            {
                free_memory[i] = NULL;
                sign = 1;
            }

            if (sign)
                free_memory[i] = free_memory[i + 1];
        }
        if (sign)
        {
            *free_count -= 1;
            *second_use += 1;
        }
        queue = pushfront(queue, item);
    }
    else
    {
        printf("Queue is full!\n");
    }

    return queue;
}
Node_t *queuelist_pop(Node_t **queue)
{
    Node_t *cur = NULL;
    cur = popend(queue);

    if (cur == NULL)
    {
        printf("Queue is empty!\n");
    }

    return cur;
}
void queuelist_print(Node_t *queue)
{
    Node_t *cur = queue;
    if (queue == NULL)
    {
        printf("Queue is emrty.\n");
    }
    else
    {
        printf("Current queue:\n");
        for ( ; cur; cur = cur->next)
            printf("%c\n", cur->data);
        printf("\n");
    }
}

void process_list(int n, int interval, times_t t1, times_t t2, times_t t3, times_t t4, int flag)
{
    Node_t *cur;
    Node_t *free_memory[MAX_LEN_QUEUE];
    Node_t *used_memory[MAX_LEN_QUEUE];
    int free_count = 0, used_count = 0, second_use = 0;

    Node_t *queue1 = NULL;
    queue_t queue_1 = create_queue("1 queue ", NULL, NULL,
                                   NULL, NULL, MAX_LEN_QUEUE, sizeof(Node_t));

    Node_t *queue2 = NULL;
    queue_t queue_2 = create_queue("2 queue ", NULL, NULL,
                                   NULL, NULL, MAX_LEN_QUEUE, sizeof(Node_t));

    int request_in_1 = 0, request_out_1 = 0, request_in_2 = 0, request_out_2 = 0, reqshow = 0, out_queue2 = 0;

    double time = 0, time_request_1 = 0, time_request_2 = 0, time_request_obr = 0, all_time_queue_1 = 0, all_time_queue_2 = 0;
    time_t rtime1 = clock();
    int type_queue = 0;

    puts("                                         PROCESS  ---  START");
    puts("-----------------------------------------------------------------------------------------------------");
    puts("|  Done tasks 1 queue  |  Len 1 queue  |  Middle len 1 queue  |  Len 2 queue  |  Middle len 2 queue |");
    puts("-----------------------------------------------------------------------------------------------------");

    while (request_out_1 < n)
    {
        if (queue_1.len_now >= MAX_LEN_QUEUE || queue_2.len_now >= MAX_LEN_QUEUE)
        {
            printf("Queue is full.\n");
            break;
        }

        if (fabs(time_request_1 - 0) < EPS)
            time_request_1 = getime(t1);

        if (fabs(time_request_2 - 0) < EPS)
            time_request_2 = getime(t2);

        if (fabs(time_request_obr - 0) < EPS)
        {
            if (queue1 != NULL)
            {
                time_request_obr = getime(t3);
                type_queue = 1;
                cur = queuelist_pop(&queue1);
                if (cur != NULL)
                {
                    free_memory[free_count++] = cur;
                    free(cur);
                }
                queue_1.len_now--;
                queue_1.middle_len += queue_1.len_now;
                queue_1.count_requests++;
                queue_1.requests_to_output++;
                all_time_queue_1 += time_request_obr;
            }
            else if (queue2 != NULL)
            {
                time_request_obr = getime(t4);
                type_queue = 2;
                cur = queuelist_pop(&queue2);
                if (cur != NULL)
                {
                    free_memory[free_count++] = cur;
                    free(cur);
                }
                queue_2.len_now--;
                queue_2.middle_len += queue_2.len_now;
                queue_2.count_requests++;
                queue_2.requests_to_output++;
                all_time_queue_2 += time_request_obr;
            }
        }
        else
        {
            if (type_queue == 2 && queue1 != NULL)
            {
                queue2 = queuelist_push(queue2, '2', used_memory, &used_count, free_memory,&free_count, &second_use);
                queue_2.len_now++;
                queue_2.middle_len += queue_2.len_now;
                queue_2.count_requests++;
                queue_2.requests_to_input++;
                all_time_queue_2 -= time_request_obr;
                time_request_obr = 0;
                out_queue2++;

                continue;
            }
        }

        double timemin = 0;

        if (fabs(time_request_obr - 0) < EPS)
            timemin = (time_request_1 - time_request_2 < EPS) ? time_request_1 : time_request_2;
        else
        {
            timemin = (time_request_2 - time_request_obr < EPS) ? time_request_2 : time_request_obr;
            timemin = (time_request_1 - timemin < EPS) ? time_request_1 : timemin;
        }

        if (fabs(timemin - time_request_obr) < EPS)
        {
            time_request_obr = 0;
            if (type_queue == 1)
                request_out_1++;
            if (type_queue == 2)
                request_out_2++;
        }

        if (request_out_1 == n)
            break;

        if (fabs(timemin - time_request_1) < EPS)
        {
            queue1 = queuelist_push(queue1, '1', used_memory, &used_count, free_memory, &free_count, &second_use);
            queue_1.len_now++;
            queue_1.middle_len += queue_1.len_now;
            queue_1.count_requests++;
            queue_1.requests_to_input++;
            request_in_1++;
        }

        if (fabs(timemin - time_request_2) < EPS)
        {
            queue2 = queuelist_push(queue2, '2', used_memory, &used_count, free_memory, &free_count, &second_use);
            queue_2.len_now++;
            queue_2.middle_len += queue_2.len_now;
            queue_2.count_requests++;
            queue_2.requests_to_input++;
            request_in_2++;
        }

        time_request_1 -= timemin;
        time_request_2 -= timemin;

        if (time_request_obr >= timemin)
            time_request_obr -= timemin;
        time += timemin;

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

    int timerealall = rtime2 - rtime1;
    double avetime_in1 = (t1.max + t1.min) / 2, avetime_out1 = (t3.max + t3.min) / 2, avetime_in2 = (t2.max + t2.min) / 2;

    double total_avetime_in1 = n * avetime_in1;
    double total_avetime_out1 = n * avetime_out1;

    double timemodel = (total_avetime_in1 - total_avetime_out1 > EPS) ? total_avetime_in1 : total_avetime_out1;
    double wait_in1 = time / avetime_in1, wait_in2 = time / avetime_in2;
    double totalwork = all_time_queue_1 + all_time_queue_2, timewithoutwork = time - totalwork;
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
           avetime_in2, request_in_2, request_out_2, request_in_2 - request_out_2, per_in2);
    puts("-------------------------------------------------------------------------------------------------------------------");

    printf("\nPrint not used addresses? (1 - Yes, 0 - No)\n");
    if(scanf("%d", &flag) != 1 || (flag != 0  && flag != 1))
        printf("Invalid command");
    else if (flag == 1)
    {
        printf("Count again-addresses:                    ---> %d\n", second_use);
        printf("Count not used addresses:                 ---> %d\n", free_count);
        printf("Not used addresses:\n");
        for (int i = 0; i < ((30 < free_count) ? 30 : free_count); i++)
            printf("%p\n", (void *)free_memory[i]);
        fflush(stdin);
    }
    free(queue1);
    free(queue2);
    fflush(stdin);
}