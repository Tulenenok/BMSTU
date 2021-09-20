#include "big_double.h"
#include "big_int.h"
#include "big_types.h"
#include "tools.h"

// #define ERROR_WITH_LEN 3

int from_bi_to_bd(big_int_t *bi, big_double_t *bd)
{
// В нашем случае, это не нужная проверка, однако при изменении этих параметров может пригодится
//    if(DATA_LEN > M_LEN)
//        return ERROR_WITH_LEN;

    bd->is_negative_m = bi->is_negative;

    size_t i = 0, j = 0;
    for(; i < DATA_LEN && bi->data[i] == 0; i++);
    for(; i < DATA_LEN; i++, j++)
    {
        bd->mantissa[j] = bi->data[i];
        increase_by_one(bd->exponent, E_LEN);
//        if(increase_by_one(bd->exponent, E_LEN))
//            return OVERFLOW;
    }
    return EXIT_SUCCESS;
}

int division_bi_bd(big_int_t *bi, big_double_t *bd, big_double_t *res)
{
    big_double_t t = { 0 };
    from_bi_to_bd(bi, &t);
    return division_big_double(&t, bd, res);
}

int division_bd_bi(big_double_t *bd, big_int_t *bi, big_double_t *res)
{
    big_double_t t = { 0 };
    from_bi_to_bd(bi, &t);
    return division_big_double(bd, &t, res);
}

// Собрать общую прогу из считывания, деления, вывода
// Написать функциональные тестики
