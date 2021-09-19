#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "big_double.h"
#include "big_double_tools.h"

int is_arrays_equal(int arr1[], size_t len1, int arr2[], size_t len2)
{
    if(len1 != len2)
        return 0;
    for(size_t i = 0; i < len1; i++)
        if(arr1[i] != arr2[i])
            return 0;
    return 1;
}

int main()
{
    {
        int x[M_LEN + 1] = {0}, y[M_LEN + 1] = {0}, z[M_LEN + 1] = {0}, perfect_z[M_LEN + 1] = {0};

        x[M_LEN] = 4;
        y[M_LEN] = 2;
        perfect_z[M_LEN] = 2;

        size_t i = 0;
        int e_sign = 0, perfect_e_sign = 0;
        int change_exp[E_LEN] = {0}, perfect_change_exp[E_LEN] = {0, 0, 0, 0, 0};

        if(!division_mantissa(x, y, z, change_exp, &e_sign, &i) &&
                is_arrays_equal(z, M_LEN + 1, perfect_z, M_LEN + 1) &&
                is_arrays_equal(change_exp, E_LEN, perfect_change_exp, E_LEN) &&
                e_sign == perfect_e_sign)
            printf("Positive test 1 for division_mantissa : PASSED\n");
        else
            printf("Positive test 1 for division_mantissa : FAILED          !!!\n");

    }

    {
        int x[M_LEN + 1] = {0}, y[M_LEN + 1] = {0}, z[M_LEN + 1] = {0}, perfect_z[M_LEN + 1] = {0};

        x[M_LEN] = 9;
        y[M_LEN] = 3;
        perfect_z[M_LEN] = 3;

        size_t i = 0;
        int e_sign = 0, perfect_e_sign = 0;
        int change_exp[E_LEN] = {0}, perfect_change_exp[E_LEN] = {0, 0, 0, 0, 0};

        if(!division_mantissa(x, y, z, change_exp, &e_sign, &i) &&
                is_arrays_equal(z, M_LEN + 1, perfect_z, M_LEN + 1) &&
                is_arrays_equal(change_exp, E_LEN, perfect_change_exp, E_LEN) &&
                e_sign == perfect_e_sign)
            printf("Positive test 2 for division_mantissa : PASSED\n");
        else
            printf("Positive test 2 for division_mantissa : FAILED          !!!\n");

    }

    {
        int x[M_LEN + 1] = {0}, y[M_LEN + 1] = {0}, z[M_LEN + 1] = {0}, perfect_z[M_LEN + 1] = {0};

        x[M_LEN - 1] = 2;
        x[M_LEN] = 0;
        y[M_LEN] = 4;
        perfect_z[M_LEN] = 5;

        size_t i = 0;
        int e_sign = 0, perfect_e_sign = 0;
        int change_exp[E_LEN] = {0}, perfect_change_exp[E_LEN] = {0, 0, 0, 0, 0};

        if(!division_mantissa(x, y, z, change_exp, &e_sign, &i) &&
                is_arrays_equal(z, M_LEN + 1, perfect_z, M_LEN + 1) &&
                is_arrays_equal(change_exp, E_LEN, perfect_change_exp, E_LEN) &&
                e_sign == perfect_e_sign)
            printf("Positive test 3 for division_mantissa : PASSED\n");
        else
            printf("Positive test 3 for division_mantissa : FAILED          !!!\n");

    }

    {
        int x[M_LEN + 1] = {0}, y[M_LEN + 1] = {0}, z[M_LEN + 1] = {0}, perfect_z[M_LEN + 1] = {0};

        x[M_LEN - 1] = 2;
        x[M_LEN] = 0;
        y[M_LEN] = 2;
        perfect_z[M_LEN - 1] = 1;
        perfect_z[M_LEN] = 0;

        size_t i = 0;
        int e_sign = 0, perfect_e_sign = 0;
        int change_exp[E_LEN] = {0}, perfect_change_exp[E_LEN] = {0, 0, 0, 0, 0};

        if(!division_mantissa(x, y, z, change_exp, &e_sign, &i) &&
                is_arrays_equal(z, M_LEN + 1, perfect_z, M_LEN + 1) &&
                is_arrays_equal(change_exp, E_LEN, perfect_change_exp, E_LEN) &&
                e_sign == perfect_e_sign)
            printf("Positive test 4 for division_mantissa : PASSED\n");
        else
            printf("Positive test 4 for division_mantissa : FAILED          !!!\n");

    }

    {
        int x[M_LEN + 1] = {0}, y[M_LEN + 1] = {0}, z[M_LEN + 1] = {0}, perfect_z[M_LEN + 1] = {0};

        x[M_LEN] = 1;
        y[M_LEN] = 2;
        perfect_z[M_LEN] = 5;

        size_t i = 0;
        int e_sign = 0, perfect_e_sign = 1;
        int change_exp[E_LEN] = {0}, perfect_change_exp[E_LEN] = {0, 0, 0, 0, 1};

        if(!division_mantissa(x, y, z, change_exp, &e_sign, &i) &&
                is_arrays_equal(z, M_LEN + 1, perfect_z, M_LEN + 1) &&
                is_arrays_equal(change_exp, E_LEN, perfect_change_exp, E_LEN) &&
                e_sign == perfect_e_sign)
            printf("Positive test 5 for division_mantissa : PASSED\n");
        else
            printf("Positive test 5 for division_mantissa : FAILED          !!!\n");
    }

    {
        int x[M_LEN + 1] = {0}, y[M_LEN + 1] = {0}, z[M_LEN + 1] = {0}, perfect_z[M_LEN + 1] = {0};

        x[M_LEN] = 5;
        y[M_LEN] = 2;
        perfect_z[M_LEN] = 5;
        perfect_z[M_LEN - 1] = 2;

        size_t i = 0;
        int e_sign = 0, perfect_e_sign = 1;
        int change_exp[E_LEN] = {0}, perfect_change_exp[E_LEN] = {0, 0, 0, 0, 1};

        if(!division_mantissa(x, y, z, change_exp, &e_sign, &i) &&
                is_arrays_equal(z, M_LEN + 1, perfect_z, M_LEN + 1) &&
                is_arrays_equal(change_exp, E_LEN, perfect_change_exp, E_LEN) &&
                e_sign == perfect_e_sign)
            printf("Positive test 6 for division_mantissa : PASSED\n");
        else
            printf("Positive test 6 for division_mantissa : FAILED          !!!\n");
    }

    {
        int x[M_LEN + 1] = {0}, y[M_LEN + 1] = {0}, z[M_LEN + 1] = {0}, perfect_z[M_LEN + 1] = {0};

        x[M_LEN] = 1;
        y[M_LEN] = 1;
        y[M_LEN - 1] = 1;
        for(size_t i = 0; i < M_LEN + 1; i++)
            perfect_z[i] = 9 * (i % 2 == 1);

        size_t i = 0;
        int e_sign = 0, perfect_e_sign = 1;
        int change_exp[E_LEN] = {0}, perfect_change_exp[E_LEN] = {0, 0, 0, 3, 1};

        if(!division_mantissa(x, y, z, change_exp, &e_sign, &i) &&
                is_arrays_equal(z, M_LEN + 1, perfect_z, M_LEN + 1) &&
                is_arrays_equal(change_exp, E_LEN, perfect_change_exp, E_LEN) &&
                e_sign == perfect_e_sign)
            printf("Positive test 6 for division_mantissa : PASSED\n");
        else
            printf("Positive test 6 for division_mantissa : FAILED          !!!\n");
    }

    printf("\n");
////////////////////////////////////////

    {
        int x[E_LEN] = {0}, y[E_LEN] = {0}, z[E_LEN] = {0}, perfect_z[E_LEN] = {0};
        int x_sign = 0, y_sign = 0, z_sign = 0, perfect_z_sign = 0;

        x[E_LEN - 1] = 9;
        y[E_LEN - 1] = 2;
        perfect_z[E_LEN - 1] = 7;

        if(!subtract_exponent(x, x_sign, y, y_sign, z, &z_sign, E_LEN) &&
                is_arrays_equal(z, E_LEN, perfect_z, E_LEN) &&
                z_sign == perfect_z_sign)
            printf("Positive test 1 for subtract_exponent : PASSED\n");
        else
            printf("Positive test 1 for subtract_exponent : FAILED          !!!\n");
    }

    {
        int x[] = {1, 2, 3}, y[] = {0, 2, 3}, z[] = {0, 0, 0}, perfect_z[] = {1, 0, 0};
        int x_sign = 1, y_sign = 1, z_sign = 0, perfect_z_sign = 1;

        if(!subtract_exponent(x, x_sign, y, y_sign, z, &z_sign, 3) &&
                is_arrays_equal(z, 3, perfect_z, 3) &&
                z_sign == perfect_z_sign)
            printf("Positive test 2 for subtract_exponent : PASSED\n");
        else
            printf("Positive test 2 for subtract_exponent : FAILED          !!!\n");
    }

    {
        int x[] = {0, 9, 9}, y[] = {0, 0, 1}, z[] = {0, 0, 0}, perfect_z[] = {1, 0, 0};
        int x_sign = 0, y_sign = 1, z_sign = 0, perfect_z_sign = 0;

        if(!subtract_exponent(x, x_sign, y, y_sign, z, &z_sign, 3) &&
                is_arrays_equal(z, 3, perfect_z, 3) &&
                z_sign == perfect_z_sign)
            printf("Positive test 3 for subtract_exponent : PASSED\n");
        else
            printf("Positive test 3 for subtract_exponent : FAILED          !!!\n");
    }

    {
        int x[] = {0, 9, 9}, y[] = {0, 1, 1}, z[] = {0, 0, 0}, perfect_z[] = {1, 1, 0};
        int x_sign = 1, y_sign = 0, z_sign = 0, perfect_z_sign = 1;

        if(!subtract_exponent(x, x_sign, y, y_sign, z, &z_sign, 3) &&
                is_arrays_equal(z, 3, perfect_z, 3) &&
                z_sign == perfect_z_sign)
            printf("Positive test 4 for subtract_exponent : PASSED\n");
        else
            printf("Positive test 4 for subtract_exponent : FAILED          !!!\n");
    }

    {
        int x[] = {0, 9, 9}, y[] = {1, 0, 0}, z[] = {0, 0, 0}, perfect_z[] = {0, 0, 1};
        int x_sign = 0, y_sign = 0, z_sign = 1, perfect_z_sign = 1;

        if(!subtract_exponent(x, x_sign, y, y_sign, z, &z_sign, 3) &&
                is_arrays_equal(z, 3, perfect_z, 3) &&
                z_sign == perfect_z_sign)
            printf("Positive test 5 for subtract_exponent : PASSED\n");
        else
            printf("Positive test 5 for subtract_exponent : FAILED          !!!\n");
    }

    {
        int x[] = {0, 5, 8}, y[] = {6, 3, 9}, z[] = {0, 0, 0}, perfect_z[] = {5, 8, 1};
        int x_sign = 1, y_sign = 1, z_sign = 1, perfect_z_sign = 0;

        if(!subtract_exponent(x, x_sign, y, y_sign, z, &z_sign, 3) &&
                is_arrays_equal(z, 3, perfect_z, 3) &&
                z_sign == perfect_z_sign)
            printf("Positive test 6 for subtract_exponent : PASSED\n");
        else
            printf("Positive test 6 for subtract_exponent : FAILED          !!!\n");
    }
    printf("\n");
///////////////////////////////////

    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {1},
                          .is_negative_e = 0,
                          .exponent = {0, 0, 0, 0, 0}};
        bd_tool_t y = {0};
        bd_tool_t perfect_y = {.is_negative_m = 1,
                                .mantissa = {0},
                                .is_negative_e = 1,
                                .exponent = {0, 0, 0, 0, 1}};
        perfect_y.mantissa[M_LEN] = 1;

        from_bd_to_bd_tool(&x, &y);

        if(is_arrays_equal(y.mantissa, M_LEN + 1, perfect_y.mantissa, M_LEN + 1) &&
                is_arrays_equal(y.exponent, E_LEN, perfect_y.exponent, E_LEN) &&
                y.is_negative_m == perfect_y.is_negative_m &&
                y.is_negative_e == perfect_y.is_negative_e)
            printf("Positive test 1 for from_bd_to_bd_tool : PASSED\n");
        else
            printf("Positive test 1 for from_bd_to_bd_tool : FAILED          !!!\n");
    }

    {
        big_double_t x = {.is_negative_m = 1,
                          .mantissa = {1},
                          .is_negative_e = 1,
                          .exponent = {0, 0, 0, 0, 2}};
        bd_tool_t y = {0};
        bd_tool_t perfect_y = {.is_negative_m = 1,
                                .mantissa = {0},
                                .is_negative_e = 1,
                                .exponent = {0, 0, 0, 0, 3}};
        perfect_y.mantissa[M_LEN] = 1;

        from_bd_to_bd_tool(&x, &y);

        if(is_arrays_equal(y.mantissa, M_LEN + 1, perfect_y.mantissa, M_LEN + 1) &&
                is_arrays_equal(y.exponent, E_LEN, perfect_y.exponent, E_LEN) &&
                y.is_negative_m == perfect_y.is_negative_m &&
                y.is_negative_e == perfect_y.is_negative_e)
            printf("Positive test 2 for from_bd_to_bd_tool : PASSED\n");
        else
            printf("Positive test 2 for from_bd_to_bd_tool : FAILED          !!!\n");
    }

    printf("\n");
