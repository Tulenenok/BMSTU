#include "inc/report_time_memory.h"
#include "inc/modes.h"

#define COUNT_TASKS 1000
#define INTERVAL 100

void menu(mode_t command, int n, int interval, times_t *t1, times_t *t2, times_t *t3, times_t *t4)
{
    if(QUEUE_LIKE_ARRAY == command)
        process_with_array(n, interval, *t1, *t2, *t3, *t4);
    if(QUEUE_LIKE_LIST == command)
        process_list(n, interval, *t1, *t2, *t3, *t4, 1);
    if(CHANGE_TIME == command)
        mode_change_time(t1, t2, t3, t4);
    if(PRINT_REPORT == command)
        create_report();

    fflush (stdin);
}

int main()
{
    setbuf(stdout, NULL);
    srand(time(NULL));

    int n = COUNT_TASKS;
    int interval = INTERVAL;

    times_t t1 = {1, 5 };
    times_t t2 = {0, 3 };
    times_t t3 = {0, 4 };
    times_t t4 = {0, 1 };

    int num_command = -1;
    while (num_command != 0)
    {
        printf("\nMenu:\n"
               "    0 - EXIT\n"
               "    1 - Queue like array\n"
               "    2 - Queue like list\n"
               "    3 - Change processing time\n"
               "    4 - Print report\n\n"
        );
        printf("Input command:");

        if (check_number(&num_command, 0, 4) != EXIT_SUCCESS)
        {
            fflush(stdin);
            printf("Invalid input command\n");
            continue;
        }

        fflush (stdin);
        menu(num_command, n, interval, &t1, &t2, &t3, &t4);
    }
    return EXIT_SUCCESS;
}
