#include <string.h>
#include <ctype.h>

#include "tools.h"
#include "big_int.h"

// Функция осуществляет проверку: является ли строка корректной для перевода ее в тип big_int_t
int is_big_int(char x[])
{
    size_t len_x = strlen(x);
    int is_sign = len_x > 0 && (x[0] == '+' || x[0] == '-');

    // Проверка, что длина строки не превыщает максимально возможной длинны числа
    if((!is_sign && len_x > DATA_LEN) || (is_sign && len_x > DATA_LEN + 1))
        return 0;

    // Проверка, что строка не состоит из одного знака + или -
    if(is_sign && len_x == 1)
        return 0;

    // Проверка, что строка не содержит символов отличных от цифер или +- (возможны только на нулевой позиции)
    for(size_t i = 0; i < len_x; i++)
        if(isdigit(x[i]) == 0 && !(i == 0 && (x[i] == '+' || x[i] == '-')))
            return 0;

    return 1;
}

// Функция переводит строку в число типа big_int
// Возвращает нулевое значение, если ошибок при переводе не возникло, иначе любое ненулевое число
int from_str_to_big_int(char str[], big_int_t *x)
{
    if(is_big_int(str) == 0)
        return EXIT_FAILURE;

    for(size_t i = strlen(str), j = DATA_LEN; j > 0 && i > 0 && isdigit(str[i - 1]); i--, j--)
        x->data[j - 1] = from_char_to_int_digit(str[i - 1]);

    x->is_negative = (str[0] == '-');

    return EXIT_SUCCESS;
}

// Переводит число типа big_int в строку
// Ответственность за корректную длину строки лежит на вызывающей строне.
void from_big_int_to_str(big_int_t *x, char str[])
{
    if(x->is_negative == 0)
        str[0] = '+';
    else
        str[0] = '-';

    size_t i = 0, j = 1;
    for(; i < DATA_LEN && x->data[i] == 0; i++);
    for(; i < DATA_LEN; i++, j++)
        str[j] = (char)x->data[i] + '0';

    str[j] = '\0';
}

void from_int_to_big_int(int x, big_int_t *res)
{
    res->is_negative = x < 0;
    x = abs(x);

    for(size_t i = DATA_LEN; x != 0 && i > 0; x /= 10, i--)
        res->data[i - 1] = x - x / 10 * 10;
}

//void big_int_print(FILE *f, big_int_t *x)
//{
//    if(x->is_negative)
//        printf("-");
//    else
//        printf("+");

//    for(size_t i = 0; i < x->len_data; i++)
//        fprintf(f, "%d", x->data[i]);
//}

//int big_int_scan(FILE *f, big_int_t *x)
//{
//    char str[DATA_LEN + 2] = "";

//    if(fgets(str, DATA_LEN + 2, f) == NULL)
//        return EXIT_FAILURE;

//    if(from_str_to_big_int(str, x))
//        return EXIT_FAILURE;

//    return EXIT_SUCCESS;
//}

int big_int_cmp(big_int_t *x, big_int_t *y)
{
    if(x->is_negative == 1 && y->is_negative == 0)
        return -1;

    if(x->is_negative == 0 && y->is_negative == 1)
        return 1;

    if(x->is_negative == 0 && y->is_negative == 0)
        for(size_t i = 0; i < DATA_LEN; i++)
            if(x->data[i] != y->data[i])
                return x->data[i] - y->data[i];

    if(x->is_negative == 1 && y->is_negative == 1)
        for(size_t i = 0; i < DATA_LEN; i++)
            if(x->data[i] != y->data[i])
                return y->data[i] - x->data[i];
    return 0;
}

int big_int_add(big_int_t *x, big_int_t *y, big_int_t *sum)
{
    if(x->is_negative == y->is_negative)
    {
        sum->is_negative = x->is_negative;
        return add(x->data, DATA_LEN, y->data, DATA_LEN, sum->data, DATA_LEN);
    }

    int cmp = arr_cmp(x->data, DATA_LEN, y->data, DATA_LEN);

    if(cmp > 0)
    {
        subtract(x->data, DATA_LEN, y->data, DATA_LEN, sum->data, DATA_LEN);
        sum->is_negative = x->is_negative;
    }

    if(cmp < 0)
    {
        subtract(y->data, DATA_LEN, x->data, DATA_LEN, sum->data, DATA_LEN);
        sum->is_negative = y->is_negative;
    }

    if(cmp == 0)
    {
        fill_arr(sum->data, DATA_LEN, 0);
        sum->is_negative = 0;
    }
    return EXIT_SUCCESS;
}

int big_int_diff(big_int_t *x, big_int_t *y, big_int_t *diff)
{
    if(x->is_negative != y->is_negative)
    {
        diff->is_negative = x->is_negative;
        return add(x->data, DATA_LEN, y->data, DATA_LEN, diff->data, DATA_LEN);
    }

    int cmp = arr_cmp(x->data, DATA_LEN, y->data, DATA_LEN);

    if(cmp > 0)
    {
        subtract(x->data, DATA_LEN, y->data, DATA_LEN, diff->data, DATA_LEN);
        diff->is_negative = x->is_negative;
    }

    if(cmp < 0)
    {
        subtract(y->data, DATA_LEN, x->data, DATA_LEN, diff->data, DATA_LEN);
        diff->is_negative = !x->is_negative;
    }

    if(cmp == 0)
    {
        fill_arr(diff->data, DATA_LEN, 0);
        diff->is_negative = 0;
    }
    return EXIT_SUCCESS;
}
