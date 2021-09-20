#ifndef _BIG_TYPES_H_
#define _BIG_TYPES_H_

#include <stdio.h>
#include <stdlib.h>

// Переводит число типа big_int_t в число типа big_double_t
// Сейчас всегда возвращает EXIT_SUCCESS, но можно подключить доп проверки,
// чтобы контролировать переполение и длины мантисс
int from_bi_to_bd(big_int_t *bi, big_double_t *bd);

// Делит число типа big_int_t на чилсо типа big_double_t
// Возвращает DIVISION_BY_ZERO, если была произведена попытка деления на 0,
//            OVERFLOW, если в результате деления произошло переполнение
//            EXIT_SUCCESS, в ином случае
int division_bi_bd(big_int_t *bi, big_double_t *bd, big_double_t *res);

// Делит число типа big_double_t на чилсо типа big_int_t
// Возвращает DIVISION_BY_ZERO, если была произведена попытка деления на 0,
//            OVERFLOW, если в результате деления произошло переполнение
//            EXIT_SUCCESS, в ином случае
int division_bd_bi(big_double_t *bd, big_int_t *bi, big_double_t *res);

#endif // _BIG_TYPES_H_
