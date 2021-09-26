#include "big_double.h"
#include "big_int.h"
#include "big_types.h"
#include "tools.h"


int from_bi_to_bd(big_int_t *bi, big_double_t *bd)
{
    bd->is_negative_m = bi->is_negative;

    for(size_t i = 0, j = 1; i < DATA_LEN; i++, j++)
        bd->mantissa[j] = bi->data[i];
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
