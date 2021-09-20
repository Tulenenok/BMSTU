#ifndef _BIG_DOUBLE_H_
#define _BIG_DOUBLE_H_

#include <stdio.h>
#include <stdlib.h>

#define M_LEN 30
#define E_LEN 5

#define OVERFLOW 2
#define IS_NOT_SCIENTIFIC 8
#define DIVISION_BY_ZERO 4

typedef struct
{
    int is_negative_m;
    int mantissa[M_LEN];
    int is_negative_e;
    int exponent[E_LEN];
} big_double_t;

int is_big_double(char s[]);

int from_str_to_big_double(char s[], big_double_t *x);

void from_big_double_to_str(char s[], big_double_t *x);

int division_big_double(big_double_t *x, big_double_t *y, big_double_t *z);

int is_equal(big_double_t *x, big_double_t *y);

// Функция считывает из файла число типа big_int_t
// Возвращает ERROR_WITH_FILE, если произошла ошибка при чтении
//            BLANK_STRING, если ввод пустой
//            IS_NOT_SCIENTIFIC, если число не является вещественным
//            OVERFLOW, если число слишком большое
//            EXIT_SUCCESS, если все удачно
int big_double_scan(FILE *f, big_double_t *x);

void big_double_print(FILE *f, big_double_t *x);

#endif // _BIG_DOUBLE_H_