//////////////////////////////

    {
        big_double_t perfect_x = {.is_negative_m = 1,
                                  .mantissa = {1},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0}};
        big_double_t x = {0};

        bd_tool_t y = {.is_negative_m = 1,
                       .mantissa = {0},
                       .is_negative_e = 1,
                       .exponent = {0, 0, 0, 0, 1}};
        y.mantissa[M_LEN] = 1;

        from_bd_tool_to_bd(&y, &x);

        if(is_arrays_equal(x.mantissa, M_LEN + 1, perfect_x.mantissa, M_LEN + 1) &&
                is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) &&
                x.is_negative_m == perfect_x.is_negative_m &&
                x.is_negative_e == perfect_x.is_negative_e)
            printf("Positive test 1 for from_bd_tool_to_bd : PASSED\n");
        else
            printf("Positive test 1 for from_bd_tool_to_bd : FAILED          !!!\n");
    }

    {
        big_double_t perfect_x = {.is_negative_m = 0,
                                  .mantissa = {7, 9},
                                  .is_negative_e = 0,
                                  .exponent = {0, 0, 0, 0, 0}};
        big_double_t x = {0};

        bd_tool_t y = {.is_negative_m = 0,
                       .mantissa = {0},
                       .is_negative_e = 1,
                       .exponent = {0, 0, 0, 0, 2}};
        y.mantissa[M_LEN] = 9;
        y.mantissa[M_LEN - 1] = 7;

        from_bd_tool_to_bd(&y, &x);

        if(is_arrays_equal(x.mantissa, M_LEN + 1, perfect_x.mantissa, M_LEN + 1) &&
                is_arrays_equal(x.exponent, E_LEN, perfect_x.exponent, E_LEN) &&
                x.is_negative_m == perfect_x.is_negative_m &&
                x.is_negative_e == perfect_x.is_negative_e)
            printf("Positive test 2 for from_bd_tool_to_bd : PASSED\n");
        else
            printf("Positive test 2 for from_bd_tool_to_bd : FAILED          !!!\n");
    }
    printf("\n");
}
