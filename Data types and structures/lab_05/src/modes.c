#include "../inc/modes.h"

int check_number(int *const number, const int l, const int r)
{
    char num[3];
    char *n;
    fflush(stdin);
    n = fgets(num, 4, stdin);
    if (n == NULL || num[0] == '\n')
        return INVALID_INPUT_NUMBER;

    num[strlen(num) - 1] = '\0';
    *number = (int)atoi(num);

    if (*number < l || *number > r)
        return INVALID_INPUT_NUMBER;

    return EXIT_SUCCESS;
}

void mode_change_time(times_t *t1, times_t *t2, times_t *t3, times_t *t4)
{
    double l, r;
    int c;
    printf("1: min = %lf; max = %lf\n", t1->min, t1->max);
    printf("2: min = %lf; max = %lf\n", t2->min, t2->max);
    printf("3: min = %lf; max = %lf\n", t3->min, t3->max);
    printf("4: min = %lf; max = %lf\n", t4->min, t4->max);
    printf("What interval to change?\n");
    if (check_number(&c, 1, 4) != EXIT_SUCCESS)
    {
        fflush(stdin);
        printf("Invalid input number\n");
        return ;
    }

    printf("Input left and right borders: ");
    if (scanf("%lf", &l) != 1)
    {
        printf("Invalid input number\n");
        return ;
    }

    if (scanf("%lf", &r) != 1)
    {
        printf("Invalid input number");
        return ;
    }

    if (c == 1)
    {
        t1->min = l;
        t1->max = r;
    }
    if (c == 2)
    {
        t2->min = l;
        t2->max = r;
    }
    if (c == 3)
    {
        t3->min = l;
        t3->max = r;
    }
    if (c == 4)
    {
        t4->min = l;
        t4->max = r;
    }

    printf("AFTER\n");
    printf("1: min = %lf; max = %lf\n", t1->min, t1->max);
    printf("2: min = %lf; max = %lf\n", t2->min, t2->max);
    printf("3: min = %lf; max = %lf\n", t3->min, t3->max);
    printf("4: min = %lf; max = %lf\n", t4->min, t4->max);
}