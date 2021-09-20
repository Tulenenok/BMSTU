#include <ctype.h>

#include "big_double.h"
#include "tools.h"
#include "big_double_tools.h"

#define TRUE 1
#define FALSE 0

int is_big_double(char s[])
{
    big_double_t x = { 0 };
    if(from_str_to_big_double(s, &x))
        return FALSE;
    return TRUE;
}

int from_str_to_big_double(char s[], big_double_t *x)
{
    if(!is_scientific(s))
        return IS_NOT_SCIENTIFIC;

    int was_point = 0;

    size_t i = 0;

    for(; s[i] && s[i] != 'E' && s[i] != 'e'; i++);                  // Переводим экспоненту
    for(; s[i]; i++)
    {
        if(s[i] == '-')
            x->is_negative_e = 1;

        if(isdigit((int)s[i]))
            if(insert_end(x->exponent, E_LEN, s[i] - '0'))
                return OVERFLOW;                                 // Переполнение экспоненты
    }

    i = 0;                                                           // Вернули счетчик на начало числа

    for(size_t j = 0; s[i] && s[i] != 'E' && s[i] != 'e'; i++)       // Переводим мантиссу
    {
        if(s[i] == '.')
            was_point = 1;

        if(s[i] == '-')
            x->is_negative_m = 1;

        if(isdigit((int)s[i]) && j == M_LEN)                           // Мантиссу собрали, нужно округлить хвост
        {
            if(s[i] >= '5' && rounding(x->mantissa, M_LEN))
            {
                if(x->is_negative_e == 1)
                    reduce_by_one(x->exponent, E_LEN);

                if((x->is_negative_e == 0 && increase_by_one(x->exponent, E_LEN)))
                    return OVERFLOW;
            }

            for(; s[i] && s[i] != 'E' && s[i] != 'e'; i++);           // Больше мантиссу мы не рассматриваем
        }

        if(isdigit((int)s[i]) && was_point == 0 && !(s[i] == '0' && j == 0)) // Мантисса до точки (ведущие 0 игнорируем)
        {
            x->mantissa[j] = from_char_to_int_digit(s[i]);
            j++;

            if(x->is_negative_e == 1)
                reduce_by_one(x->exponent, E_LEN);

            if((x->is_negative_e == 0 && increase_by_one(x->exponent, E_LEN)))
                return OVERFLOW;
        }

        if(isdigit((int)s[i]) && was_point == 1)                      // Мантисса после точки (не изменяет экспоненту)
        {
            x->mantissa[j] = from_char_to_int_digit(s[i]);
            j++;
        }

        if(is_null_arr(x->exponent, E_LEN))
            x->is_negative_e = 0;
    }
    if(is_null_arr(x->mantissa, M_LEN))
        x->is_negative_m = 0;
    return EXIT_SUCCESS;
}

void from_big_double_to_str(char s[], big_double_t *x)
{
    size_t i = 3, j = M_LEN, k = 0;                         // i - счетчик по строке, j - счетчик по мантиссе, k - счетчик по экспоненте

    s[0] = (x->is_negative_m == 0) ? '+' : '-';             // определили знак мантиссы
    s[1] = '0';
    s[2] = '.';

    if(is_null_arr(x->exponent, E_LEN))
        s[i++] = '0';
    else
    {
        for(; j > 0 && x->mantissa[j - 1] == 0; j--);           // нашли, где мантисса заканчивается (чтобы не добавлять лишние нули)
        for(size_t t = 0; t < j; t++, i++)                      // добавили мантиссу
            s[i] = from_int_to_char_digit(x->mantissa[t]);
    }

    s[i] = 'E';                                             // добавили E
    i++;

    s[i] = (x->is_negative_e == 0) ? '+' : '-';             // добавили знак экспоненты
    i++;

    if(is_null_arr(x->exponent, E_LEN))
        s[i++] = '0';
    else
    {
        for(; k < E_LEN && x->exponent[k] == 0; k++);           // пропустили ведущие нули у экспоненты
        for(; k < E_LEN; k++, i++)                              // добавили экспоненту
            s[i] = from_int_to_char_digit(x->exponent[k]);
    }

    s[i] = '\0';
}

int division_big_double(big_double_t *x, big_double_t *y, big_double_t *z)
{
    if(is_null_arr(y->mantissa, M_LEN))
        return DIVISION_BY_ZERO;

    if(is_null_arr(x->mantissa, M_LEN))
        return EXIT_SUCCESS;

    bd_tool_t x_tool = { 0 }, y_tool = { 0 }, z_tool = { 0 };
    from_bd_to_bd_tool(x, &x_tool);
    from_bd_to_bd_tool(y, &y_tool);

    int change_exp[E_LEN] = {0}, t[E_LEN] = {0};
    int e_sign = 0, t_sign = 0;
    size_t i = 0;

    division_mantissa(x_tool.mantissa, y_tool.mantissa, z_tool.mantissa, change_exp, &e_sign, &i);

    z_tool.is_negative_m = x->is_negative_m != y->is_negative_m;

    if(subtract_exponent(x_tool.exponent, x_tool.is_negative_e, y_tool.exponent, y_tool.is_negative_e, t, &t_sign, E_LEN))
        return OVERFLOW;

    if(subtract_exponent(t, t_sign, change_exp, !e_sign, z_tool.exponent, &z_tool.is_negative_e, E_LEN))
        return OVERFLOW;

    return from_bd_tool_to_bd(&z_tool, z);
}

int is_equal(big_double_t *x, big_double_t *y)
{
    if(!arr_cmp(x->mantissa, M_LEN, y->mantissa, M_LEN) &&
        !arr_cmp(x->exponent, E_LEN, y->exponent, E_LEN) &&
        x->is_negative_m == y->is_negative_m &&
        x->is_negative_e == y->is_negative_e)
        return TRUE;
    return FALSE;

}

int big_double_scan(FILE *f, big_double_t *x)
{
    char str[M_LEN + E_LEN + 100] = "";

    int rc = EXIT_SUCCESS;

    if((rc = input_str(f, str)))
        return rc;

    if((rc = from_str_to_big_double(str, x)))
        return rc;

    return rc;
}

void big_double_print(FILE *f, big_double_t *x)
{
    char s[M_LEN + E_LEN + 5] = "";
    from_big_double_to_str(s, x);
    fprintf(f, "%s\n", s);
}
