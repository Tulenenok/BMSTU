#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "big_double.h"

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
        char x[] = "-1.8et8";
        if(is_not_big_double(x))
            printf("Negative test 1 for is_big_int : PASSED\n");
        else
            printf("Negative test 1 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-89e0.01";
        if(is_not_big_double(x))
            printf("Negative test 2 for is_big_int : PASSED\n");
        else
            printf("Negative test 2 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-0.0000009e+67";
        if(!is_not_big_double(x))
            printf("Positive test 1 for is_big_int : PASSED\n");
        else
            printf("Positive test 1 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-9990e+986";
        if(!is_not_big_double(x))
            printf("Positive test 2 for is_big_int : PASSED\n");
        else
            printf("Positive test 2 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-0E0";
        if(!is_not_big_double(x))
            printf("Positive test 3 for is_big_int : PASSED\n");
        else
            printf("Positive test 3 for is_big_int : FAILED          !!!\n");
    }

    printf("\n");
///////////////////////////

    {
        char s[] = "15";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 0,
                                  .mantissa = { 0 },
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0, 0}};
        perfect_x.mantissa[M_LEN - 1] = 5;
        perfect_x.mantissa[M_LEN - 2] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test  1 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test  1 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "1.5";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 0,
                                  .mantissa = {0},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 1}};
        perfect_x.mantissa[M_LEN - 1] = 5;
        perfect_x.mantissa[M_LEN - 2] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test  2 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test  2 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = ".55678";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 0,
                                  .mantissa = { 0 },
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 5}};
        perfect_x.mantissa[M_LEN - 1] = 8;
        perfect_x.mantissa[M_LEN - 2] = 7;
        perfect_x.mantissa[M_LEN - 3] = 6;
        perfect_x.mantissa[M_LEN - 4] = 5;
        perfect_x.mantissa[M_LEN - 5] = 5;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test  3 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test  3 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "+123.";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 0,
                                  .mantissa = {0},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0}};
        perfect_x.mantissa[M_LEN - 1] = 3;
        perfect_x.mantissa[M_LEN - 2] = 2;
        perfect_x.mantissa[M_LEN - 3] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test  4 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test  4 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-8000.000";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {0},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 3}};
        perfect_x.mantissa[M_LEN - 7] = 8;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test  5 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test  5 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-0.1E10";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {0},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0, 9}};
        perfect_x.mantissa[M_LEN - 1] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test  6 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test  6 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-0.01009E-103";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {0},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 1, 0, 8}};
        perfect_x.mantissa[M_LEN - 1] = 9;
        perfect_x.mantissa[M_LEN - 2] = 0;
        perfect_x.mantissa[M_LEN - 3] = 0;
        perfect_x.mantissa[M_LEN - 4] = 1;
        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test  7 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test  7 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-1.e7987";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {0},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 7, 9, 8, 7}};
        perfect_x.mantissa[M_LEN - 1] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test  8 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test  8 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-14.5e9998";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = { 0 },
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 9, 9, 9, 7}};
        perfect_x.mantissa[M_LEN - 1] = 5;
        perfect_x.mantissa[M_LEN - 2] = 4;
        perfect_x.mantissa[M_LEN - 3] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test  9 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test  9 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-1.1234567890e-9990";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = { 0 },
                                  .is_negative_e = 1,
                                  .exponent = {0, 1, 0, 0, 0, 0}};
        perfect_x.mantissa[M_LEN - 1] = 0;
        perfect_x.mantissa[M_LEN - 2] = 9;
        perfect_x.mantissa[M_LEN - 3] = 8;
        perfect_x.mantissa[M_LEN - 4] = 7;
        perfect_x.mantissa[M_LEN - 5] = 6;
        perfect_x.mantissa[M_LEN - 6] = 5;
        perfect_x.mantissa[M_LEN - 7] = 4;
        perfect_x.mantissa[M_LEN - 8] = 3;
        perfect_x.mantissa[M_LEN - 9] = 2;
        perfect_x.mantissa[M_LEN - 10] = 1;
        perfect_x.mantissa[M_LEN - 11] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test 10 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test 10 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-1.1234567890e-99990";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = { 0 },
                                  .is_negative_e = 1,
                                  .exponent = {1, 0, 0, 0, 0, 0}};
        perfect_x.mantissa[M_LEN - 1] = 0;
        perfect_x.mantissa[M_LEN - 2] = 9;
        perfect_x.mantissa[M_LEN - 3] = 8;
        perfect_x.mantissa[M_LEN - 4] = 7;
        perfect_x.mantissa[M_LEN - 5] = 6;
        perfect_x.mantissa[M_LEN - 6] = 5;
        perfect_x.mantissa[M_LEN - 7] = 4;
        perfect_x.mantissa[M_LEN - 8] = 3;
        perfect_x.mantissa[M_LEN - 9] = 2;
        perfect_x.mantissa[M_LEN - 10] = 1;
        perfect_x.mantissa[M_LEN - 11] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test 11 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test 11 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-12e-2";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = { 0 },
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 2}};
        perfect_x.mantissa[M_LEN - 1] = 2;
        perfect_x.mantissa[M_LEN - 2] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test 12 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test 12 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-123456789012345678901234567890e-99999";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                                  .is_negative_e = 1,
                                  .exponent = {0, 9, 9, 9, 9, 9}};
        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test 13 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test 13 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-12345678901234567890123456780.9e-10";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 9},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 1, 1}};
        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test 14 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test 14 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-0.1e-99999";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = { 0 },
                                  .is_negative_e = 1,
                                  .exponent = {1, 0, 0, 0, 0, 0}};
        perfect_x.mantissa[M_LEN - 1] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test 15 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test 15 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-1.23456789012345678901234567890e30";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0, 1}};
        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test 16 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test 16 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-1.23456789012345678901234567890e28";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 1}};
        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test 17 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test 17 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-0.01e1";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = { 0 },
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 1}};
        perfect_x.mantissa[M_LEN - 1] = 1;

        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test 18 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test 18 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-1.1e78E9";
        big_double_t x = {0};
        if(from_str_to_big_double(s, &x))
            printf("Negative test 1 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 1 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-.e9";
        big_double_t x = {0};
        if(from_str_to_big_double(s, &x))
            printf("Negative test 2 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 2 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-1e";
        big_double_t x = {0};
        if(from_str_to_big_double(s, &x))
            printf("Negative test 3 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 3 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-0.8.e0";
        big_double_t x = {0};
        if(from_str_to_big_double(s, &x))
            printf("Negative test 4 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 4 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-1e999999";
        big_double_t x = {0};
        if(from_str_to_big_double(s, &x))
            printf("Negative test 5 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 5 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-999999999999999999999999999999.9e99999";
        big_double_t x = {0};

        if(from_str_to_big_double(s, &x))
            printf("Negative test 6 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 6 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-.9999999999999999999999999999999e99999";
        big_double_t x = {0};

        if(from_str_to_big_double(s, &x))
            printf("Negative test 7 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 7 for from_str_to_big_double : FAILED          !!!\n");
    }

    printf("\n");

    {
        char s[] = "";
        char perfect_s[] = "-0.1E+7988";
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = { 0 },
                          .is_negative_e = 0,
                          .exponent = {0, 0, 7, 9, 8, 8}};
        x.mantissa[M_LEN - 1] = 1;

        from_big_double_to_str(s, &x);
        if(!strcmp(s, perfect_s))
            printf("Positive test 1 for from_big_double_to_str : PASSED\n");
        else
            printf("Positive test 1 for from_big_double_to_str : FAILED          !!!\n");
    }

    {
        char s[] = "";
        char perfect_s[] = "-0.12345E-10";
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = { 0 },
                          .is_negative_e = 1,
                          .exponent = {0, 0, 0, 0, 1, 0}};
        x.mantissa[M_LEN - 1] = 5;
        x.mantissa[M_LEN - 2] = 4;
        x.mantissa[M_LEN - 3] = 3;
        x.mantissa[M_LEN - 4] = 2;
        x.mantissa[M_LEN - 5] = 1;

        from_big_double_to_str(s, &x);
        if(!strcmp(s, perfect_s))
            printf("Positive test 2 for from_big_double_to_str : PASSED\n");
        else
            printf("Positive test 2 for from_big_double_to_str : FAILED          !!!\n");
    }

    {
        char s[] = "";
        char perfect_s[] = "+0.1009E-104";
        big_double_t x = {.is_negative_m = 0,
                          .mantissa = { 0 },
                          .is_negative_e = 1,
                          .exponent = {0, 0, 0, 1, 0, 4}};
        x.mantissa[M_LEN - 1] = 9;
        x.mantissa[M_LEN - 2] = 0;
        x.mantissa[M_LEN - 3] = 0;
        x.mantissa[M_LEN - 4] = 1;

        from_big_double_to_str(s, &x);
        if(!strcmp(s, perfect_s))
            printf("Positive test 3 for from_big_double_to_str : PASSED\n");
        else
            printf("Positive test 3 for from_big_double_to_str : FAILED          !!!\n");
    }

    {
        char s[] = "";
        char perfect_s[] = "+0.0E+0";
        big_double_t x = {.is_negative_m = 0,
                          .mantissa = {0},
                          .is_negative_e = 0,
                          .exponent = {0}};

        from_big_double_to_str(s, &x);
        if(!strcmp(s, perfect_s))
            printf("Positive test 4 for from_big_double_to_str : PASSED\n");
        else
            printf("Positive test 4 for from_big_double_to_str : FAILED          !!!\n");
    }

    printf("\n");
/////////////////////////////

    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = { 0 },
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0, 0}};
        x.mantissa[M_LEN - 1] = 5;
        x.mantissa[M_LEN - 2] = 1;

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0, 1}};
        y.mantissa[M_LEN - 1] = 3;

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = {0},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 1}};
        perfect_z.mantissa[M_LEN - 1] = 5;

        big_double_t z = {0};

        if(!division_big_double(&x, &y, &z) &&
                is_arrays_equal(z.mantissa, M_LEN, perfect_z.mantissa, M_LEN) &&
                is_arrays_equal(z.exponent, E_LEN, perfect_z.exponent, E_LEN) &&
                z.is_negative_m == perfect_z.is_negative_m &&
                z.is_negative_e == perfect_z.is_negative_e)
            printf("Positive test 1 for division_big_double : PASSED\n");
        else
            printf("Positive test 1 for division_big_double : FAILED          !!!\n");
    }

    {
        big_double_t x = {.is_negative_m = 0,
                          .mantissa = { 0 },
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0, 2}};
        x.mantissa[M_LEN - 1] = 5;
        x.mantissa[M_LEN - 2] = 5;

        big_double_t y = {.is_negative_m = 0,
                          .mantissa = {0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0, 1}};
        y.mantissa[M_LEN - 1] = 5;

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = { 0 },
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0, 1}};
        perfect_z.mantissa[M_LEN - 1] = 1;
        perfect_z.mantissa[M_LEN - 2] = 1;

        big_double_t z = {0};

        if(!division_big_double(&x, &y, &z) &&
                is_arrays_equal(z.mantissa, M_LEN, perfect_z.mantissa, M_LEN) &&
                is_arrays_equal(z.exponent, E_LEN, perfect_z.exponent, E_LEN) &&
                z.is_negative_m == perfect_z.is_negative_m &&
                z.is_negative_e == perfect_z.is_negative_e)
            printf("Positive test 2 for division_big_double : PASSED\n");
        else
            printf("Positive test 2 for division_big_double : FAILED          !!!\n");
    }

    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {0},
                          .is_negative_e = 1,
                          .exponent = {0, 0, 0, 0, 0, 3}};
        x.mantissa[M_LEN - 3] = 8;                               // Это 800 !!!

        big_double_t y = {.is_negative_m = 0,
                          .mantissa = {0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0, 1}};
        y.mantissa[M_LEN - 1] = 5;

        big_double_t perfect_z = {.is_negative_m = 1,
                                  .mantissa = {0},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 3}};
        perfect_z.mantissa[M_LEN - 1] = 6;
        perfect_z.mantissa[M_LEN - 2] = 1;

        big_double_t z = {0};

        if(!division_big_double(&x, &y, &z) &&
                is_arrays_equal(z.mantissa, M_LEN, perfect_z.mantissa, M_LEN) &&
                is_arrays_equal(z.exponent, E_LEN, perfect_z.exponent, E_LEN) &&
                z.is_negative_m == perfect_z.is_negative_m &&
                z.is_negative_e == perfect_z.is_negative_e)
            printf("Positive test 3 for division_big_double : PASSED\n");
        else
            printf("Positive test 3 for division_big_double : FAILED          !!!\n");
    }

    {
        big_double_t x = {.is_negative_m = 0,
                          .mantissa = {0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0, 2}};
        x.mantissa[M_LEN - 1] = 5;
        x.mantissa[M_LEN - 2] = 1;

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0, 2}};
        y.mantissa[M_LEN - 2] = 8;

        big_double_t perfect_z = {.is_negative_m = 1,
                                  .mantissa = {0},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 4}};
        perfect_z.mantissa[M_LEN - 1] = 5;
        perfect_z.mantissa[M_LEN - 2] = 7;
        perfect_z.mantissa[M_LEN - 3] = 8;
        perfect_z.mantissa[M_LEN - 4] = 1;

        big_double_t z = {0};

        if(!division_big_double(&x, &y, &z) &&
                is_arrays_equal(z.mantissa, M_LEN, perfect_z.mantissa, M_LEN) &&
                is_arrays_equal(z.exponent, E_LEN, perfect_z.exponent, E_LEN) &&
                z.is_negative_m == perfect_z.is_negative_m &&
                z.is_negative_e == perfect_z.is_negative_e)
            printf("Positive test 4 for division_big_double : PASSED\n");
        else
            printf("Positive test 4 for division_big_double : FAILED          !!!\n");
    }

    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {0},
                          .is_negative_e = 1,
                          .exponent = {0, 0, 0, 0, 0, 2}};
        x.mantissa[M_LEN - 1] = 2;

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {0, 0},
                          .is_negative_e = 1,
                          .exponent = {0, 0, 0, 0, 0, 2}};
        y.mantissa[M_LEN - 2] = 5;

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = {0},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 2}};
        perfect_z.mantissa[M_LEN - 1] = 4;

        big_double_t z = {0};

        if(!division_big_double(&x, &y, &z) &&
                is_arrays_equal(z.mantissa, M_LEN, perfect_z.mantissa, M_LEN) &&
                is_arrays_equal(z.exponent, E_LEN, perfect_z.exponent, E_LEN) &&
                z.is_negative_m == perfect_z.is_negative_m &&
                z.is_negative_e == perfect_z.is_negative_e)
            printf("Positive test 5 for division_big_double : PASSED\n");
        else
            printf("Positive test 5 for division_big_double : FAILED          !!!\n");
    }


    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = { 0 },
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0}};
        x.mantissa[M_LEN - 1] = 1;

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {0},
                          .is_negative_e = 1,
                          .exponent = {0, 0, 0, 0, 1}};
        y.mantissa[M_LEN - 1] = 1;

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = {0},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 1}};
        perfect_z.mantissa[M_LEN - 1] = 1;

        big_double_t z = {0};

        if(!division_big_double(&x, &y, &z) &&
                is_arrays_equal(z.mantissa, M_LEN, perfect_z.mantissa, M_LEN) &&
                is_arrays_equal(z.exponent, E_LEN, perfect_z.exponent, E_LEN) &&
                z.is_negative_m == perfect_z.is_negative_m &&
                z.is_negative_e == perfect_z.is_negative_e)
            printf("Positive test 6 for division_big_double : PASSED\n");
        else
            printf("Positive test 6 for division_big_double : FAILED          !!!\n");
    }


    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0, 1}};
        x.mantissa[M_LEN - 1] = 5;
        x.mantissa[M_LEN - 2] = 6;

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0, 3}};
        y.mantissa[M_LEN - 3] = 5;                                 // это 500!!!

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = {0},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 0, 4}};
        perfect_z.mantissa[M_LEN - 1] = 3;
        perfect_z.mantissa[M_LEN - 2] = 1;

        big_double_t z = {0};

        if(!division_big_double(&x, &y, &z) &&
                is_arrays_equal(z.mantissa, M_LEN, perfect_z.mantissa, M_LEN) &&
                is_arrays_equal(z.exponent, E_LEN, perfect_z.exponent, E_LEN) &&
                z.is_negative_m == perfect_z.is_negative_m &&
                z.is_negative_e == perfect_z.is_negative_e)
            printf("Positive test 7 for division_big_double : PASSED\n");
        else
            printf("Positive test 7 for division_big_double : FAILED          !!!\n");
    }

