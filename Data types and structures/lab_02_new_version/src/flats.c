#include "../inc/flats.h"
#include "../inc/tools.h"

#include <stdbool.h>

#define BLANK_STRING -1

int input_str(char s[], const int max_len);



int read_data_from_file(FILE *f, flat_t fl[])
{
    char str[MAX_STR*COLUMNS];
    int i = 0;
    char line[COLUMNS][MAX_STR];
    while (fgets(str, 200, f))
    {
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = 0;
        size_t c = 0;
        split(str, line, ";", &c);
        if (is_data_correct(line) && c == 10)
            add_flat(line, fl, i);
        else
            return 0;
        i++;
    }
    return i;
}

void create_key_table(flat_t fl[], key_t tb[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        tb[i].ind = i;
        tb[i].s = fl[i].s;
    }
}

void bubble_sort_flats(flat_t fl[], size_t k)
{
    if (fl == NULL)
        return;
    for (size_t i = 0; i < k - 1; i++)
        for (size_t j = 0; j < k - 1 - i; j++)
            if (fl[j].s > fl[j + 1].s)
            {
                flat_t buf = fl[j + 1];
                fl[j + 1] = fl[j];
                fl[j] = buf;
            }
}

void bubble_sort_keys(key_t tb[], size_t k)
{
    if (tb == NULL)
        return;
    for (size_t i = 0; i < k - 1; i++)
        for (size_t j = 0; j < k - 1 - i; j++)
            if (tb[j].s > tb[j + 1].s)
            {
                key_t buf = tb[j + 1];
                tb[j + 1] = tb[j];
                tb[j] = buf;
            }
}

void print_new_flat(flat_t fl)
{
    printf("%-25s %-8d %-8d %-8d     NO     ", fl.address, fl.s, fl.count_rooms, fl.price);
    if (fl.type.new_flat.is_decorate)
        printf(" YES       ");
    else
        printf(" NO        ");
    printf(" -           -        -          -        \n");
}
void print_old_flat(flat_t fl)
{
    printf("%-25s %-8d %-8d %-8d     YES     -          %-11d %-8d %-10d", fl.address, fl.s, fl.count_rooms, fl.price, fl.type.old_flat.year, fl.type.old_flat.owners, fl.type.old_flat.residents);
    if (fl.type.old_flat.was_animals)
        printf(" Y");
    else
        printf(" N");
    printf("\n");
}
void print_according_to_tb(flat_t fl[], key_t tb[], int n)
{
    printf("      Address                   s     count_rooms    price(m^2)   is old  is decor.  build time  owners   residents  an\n");
    for (int i = 0; i < MAX_OUTPUT_COUNT; ++i)
    {
        printf("   %-3d     ", i);
        if (fl[tb[i].ind].is_it_old)
            print_old_flat(fl[tb[i].ind]);
        else
            print_new_flat(fl[tb[i].ind]);
    }
}

int key(flat_t fl[], int sz)
{
    int a, b;
    printf("Price(m^2) range:\nfrom >>> ");
    if (scanf("%d", &a) != 1 || a < 0)
        return -1;
    printf("to >>> ");
    if (scanf("%d", &b) != 1 || b < 0 || b < a)
        return -1;

    flat_t filtered[MAX_SIZE];
    int j = 0;
    for (int i = 0; i < sz; i++)
    {
        if (fl[i].is_it_old && fl[i].count_rooms == 2 && fl[i].price >= a && fl[i].price <= b && !fl[i].type.old_flat.was_animals)
            filtered[j++] = fl[i];
    }
    print_dataset(filtered, j);
    return j;
}
void print_keys(key_t tb[], int n)
{
    printf("         s\n");
    if (n > MAX_OUTPUT_COUNT)
    {
        for (int i = 0; i < MAX_OUTPUT_COUNT/2; ++i)
            printf("  %-8d  %-8d\n", tb[i].ind, tb[i].s);
        printf("       ...\n");
        for (int i = n - MAX_OUTPUT_COUNT/2; i < n; ++i)
            printf("  %-8d  %-8d\n", tb[i].ind, tb[i].s);
    }
    else
        for (int i = 0; i < n; ++i)
            printf("  %-8d  %-8d\n", tb[i].ind, tb[i].s);

}

