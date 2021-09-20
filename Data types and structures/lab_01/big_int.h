#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#include <stdio.h>
#include <stdlib.h>

#define DATA_LEN 30

#define IS_NOT_BIG_INT 9

typedef struct
{
    int is_negative;
    int data[DATA_LEN];
} big_int_t;

// Функция проверяет, является ли переданная строка числом типа big_int_t
int is_big_int(char x[]);

// Функция переводит строку в число типа big_int_t. В случае успеха возвращает 0, иначе любое ненулевое число
int from_str_to_big_int(char str[], big_int_t *x);

// Функция переводит число типа big_int_t в строку
void from_big_int_to_str(big_int_t *x, char str[]);

// Функция переводит число типа int в число типа big_int_t
void from_int_to_big_int(int x, big_int_t *res);

// Функция печатает в файл число типа big_int_t
void big_int_print(FILE *f, big_int_t *x);

// Функция считывает из файла число типа big_int_t
// Возвращает ERROR_WITH_FILE, если произошла ошибка при чтении
//            BLANK_STRING, если ввод пустой
//            IS_NOT_BIG_INT, если число нельзя привести к типу big_int
//            EXIT_SUCCESS, если все удачно
int big_int_scan(FILE *f, big_int_t *x);

// Функция сравнивает два числа типа big_int_t.
// Возвращает число меньше 0, если первое число меньше второго, 0 если равны, больше 0 в ином случае
int big_int_cmp(big_int_t *x, big_int_t *y);

// Функция складывает два целых числа типа big_int_t. В случае успеха возвращает 0, иначе любое ненулевое число.
int big_int_add(big_int_t *x, big_int_t *y, big_int_t *sum);

// Функция вычитает два целых числа типа big_int_t. В случае успеха возвращает 0, иначе любое ненулевое число.
int big_int_diff(big_int_t *x, big_int_t *y, big_int_t *diff);

#endif // _BIG_INT_H_
