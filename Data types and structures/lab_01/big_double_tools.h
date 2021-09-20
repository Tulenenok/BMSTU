#ifndef _BIG_DOUBLE_TOOLS_H_
#define _BIG_DOUBLE_TOOLS_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int is_negative_m;
    int mantissa[M_LEN + 1];
    int is_negative_e;
    int exponent[E_LEN];
} bd_tool_t;

// Делит два целых числа, возвращает целое число и экспоненту
int division_mantissa(int x[], int y[], int z[], int change_exp[], int *e_sign, size_t *i);

// Вычитает экспоненту
int subtract_exponent(int x[], int x_sign, int y[], int y_sign, int z[], int *z_sign, size_t len);

// Переводит структуру вида big_double в bd_tool
// Возвращает OVERFLOW, в случае переполнения
//            EXIT_SUCCESS, если все удачно
int from_bd_to_bd_tool(big_double_t *x, bd_tool_t *y);

// Переводит структуру вида big_tool в big_double
// Возвращает OVERFLOW, в случае переполнения
//            EXIT_SUCCESS, если все удачно
int from_bd_tool_to_bd(bd_tool_t *x, big_double_t *y);

#endif // BIG_DOUBLE_TOOLS_H