int flat_area_cmp(const void *a, const void *b)
{
    flat_t *a1 = (void *) a;
    flat_t *a2 = (void *) b;
    return a1->s - a2->s;
}
int key_area_cmp(const void *a, const void *b)
{
    key_t *a1 = (void *) a;
    key_t *a2 = (void *) b;
    return a1->s - a2->s;
}

int input_params_of_del_flat(flat_t *flat)
{
    printf("Input params of flat that your want to delete\n");
    printf("Address:");
    if(input_str(flat->address, 25))
        return EXIT_FAILURE;
    printf("Area:");
    if(scanf("%d", &flat->s) != 1 || flat->s < 0)
        return EXIT_FAILURE;
    printf("Count rooms:");
    if(scanf("%d", &flat->count_rooms) != 1|| flat->count_rooms < 0)
        return EXIT_FAILURE;
    printf("Price:");
    if(scanf("%d", &flat->price) != 1 || flat->count_rooms < 0)
        return EXIT_FAILURE;

    char buf[2];
    printf("Is it old? (0 - NO, 1 - YES):");
    scanf("%s", buf);
    if (!strcmp(buf, "0"))
    {
        flat->is_it_old = 0;
        printf("Is finishing?(0 - NO, 1 - YES):");
        if(scanf("%d", &flat->type.new_flat.is_decorate) != 1 ||
                (flat->type.new_flat.is_decorate != 0 && flat->type.new_flat.is_decorate != 1))
            return EXIT_FAILURE;
    }
    else if (!strcmp(buf, "1"))
    {
        flat->is_it_old = 1;
        printf("Build time:");
        if(scanf("%d", &flat->type.old_flat.year) != 1 || flat->type.old_flat.year < 0)
            return EXIT_FAILURE;

        printf("Owners:");
        if(scanf("%d", &flat->type.old_flat.owners) != 1 || flat->type.old_flat.owners < 0)
            return EXIT_FAILURE;

        printf("Residents:");
        if(scanf("%d", &flat->type.old_flat.residents) != 1 || flat->type.old_flat.residents < 0)
            return EXIT_FAILURE;

        printf("Was animals?(0 - NO, 1 - YES):");
        if(scanf("%d", &flat->type.old_flat.was_animals) != 1 ||
           (flat->type.old_flat.was_animals != 0 && flat->type.old_flat.was_animals != 1))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

bool is_flats_equal(flat_t *fl1, flat_t *fl2)
{
    if(strcmp(fl1->address, fl2->address))
        return false;
    if(fl1->s != fl2->s)
        return false;
    if(fl1->count_rooms != fl2->count_rooms)
        return false;
    if(fl1->price != fl2->price)
        return false;
    if(fl1->is_it_old != fl2->is_it_old)
        return false;
    if(fl1->is_it_old)
    {
        if(fl1->type.old_flat.year != fl2->type.old_flat.year)
            return false;
        if(fl1->type.old_flat.owners != fl2->type.old_flat.owners)
            return false;
        if(fl1->type.old_flat.residents != fl2->type.old_flat.residents)
            return false;
        if(fl1->type.old_flat.was_animals != fl2->type.old_flat.was_animals)
            return false;
    } else
        if(fl1->type.new_flat.is_decorate != fl2->type.new_flat.is_decorate)
            return false;
    return true;
}

int del_flat(flat_t fl[], int *sz)
{
    flat_t flat = { 0 };
    input_params_of_del_flat(&flat);

    for (int i = 0; i < *sz; i++)
        if(is_flats_equal(&flat, &fl[i]))
        {
            for (int j = i; j < *sz - 1; j++)
                fl[j] = fl[j + 1];
            i--;
            (*sz)--;
        }
    return 0;
}

int input_str(char s[], const int max_len)
{
    char buf;
    int len = 0;
    int is_blank_str = true;

    for (; 1 == scanf("%c", &buf) && '\n' != buf && len < max_len; len++)
    {
        s[len] = buf;
        if (' ' != buf)
            is_blank_str = false;
    }

    if (max_len == len)
        return 6;

    s[len] = '\0';

    return (0 == len || is_blank_str) ? BLANK_STRING : EXIT_SUCCESS;
}

int input_flat(flat_t fl[], int i, int need_write_to_table)
{
    char input[300];
    char arr[10][MAX_STR];
    char buf[30];

    printf("Address:");
    if(input_str(buf, 25))
        return EXIT_FAILURE;
    strcat(input, buf);
    strcat(input, ";");

    printf("Area:");
    scanf("%s", buf);
    if (strlen(buf) > 10 || strlen(buf) == 10 && atoi(buf) < 0)
        return -1;
    strcat(input, buf);
    strcat(input, ";");

    printf("Rooms:");
    scanf("%s", buf);
    if (strlen(buf) > 10 || strlen(buf) == 10 && atoi(buf) < 0)
        return -1;
    strcat(input, buf);
    strcat(input, ";");

    printf("Price:");
    scanf("%s", buf);
    if (strlen(buf) > 10 || strlen(buf) == 10 && atoi(buf) < 0)
        return -1;
    strcat(input, buf);
    strcat(input, ";");

    printf("Is it old? (0 - NO, 1 - YES):");
    scanf("%s", buf);
    strcat(input, buf);
    strcat(input, ";");

    if (!strcmp(buf, "0"))
    {
        printf("Is finishing?(0 - NO, 1 - YES):");
        scanf("%s", buf);
        strcat(input, buf);
        strcat(input, ";-;-;-;-");
    }
    else if (!strcmp(buf, "1"))
    {
        strcat(input, "-;");
        printf("Build time:");
        scanf("%s", buf);
        if (strlen(buf) > 10 || strlen(buf) == 10 && atoi(buf) < 0)
            return -1;
        strcat(input, buf);
        strcat(input, ";");

        printf("Owners:");
        scanf("%s", buf);
        if (strlen(buf) > 10 || strlen(buf) == 10 && atoi(buf) < 0)
            return -1;
        strcat(input, buf);
        strcat(input, ";");

        printf("Residents:");
        scanf("%s", buf);
        if (strlen(buf) > 10 || strlen(buf) == 10 && atoi(buf) < 0)
            return -1;
        strcat(input, buf);
        strcat(input, ";");

        printf("Was animals?(0 - NO, 1 - YES):");
        scanf("%s", buf);
        strcat(input, buf);
    }
    else
        return EXIT_FAILURE;

    size_t c = 0;

    split(input, arr, ";", &c);
    if (is_data_correct(arr))
    {
        if (need_write_to_table)
            add_flat(arr, fl, i);
    }
    else
        return EXIT_FAILURE;

    return 0;
}

void print_dataset(flat_t fl[], int sz)
{
    printf("\n         Address                   s     count_rooms    price   is old  is decor.  build time  owners   residents  an\n");
    if (sz > MAX_OUTPUT_COUNT)
    {
        for (int i = 0; i < MAX_OUTPUT_COUNT/2; ++i)
        {
            printf(" %-3d     ", i);
            if (fl[i].is_it_old)
                print_old_flat(fl[i]);
            else
                print_new_flat(fl[i]);
        }
        printf("                                                               ...\n");
        for (int i = sz - MAX_OUTPUT_COUNT/2; i < sz; ++i)
        {
            printf(" %-3d     ", i);
            if (fl[i].is_it_old)
                print_old_flat(fl[i]);
            else
                print_new_flat(fl[i]);
        }
    }
    else
        for (int i = 0; i < sz; ++i)
        {
            printf(" %-3d     ", i);
            if (fl[i].is_it_old)
                print_old_flat(fl[i]);
            else
                print_new_flat(fl[i]);
        }

}

void add_flat(char data[][MAX_STR], flat_t fl[], int i)
{
    strcpy(fl[i].address, data[0]);
    fl[i].s = atoi(data[1]);
    fl[i].count_rooms = atoi(data[2]);
    fl[i].price = atoi(data[3]);
    fl[i].is_it_old = atoi(data[4]);

    if (!fl[i].is_it_old)
        fl[i].type.new_flat.is_decorate = atoi(data[5]);
    else
    {
        fl[i].type.old_flat.year = atoi(data[6]);
        fl[i].type.old_flat.owners = atoi(data[7]);
        fl[i].type.old_flat.residents = atoi(data[8]);
        fl[i].type.old_flat.was_animals = atoi(data[9]);
    }
}