//    {
//        big_double_t x = {.is_negative_m = 1,
//                          .mantissa = {0},
//                          .is_negative_e = 0,
//                          .exponent = {0, 0, 0, 0, 0, 0}};
//        x.mantissa[M_LEN - 1] = 1;

//        big_double_t y = {.is_negative_m = 1,
//                          .mantissa = {0},
//                          .is_negative_e = 0,
//                          .exponent = {0, 0, 0, 0, 0, 0}};
//        y.mantissa[M_LEN - 1] = 1;
//        y.mantissa[M_LEN - 2] = 1;

//        big_double_t perfect_z = {.is_negative_m = 0,
//                                  .mantissa = {0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 0, 0},
//                                  .is_negative_e = 0,
//                                  .exponent = {0, 0, 0, 0, 0, 0}};

//        big_double_t z = {0};

//        if(!division_big_double(&x, &y, &z) &&
//                is_arrays_equal(z.mantissa, M_LEN, perfect_z.mantissa, M_LEN) &&
//                is_arrays_equal(z.exponent, E_LEN, perfect_z.exponent, E_LEN) &&
//                z.is_negative_m == perfect_z.is_negative_m &&
//                z.is_negative_e == perfect_z.is_negative_e)
//            printf("Positive test 8 for division_big_double : PASSED\n");
//        else
//            printf("Positive test 8 for division_big_double : FAILED          !!!\n");
//    }

    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {1},
                          .is_negative_e = 0,
                          .exponent = {9, 9, 9, 9, 8}};

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {1},
                          .is_negative_e = 1,
                          .exponent = {0, 0, 0, 0, 2}};
        big_double_t z = {0};

        if(division_big_double(&x, &y, &z))
            printf("Negative test 1 for division_big_double : PASSED\n");
        else
            printf("Negative test 1 for division_big_double : FAILED          !!!\n");
    }


    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {1},
                          .is_negative_e = 0,
                          .exponent = {9, 9, 9, 9, 7}};

        big_double_t y = {0};
        big_double_t z = {0};

        if(division_big_double(&x, &y, &z))
            printf("Negative test 2 for division_big_double : PASSED\n");
        else
            printf("Negative test 2 for division_big_double : FAILED          !!!\n");
    }

    printf("\n");
