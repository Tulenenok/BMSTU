#include "../inc/tools.h"

int is_adress_correct(char adr[])
{
    if (strlen(adr) >= 25)
        return 0;
    int i = -1;
    while (adr[++i])
        if (!isalpha(adr[i]) && !isdigit(adr[i]) && !isspace(adr[i]) && adr[i] != ',')
            return 0;
    return 1;
}

int is_dec_correct(char dec[])
{
    int i = -1;
    while (dec[++i])
        if (!isdigit(dec[i]) || strlen(dec) > 10 || strlen(dec) == 10 && atoi(dec) < 0)
            return 0;
    return 1;
}

int is_bin_correct(char bin[])
{
    if (bin[0] != '0' && bin[0] != '1' || strlen(bin) > 1)
        return 0;
    return 1;
}

int is_data_correct(char data[][MAX_STR])
{
    for (int i = 0; i < COLUMNS; ++i)
    {
        int old;
        if (i == 0)
            if (!is_adress_correct(data[i]))
                return 0;
        if (i > 0 && i < 4)
            if (!is_dec_correct(data[i]))
                return 0;
        if (i == 4)
        {
            if (!is_bin_correct(data[i]))
                return 0;
            else
                old = atoi(data[i]);
        }
        if (i == 5)
        {
            if (!old && !is_bin_correct(data[i]))
                return 0;
            if (old && strcmp(data[i], "-"))
                return 0;
        }
        if (i > 5 && i < 9)
        {
            if (!old && strcmp(data[i], "-"))
                return 0;
            if (old && !is_dec_correct(data[i]))
                return 0;
        }
        if (i == 9)
        {
            if (!old && data[i][0] != '-')
                return 0;
            if (old && !is_bin_correct(data[i]))
                return 0;
        }

    }
    return 1;
}

void split(char str[], char arr[][MAX_STR], char delims[], size_t *n)
{
    size_t i, cur_wor_sym = 0;
    int flag;
    for (i = 0; str[i]; i++)
    {
        flag = 0;
        if (strchr(delims, str[i]) != NULL)
        {
            if (cur_wor_sym)
            {
                arr[*n][cur_wor_sym] = '\0';
                (*n)++;
                cur_wor_sym = 0;
                flag = 1;
            }
            flag = 1;
        }

        if (!flag)
        {
            arr[*n][cur_wor_sym] = str[i];
            cur_wor_sym++;
        }
    }

    if (cur_wor_sym)
    {
        arr[*n][cur_wor_sym] = '\0';
        (*n)++;
    }
}
