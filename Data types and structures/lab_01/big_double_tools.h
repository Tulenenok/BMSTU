#ifndef _BIG_DOUBLE_TOOLS_H_
#define _BIG_DOUBLE_TOOLS_H_

#include <stdio.h>
#include <stdlib.h>

// Делит два целых числа, возвращает целое число и экспоненту
int division_mantissa(int x[], int y[], int z[], int change_exp[], int *e_sign, size_t *i);

// Вычитает экспоненту
int subtract_exponent(int x[], int x_sign, int y[], int y_sign, int z[], int *z_sign, size_t len);

#endif // BIG_DOUBLE_TOOLS_H