//////////////////////
    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {1, 5},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 2}};

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {3},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 1}};

        if(!is_equal(&x, &y))
            printf("Positive test 1 for is_equal : PASSED\n");
        else
            printf("Positive test 1 for is_equal : FAILED          !!!\n");
    }

    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {1, 5},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 2}};

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {1, 5},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 2}};

        if(is_equal(&x, &y))
            printf("Positive test 2 for is_equal : PASSED\n");
        else
            printf("Positive test 2 for is_equal : FAILED          !!!\n");
    }

    printf("\n");
/////////////////

    {
        FILE *f = fopen("unit_tests/pos_01_in_big_double_scan.txt", "r");
        if(!f)
             printf("Positive test 1 for big_double_scan : FAILED          !!!   FILE\n");
        big_double_t x = { 0 };
        big_double_t perfect_x = {.is_negative_m = 0,
                               .mantissa = { 0 },
                               .is_negative_e = 0,
                               .exponent = {0, 0, 0, 0, 0}};
        perfect_x.mantissa[M_LEN - 1] = 3;
        perfect_x.mantissa[M_LEN - 2] = 2;
        perfect_x.mantissa[M_LEN - 3] = 1;

        if(!big_double_scan(f, &x) &&
            x.is_negative_m == perfect_x.is_negative_m &&
            x.is_negative_e == perfect_x.is_negative_e &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN))
            printf("Positive test 1 for big_double_scan : PASSED\n");
        else
            printf("Positive test 1 for big_double_scan : FAILED          !!!\n");
        fclose(f);
    }

    {
        FILE *f = fopen("unit_tests/pos_02_in_big_double_scan.txt", "r");
        if(!f)
             printf("Positive test 2 for big_double_scan : FAILED          !!!   FILE\n");
        big_double_t x = { 0 };
        big_double_t perfect_x = {.is_negative_m = 1,
                               .mantissa = {0},
                               .is_negative_e = 1,
                               .exponent = {0, 0, 0, 0, 0, 3}};
        perfect_x.mantissa[M_LEN - 3] = 1;

        if(!big_double_scan(f, &x) &&
            x.is_negative_m == perfect_x.is_negative_m &&
            x.is_negative_e == perfect_x.is_negative_e &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN))
            printf("Positive test 2 for big_double_scan : PASSED\n");
        else
            printf("Positive test 2 for big_double_scan : FAILED          !!!\n");
        fclose(f);
    }

    {
        FILE *f = fopen("unit_tests/neg_01_in_big_double_scan.txt", "r");
        if(!f)
             printf("Negative test 1 for big_double_scan : FAILED          !!!   FILE\n");
        big_double_t x = { 0 };

        if(big_double_scan(f, &x))
            printf("Negative test 1 for big_double_scan : PASSED\n");
        else
            printf("Negative test 1 for big_double_scan : FAILED          !!!\n");
        fclose(f);
    }

    {
        FILE *f = fopen("unit_tests/neg_02_in_big_double_scan.txt", "r");
        if(!f)
             printf("Negative test 2 for big_double_scan : FAILED          !!!   FILE\n");
        big_double_t x = { 0 };

        if(big_double_scan(f, &x))
            printf("Negative test 2 for big_double_scan : PASSED\n");
        else
            printf("Negative test 2 for big_double_scan : FAILED          !!!\n");
        fclose(f);
    }

    return EXIT_SUCCESS;
}
