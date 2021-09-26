#include <ctype.h>

#include "big_double.h"
#include "tools.h"
#include "big_double_tools.h"

#define TRUE 1
#define FALSE 0

int is_not_big_double(char s[])
{
    if(!is_scientific(s))
        return IS_NOT_SCIENTIFIC;

    size_t len_m = 0, len_e = 0;
    int was_e = FALSE;

    for(size_t i = 0; s[i]; i++)
        if(s[i] == 'E' || s[i] == 'e')
            was_e = TRUE;
        else if(isdigit(s[i]) && was_e == FALSE)
            len_m++;
        else if(isdigit(s[i]) && was_e == TRUE)
            len_e++;

    if(len_m > MAX_M_LEN)
        return TOO_LARGE_M;
    if(len_e > MAX_E_LEN)
        return TOO_LARGE_E;

    return EXIT_SUCCESS;
}

int from_str_to_big_double(char s[], big_double_t *x)
{
    int rc = EXIT_SUCCESS;

    if((rc = is_not_big_double(s)))
        return rc;

    size_t i = 0;
    for(; s[i] && s[i] != 'E' && s[i] != 'e'; i++);                  // Переводим экспоненту
    for(; s[i]; i++)
    {
        if(s[i] == '-')
            x->is_negative_e = 1;

        if(isdigit((int)s[i]))
            insert_end(x->exponent, E_LEN, from_char_to_int_digit(s[i]));
    }

    i = 0;                                                           // Вернули счетчик на начало числа
    for(; s[i] && s[i] != 'E' && s[i] != 'e' && s[i] != '.'; i++)    // Переводим мантиссу
    {
        if(s[i] == '-')
            x->is_negative_m = 1;
        if(s[i] == '+')
            x->is_negative_m = 0;
        if(isdigit(s[i]))
            insert_end(x->mantissa, M_LEN, from_char_to_int_digit(s[i]));
    }

    for(; s[i] && s[i] != 'E' && s[i] != 'e'; i++)
        if(isdigit(s[i]))
        {
            reduce_one_with_sign(x->exponent, E_LEN, &(x->is_negative_e));
            insert_end(x->mantissa, M_LEN, from_char_to_int_digit(s[i]));
        }

    if(is_null_arr(x->exponent, E_LEN))
        x->is_negative_e = 0;

    if(is_null_arr(x->mantissa, M_LEN))
        x->is_negative_m = 0;

    return rc;
}

void from_big_double_to_str(char s[], big_double_t *x)
{
    size_t i = 3, j = 1, k = 0;                         // i - счетчик по строке, j - счетчик по мантиссе, k - счетчик по экспоненте

    s[0] = (x->is_negative_m == 0) ? '+' : '-';             // определили знак мантиссы
    s[1] = '0';
    s[2] = '.';

    if(is_null_arr(x->mantissa, M_LEN))
        s[i++] = '0';
    else
    {
        for(; j < M_LEN && x->mantissa[j] == 0; j++);           // нашли, где мантисса заканчивается (чтобы не добавлять лишние нули)
        for(; j < M_LEN; j++, i++)                              // добавили мантиссу
        {
            s[i] = from_int_to_char_digit(x->mantissa[j]);
            increase_one_with_sign(x->exponent, E_LEN, &x->is_negative_e);
        }
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

    int x_m_copy[M_LEN] = {0}, y_m_copy[M_LEN] = {0};
    arr_cpy(x->mantissa, M_LEN, x_m_copy, M_LEN);
    arr_cpy(y->mantissa, M_LEN, y_m_copy, M_LEN);

    int change_exp[E_LEN] = {0}, t[E_LEN] = {0};
    int e_sign = 0, t_sign = 0;
    size_t i = 0;

    division_mantissa(x_m_copy, y_m_copy, z->mantissa, change_exp, &e_sign, &i);

    printf("\nDivision mantissa : DONE\n");

    z->is_negative_m = x->is_negative_m != y->is_negative_m;

    if(subtract_exponent(x->exponent, x->is_negative_e, y->exponent, y->is_negative_e, t, &t_sign, E_LEN))
        return OVERFLOW;

    if(subtract_exponent(t, t_sign, change_exp, !e_sign, z->exponent, &(z->is_negative_e), E_LEN))
        return OVERFLOW;

    printf("\nDivision exponent : DONE\n");

    if(z->mantissa[0] != 0 && z->mantissa[M_LEN - 1] >= 5)
    {
        if(round_shift_right(z->mantissa, M_LEN))
            return OVERFLOW;

        if(z->is_negative_e == 1)
            reduce_by_one(z->exponent, E_LEN);

        if((z->is_negative_e == 0 && increase_by_one(z->exponent, E_LEN)))
            return OVERFLOW;
        printf("\nRounding : DONE\n");
    } else if(z->mantissa[0] != 0)
    {
        shift_right(z->mantissa, M_LEN, 1);
        increase_one_with_sign(z->exponent, E_LEN, &z->is_negative_e);
    }

//    while(z->exponent[0] != 0 && z->mantissa[M_LEN - 1] == 0)
//    {
//        shift_left(z->mantissa, M_LEN, 1);
//        increase_one_with_sign(z->exponent, E_LEN, &x->is_negative_e);
//    }
    if(z->exponent[0] != 0)
        return OVERFLOW;
    return EXIT_SUCCESS;
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
    char s[MAX_M_LEN + MAX_E_LEN + 5] = "";
    from_big_double_to_str(s, x);
    fprintf(f, "%s\n", s);
}
