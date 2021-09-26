#include "tools.h"
#include "big_double.h"
#include "big_double_tools.h"

void print_arr(int arr[], size_t len)
{
    for(size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int division_mantissa(int x[], int y[], int z[], int change_exp[], int *e_sign, size_t *i)
{
    if(*i >= M_LEN)                                   // Выход из рекурсии (заполнили всю мантиссу)
        return 0;

    int div[M_LEN] = {0}, mod[M_LEN] = {0};              // Массивы для промежуточных вычислений

    if(arr_cmp(x, M_LEN, y, M_LEN) < 0)                  // Увеличили мантиссу на 10
    {
        shift_left(x, M_LEN, 1);
        reduce_one_with_sign(change_exp, E_LEN, e_sign); // Учли это в экспоненте
    }

    size_t x_i = 0, y_i = 0;                             // Подгоняем у делителя разряды до разрядов числителя
    for(; x_i < M_LEN && x[x_i] == 0; x_i++);
    for(; y_i < M_LEN && y[y_i] == 0; y_i++);
    if(arr_cmp(x, M_LEN, y, M_LEN) > 0 && x_i < y_i)
    {
        shift_left(y, M_LEN, y_i - x_i - 1);
        while(x_i < y_i - 1)
        {
            increase_one_with_sign(change_exp, E_LEN, e_sign);
            y_i--;
        }
    }

//    printf("X = ");
//    print_arr(x, M_LEN);
//    printf("Y = ");
//    print_arr(y, M_LEN);

    division(x, M_LEN, y, M_LEN, div, M_LEN, mod, M_LEN);        // Поделили мантиссы
//    printf("D = ");
//    print_arr(div, M_LEN);
//    printf("M = ");
//    print_arr(mod, M_LEN);
//    printf("Z = ");
//    print_arr(z, M_LEN);
//    printf("I = %zu\n", *i);
//    printf("C = %d\n", *change_exp);
//    printf("\n");

    arr_cpy(mod, M_LEN, x, M_LEN);                               // Скопировали остаток, который получился в x для дальнейшего деления
    if(is_null_arr(div, M_LEN))
    {
        shift_left(z, M_LEN, 1);
        z[M_LEN] = div[0];
        (*i)++;
    }
    else
    {
        size_t k = 0;
        for(; k < M_LEN && div[k] == 0; k++);
        for(; k < M_LEN && *i < M_LEN; k++)
        {
            shift_left(z, M_LEN, 1);
            z[M_LEN - 1] = div[k];
            (*i)++;
        }
    }

    if(is_null_arr(mod, M_LEN))
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
