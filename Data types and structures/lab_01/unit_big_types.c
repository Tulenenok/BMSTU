#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "big_int.h"
#include "big_double.h"
#include "big_types.h"

int is_arrays_equal(int arr1[], size_t len1, int arr2[], size_t len2)
{
    if(len1 != len2)
        return 0;
    for(size_t i = 0; i < len1; i++)
        if(arr1[i] != arr2[i])
            return 0;
    return 1;
}

int main(void)
{
    {
        big_int_t bi = { 0 };
        bi.data[DATA_LEN - 1] = 9;
        bi.data[DATA_LEN - 2] = 0;
        bi.data[DATA_LEN - 3] = 5;

        big_double_t x = { 0 };
        big_double_t perfect_x = {.is_negative_m = 0, .mantissa = {5, 0, 9}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 3}};

        if(!from_bi_to_bd(&bi, &x) &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )
            printf("Positive test  1 for from_bi_to_bd : PASSED\n");
        else
            printf("Positive test  1 for from_bi_to_bd : FAILED          !!!\n");
    }

    {
        big_int_t bi = { 0 };
        bi.is_negative = 1;
        bi.data[DATA_LEN - 1] = 8;
        bi.data[DATA_LEN - 2] = 7;

        big_double_t x = { 0 };
        big_double_t perfect_x = {.is_negative_m = 1, .mantissa = {7, 8}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 2}};

        if(!from_bi_to_bd(&bi, &x) &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )
            printf("Positive test  2 for from_bi_to_bd : PASSED\n");
        else
            printf("Positive test  2 for from_bi_to_bd : FAILED          !!!\n");
    }
    printf("\n");
///////////////////////

    {
        big_int_t bi = { 0 };
        bi.is_negative = 1;
        bi.data[DATA_LEN - 1] = 0;
        bi.data[DATA_LEN - 2] = 1;

        big_double_t bd = {.is_negative_m = 1, .mantissa = {2}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 1}};

        big_double_t x = { 0 };
        big_double_t perfect_x = {.is_negative_m = 0, .mantissa = {5}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 1}};
        if(!division_bi_bd(&bi, &bd, &x) &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )
            printf("Positive test  1 for division_bi_bd : PASSED\n");
        else
            printf("Positive test  1 for division_bi_bd : FAILED          !!!\n");
    }

    {
        big_int_t bi = { 0 };
        bi.is_negative = 1;
        bi.data[DATA_LEN - 1] = 1;
        bi.data[DATA_LEN - 2] = 1;

        big_double_t bd = {.is_negative_m = 0, .mantissa = { 2 }, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 1}};

        big_double_t x = { 0 };
        big_double_t perfect_x = {.is_negative_m = 1, .mantissa = {5, 5}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 1}};
        if(!division_bi_bd(&bi, &bd, &x) &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )
            printf("Positive test  2 for division_bi_bd : PASSED\n");
        else
            printf("Positive test  2 for division_bi_bd : FAILED          !!!\n");
    }

    {
        big_int_t bi = { 0 };
        bi.is_negative = 0;
        bi.data[DATA_LEN - 1] = 8;
        bi.data[DATA_LEN - 2] = 1;

        big_double_t bd = {.is_negative_m = 1, .mantissa = { 3 }, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 3}};

        big_double_t x = { 0 };
        big_double_t perfect_x = {.is_negative_m = 1, .mantissa = {6}, .is_negative_e = 1, .exponent = {0, 0, 0, 0, 1}};
        if(!division_bi_bd(&bi, &bd, &x) &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )
            printf("Positive test  3 for division_bi_bd : PASSED\n");
        else
            printf("Positive test  3 for division_bi_bd : FAILED          !!!\n");
    }

    {
        big_int_t bi = { 0 };
        bi.is_negative = 1;
        bi.data[DATA_LEN - 1] = 0;
        bi.data[DATA_LEN - 2] = 1;

        big_double_t bd = {.is_negative_m = 0, .mantissa = {0}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 0}};

        big_double_t x = { 0 };
        if(division_bi_bd(&bi, &bd, &x) == DIVISION_BY_ZERO)
            printf("Negative test  1 for division_bi_bd : PASSED\n");
        else
            printf("Negative test  1 for division_bi_bd : FAILED          !!!\n");
    }
    printf("\n");
////////////////////////
    {
        big_int_t bi = { 0 };
        bi.is_negative = 1;
        bi.data[DATA_LEN - 1] = 2;

        big_double_t bd = {.is_negative_m = 1, .mantissa = {1, 0}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 2}};

        big_double_t x = { 0 };
        big_double_t perfect_x = {.is_negative_m = 0, .mantissa = {5}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 1}};
        if(!division_bd_bi(&bd, &bi, &x) &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )
            printf("Positive test  1 for division_bd_bi : PASSED\n");
        else
            printf("Positive test  1 for division_bd_bi : FAILED          !!!\n");
    }

    {
        big_int_t bi = { 0 };
        bi.is_negative = 0;
        bi.data[DATA_LEN - 1] = 4;

        big_double_t bd = {.is_negative_m = 0, .mantissa = {1, 0}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 2}};

        big_double_t x = { 0 };
        big_double_t perfect_x = {.is_negative_m = 0, .mantissa = {2, 5}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 1}};
        if(!division_bd_bi(&bd, &bi, &x) &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )
            printf("Positive test  2 for division_bd_bi : PASSED\n");
        else
            printf("Positive test  2 for division_bd_bi : FAILED          !!!\n");
    }

    {
        big_int_t bi = { 0 };
        bi.is_negative = 0;
        bi.data[DATA_LEN - 1] = 0;
        bi.data[DATA_LEN - 2] = 1;

        big_double_t bd = {.is_negative_m = 1, .mantissa = {1}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 1}};

        big_double_t x = { 0 };
        big_double_t perfect_x = {.is_negative_m = 1, .mantissa = {1}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 0}};
        if(!division_bd_bi(&bd, &bi, &x) &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )
            printf("Positive test  3 for division_bd_bi : PASSED\n");
        else
            printf("Positive test  3 for division_bd_bi : FAILED          !!!\n");
    }
    {
        big_int_t bi = { 0 };

        big_double_t bd = {.is_negative_m = 0, .mantissa = {0}, .is_negative_e = 0, .exponent = {0, 0, 0, 0, 0}};

        big_double_t x = { 0 };
        if(division_bd_bi(&bd, &bi, &x) == DIVISION_BY_ZERO)
            printf("Negative test  1 for division_bd_bi : PASSED\n");
        else
            printf("Negative test  1 for division_bd_bi : FAILED          !!!\n");
    }
    return EXIT_SUCCESS;
}
