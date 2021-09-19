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
        if(!is_big_double(x))
            printf("Negative test 1 for is_big_int : PASSED\n");
        else
            printf("Negative test 1 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-89e0.01";
        if(!is_big_double(x))
            printf("Negative test 2 for is_big_int : PASSED\n");
        else
            printf("Negative test 2 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-0.0000009e+67";
        if(is_big_double(x))
            printf("Positive test 1 for is_big_int : PASSED\n");
        else
            printf("Positive test 1 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-9990e+986";
        if(is_big_double(x))
            printf("Positive test 2 for is_big_int : PASSED\n");
        else
            printf("Positive test 2 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-0E0";
        if(is_big_double(x))
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
                                  .mantissa = {1, 5},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 2}};
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
                                  .mantissa = {1, 5},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 1}};
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
                                  .mantissa = {5, 5, 6, 7, 8},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0}};
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
                                  .mantissa = {1, 2, 3},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 3}};
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
                                  .mantissa = {8},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 4}};
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
                                  .mantissa = {1},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 1, 0}};
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
                                  .mantissa = {0, 1, 0, 0, 9},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 1, 0, 3}};
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
                                  .mantissa = {1},
                                  .is_negative_e = 0,
                                  .exponent = {0, 7, 9, 8, 8}};
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
                                  .mantissa = {1, 4, 5},
                                  .is_negative_e = 0,
                                  .exponent = {1, 0, 0, 0, 0}};
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
        char s[] = "-1234567890.5e9990";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 5},
                                  .is_negative_e = 0,
                                  .exponent = {1, 0, 0, 0, 0}};
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
        char s[] = "-123.45e-13";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {1, 2, 3, 4, 5},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 1, 0}};
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
                                  .mantissa = {1, 2},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0}};
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
        char s[] = "-123456789012345678901234567890e-10";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 2, 0}};
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
        char s[] = "-123456789012345678901234567890.9e-10";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 2, 0}};
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
                                  .mantissa = {1},
                                  .is_negative_e = 1,
                                  .exponent = {9, 9, 9, 9, 9}};
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
        char s[] = "-999999999999999999999999999999.9e-30";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {1},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 1}};
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
        char s[] = "-1e-1";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {1},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0}};
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
        char s[] = "-9999999999999999999999999999999999e-31";
        big_double_t x = {0};
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {1},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0}};
        if(from_str_to_big_double(s, &x) == 0 &&
            x.is_negative_m == perfect_x.is_negative_m                    &&
            x.is_negative_e == perfect_x.is_negative_e                    &&
            is_arrays_equal(x.mantissa, M_LEN, perfect_x.mantissa, M_LEN) &&
            is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) )

            printf("Positive test 18 for from_str_to_big_double : PASSED\n");
        else
            printf("Positive test 18 for from_str_to_big_double : FAILED          !!!\n");
    }


    printf("\n");

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
        char s[] = "-1.1e99999";
        big_double_t x = {0};
        if(from_str_to_big_double(s, &x))
            printf("Negative test 5 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 5 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-1e999999";
        big_double_t x = {0};
        if(from_str_to_big_double(s, &x))
            printf("Negative test 6 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 6 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-999999999999999999999999999999.9e99999";
        big_double_t x = {0};

        if(from_str_to_big_double(s, &x))
            printf("Negative test 7 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 7 for from_str_to_big_double : FAILED          !!!\n");
    }

    {
        char s[] = "-.9999999999999999999999999999999e99999";
        big_double_t x = {0};

        if(from_str_to_big_double(s, &x))
            printf("Negative test 8 for from_str_to_big_double : PASSED\n");
        else
            printf("Negative test 8 for from_str_to_big_double : FAILED          !!!\n");
    }

    printf("\n");

    {
        char s[] = "";
        char perfect_s[] = "-0.1E+7988";
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {1},
                          .is_negative_e = 0,
                          .exponent = {0, 7, 9, 8, 8}};

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
                          .mantissa = {1, 2, 3, 4, 5},
                          .is_negative_e = 1,
                          .exponent = {0, 0, 0, 1, 0}};
        from_big_double_to_str(s, &x);
        if(!strcmp(s, perfect_s))
            printf("Positive test 2 for from_big_double_to_str : PASSED\n");
        else
            printf("Positive test 2 for from_big_double_to_str : FAILED          !!!\n");
    }

    {
        char s[] = "";
        char perfect_s[] = "+0.01009E-103";
        big_double_t x = {.is_negative_m = 0,
                          .mantissa = {0, 1, 0, 0, 9},
                          .is_negative_e = 1,
                          .exponent = {0, 0, 1, 0, 3}};

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
                          .mantissa = {1, 5},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 2}};

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {3},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 1}};

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = {5},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 1}};

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
                          .mantissa = {5, 5},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 2}};

        big_double_t y = {.is_negative_m = 0,
                          .mantissa = {5},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 1}};

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = {1, 1},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 2}};

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
                          .mantissa = {8, 0, 0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 3}};

        big_double_t y = {.is_negative_m = 0,
                          .mantissa = {5},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 1}};

        big_double_t perfect_z = {.is_negative_m = 1,
                                  .mantissa = {1, 6, 0},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 3}};

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
                          .mantissa = {1, 5},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 2}};

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {8, 0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 2}};

        big_double_t perfect_z = {.is_negative_m = 1,
                                  .mantissa = {1, 8, 7, 5},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0}};

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
                          .mantissa = {0, 0, 2},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0}};

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {5, 0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 2}};

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = {4},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 4}};

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
                          .mantissa = {1},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0}};

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {0, 1},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0}};

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = {1},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 2}};

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
                          .mantissa = {6, 5},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 1}};

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {5, 0, 0},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 3}};

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = {1, 3},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 1}};

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

    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {1},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 1}};

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {1, 1},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 2}};

        big_double_t perfect_z = {.is_negative_m = 0,
                                  .mantissa = {9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9, 0, 9},
                                  .is_negative_e = 1,
                                  .exponent = {0, 0, 0, 0, 1}};

        big_double_t z = {0};

        if(!division_big_double(&x, &y, &z) &&
                is_arrays_equal(z.mantissa, M_LEN, perfect_z.mantissa, M_LEN) &&
                is_arrays_equal(z.exponent, E_LEN, perfect_z.exponent, E_LEN) &&
                z.is_negative_m == perfect_z.is_negative_m &&
                z.is_negative_e == perfect_z.is_negative_e)
            printf("Positive test 8 for division_big_double : PASSED\n");
        else
            printf("Positive test 8 for division_big_double : FAILED          !!!\n");
    }

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

        big_double_t y = {.is_negative_m = 1,
                          .mantissa = {1, 1, 1},
                          .is_negative_e = 1,
                          .exponent = {0, 0, 0, 0, 1}};
        big_double_t z = {0};

        if(division_big_double(&x, &y, &z))
            printf("Negative test 2 for division_big_double : PASSED\n");
        else
            printf("Negative test 2 for division_big_double : FAILED          !!!\n");
    }

    return EXIT_SUCCESS;
}
