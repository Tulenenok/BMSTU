#ifndef _BIG_DOUBLE_H_
#define _BIG_DOUBLE_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_M_LEN 30
#define MAX_E_LEN 5

#define M_LEN 31
#define E_LEN 6

#define OVERFLOW 2
#define IS_NOT_SCIENTIFIC 8
#define DIVISION_BY_ZERO 4

#define TOO_LARGE_M 12
#define TOO_LARGE_E 13

// Число предствляется в следующем виде (is_negative_m)0.(mantissa)E(is_negative_e)(exponent)
typedef struct
{
    int is_negative_m;
    int mantissa[M_LEN];
    int is_negative_e;
    int exponent[E_LEN];
} big_double_t;

// Проверяет, можно ли перевести встроку в число типа big_double_t
// Возвращает TRUE, если числа равны
//             FALSE, в ином случае
int is_not_big_double(char s[]);

// Перевеодит строку в число типа big_double_y
// Возвращает OVERFLOW, если происходит переполнение
//            EXIT_SUCCESS, если все удачно
int from_str_to_big_double(char s[], big_double_t *x);

// Переводит число типа big_double_t в строку
void from_big_double_to_str(char s[], big_double_t *x);

// Делит два числа типа big_double
// Возвращает DIVISION_BY_ZERO, если мы пытаемся поделить на 0
//            OVERFLOW, если в процессе деления происходит переполнение
//            EXIT_SUCCESS, если все удачно
int division_big_double(big_double_t *x, big_double_t *y, big_double_t *z);

// Проверяет, равны ли два числа типа big_double_t
// Возвращает TRUE, если числа равны
//             FALSE, в ином случае
int is_equal(big_double_t *x, big_double_t *y);

// Функция считывает из файла число типа big_int_t
// Возвращает ERROR_WITH_FILE, если произошла ошибка при чтении
//            BLANK_STRING, если ввод пустой
//            IS_NOT_SCIENTIFIC, если число не является вещественным
//            OVERFLOW, если число слишком большое
//            EXIT_SUCCESS, если все удачно
int big_double_scan(FILE *f, big_double_t *x);

// Печатает число типа big_double_t
void big_double_print(FILE *f, big_double_t *x);

#endif // _BIG_DOUBLE_H_
