#include "tools.h"
#include "big_double.h"
#include "big_double_tools.h"

int from_bd_to_bd_tool(big_double_t *x, bd_tool_t *y)
{
    y->is_negative_m = x->is_negative_m;
    y->is_negative_e = x->is_negative_e;
    arr_cpy(x->exponent, E_LEN, y->exponent, E_LEN);
    arr_cpy_to_end(x->mantissa, M_LEN, y->mantissa, M_LEN + 1);

    size_t i = M_LEN;
    for(; i > 0  && x->mantissa[i - 1] == 0; i--);
    for(; i > 0; i--)
        if(reduce_one_with_sign(y->exponent, E_LEN, &(y->is_negative_e)))
            return OVERFLOW;
    return EXIT_SUCCESS;
}

int from_bd_tool_to_bd(bd_tool_t *x, big_double_t *y)
{
    y->is_negative_m = x->is_negative_m;
    y->is_negative_e = x->is_negative_e;
    arr_cpy(x->exponent, E_LEN, y->exponent, E_LEN);
    arr_cpy_to_start(x->mantissa, M_LEN + 1, y->mantissa, M_LEN);

    size_t i = 0;
    for(; i < M_LEN + 1  && x->mantissa[i] == 0; i++);
    for(; i < M_LEN + 1; i++)
        if(increase_one_with_sign(y->exponent, E_LEN, &(y->is_negative_e)))
            return OVERFLOW;
    return EXIT_SUCCESS;
}

int division_mantissa(int x[], int y[], int z[], int change_exp[], int *e_sign, size_t *i)
{
    if(*i >= M_LEN + 1)                                  // Выход из рекурсии (заполнили всю мантиссу)
        return 0;

    int div[M_LEN + 1] = {0}, mod[M_LEN + 1] = {0};      // Массивы для промежуточных вычислений

    size_t len = M_LEN + 1;
    if(arr_cmp(x, len, y, len) < 0)                      // Увеличили мантиссу на 10
    {
        shift_left(x, len, 1);
        reduce_one_with_sign(change_exp, E_LEN, e_sign); // Учли это в экспоненте
    }

    size_t x_i = 0, y_i = 0;
    for(; x_i < len && x[x_i] == 0; x_i++);
    for(; y_i < len && y[y_i] == 0; y_i++);
    if(arr_cmp(x, len, y, len) > 0 && x_i < y_i)
    {
        shift_left(y, len, y_i - x_i - 1);
        while(x_i < y_i - 1)
        {
            increase_one_with_sign(change_exp, E_LEN, e_sign);
            y_i--;
        }
    }

    division(x, len, y, len, div, len, mod, len);        // Поделили мантиссы
    arr_cpy(mod, len, x, len);                           // Скопировали остаток, который получился в x для дальнейшего деления

    if(is_null_arr(div, M_LEN + 1))
    {
        shift_left(z, M_LEN + 1, 1);
        z[M_LEN] = div[0];
        (*i)++;
    }
    else
    {
        size_t k = 0;
        for(; k < M_LEN + 1 && div[k] == 0; k++);
        for(; k < M_LEN + 1 && *i < M_LEN + 1; k++)
        {
            shift_left(z, M_LEN + 1, 1);
            z[M_LEN] = div[k];
            (*i)++;
        }
    }

    if(is_null_arr(mod, M_LEN + 1))
        return 0;

    return division_mantissa(x, y, z, change_exp, e_sign, i);
}

int subtract_exponent(int x[], int x_sign, int y[], int y_sign, int z[], int *z_sign, size_t len)
{
    int x_y_cmp = arr_cmp(x, len, y, len);

    if(x_sign == y_sign && x_y_cmp >= 0)
    {
        *z_sign = x_sign;
        return subtract(x, len, y, len, z, len);
    }

    if(x_sign == y_sign && x_y_cmp < 0)
    {
        *z_sign = !x_sign;
        return subtract(y, len, x, len, z, len);
    }

    if(x_sign == 0 && y_sign == 1)
    {
        *z_sign = 0;
        return add(x, len, y, len, z, len);
    }

    *z_sign = 1;
    return add(x, len, y, len, z, len);
}
