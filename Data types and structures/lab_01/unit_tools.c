#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

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
        char s[] = "10";
        if(is_scientific(s))
            printf("Positive test 1 for is_scientific : PASSED\n");
        else
            printf("Positive test 1 for is_scientific : FAILED          !!!\n");
    }

    {
        char s[] = "-1";
        if(is_scientific(s))
            printf("Positive test 2 for is_scientific : PASSED\n");
        else
            printf("Positive test 2 for is_scientific : FAILED          !!!\n");
    }

    {
        char s[] = "+1.";
        if(is_scientific(s))
            printf("Positive test 3 for is_scientific : PASSED\n");
        else
            printf("Positive test 3 for is_scientific : FAILED          !!!\n");
    }

    {
        char s[] = "-1.1";
        if(is_scientific(s))
            printf("Positive test 4 for is_scientific : PASSED\n");
        else
            printf("Positive test 4 for is_scientific : FAILED          !!!\n");
    }

    {
        char s[] = "-1.e1";
        if(is_scientific(s))
            printf("Positive test 5 for is_scientific : PASSED\n");
        else
            printf("Positive test 5 for is_scientific : FAILED          !!!\n");
    }

    {
        char s[] = ".4e+5";
        if(is_scientific(s))
            printf("Positive test 6 for is_scientific : PASSED\n");
        else
            printf("Positive test 6 for is_scientific : FAILED          !!!\n");
    }

    {
        char s[] = "1e2E2";
        if(!is_scientific(s))
            printf("Negative test 1 for is_scientific : PASSED\n");
        else
            printf("Negative test 1 for is_scientific : FAILED          !!!\n");
    }

    {
        char s[] = "+.e+1";
        if(!is_scientific(s))
            printf("Negative test 2 for is_scientific : PASSED\n");
        else
            printf("Negative test 2 for is_scientific : FAILED          !!!\n");
    }

    {
        char s[] = "1.e.";
        if(!is_scientific(s))
            printf("Negative test 3 for is_scientific : PASSED\n");
        else
            printf("Negative test 3 for is_scientific : FAILED          !!!\n");
    }

    {
        char s[] = "1et";
        if(!is_scientific(s))
            printf("Negative test 4 for is_scientific : PASSED\n");
        else
            printf("Negative test 4 for is_scientific : FAILED          !!!\n");
    }

    printf("\n");
///////////////////

    {
        int arr[] = {1, 2, 3, 4, 5};
        int perfect_arr[] = {1, 2, 3, 4, 6};
        size_t len = 5;
        if(!increase_by_one(arr, len) && is_arrays_equal(arr, len, perfect_arr, len))
            printf("Positive test 1 for increase_by_one : PASSED\n");
        else
            printf("Positive test 1 for increase_by_one : FAILED          !!!\n");
    }

    {
        int arr[] = {1, 9, 9, 9, 9};
        int perfect_arr[] = {2, 0, 0, 0, 0};
        size_t len = 5;
        if(!increase_by_one(arr, len) && is_arrays_equal(arr, len, perfect_arr, len))
            printf("Positive test 2 for increase_by_one : PASSED\n");
        else
            printf("Positive test 2 for increase_by_one : FAILED          !!!\n");
    }

    {
        int arr[] = {9, 9, 9, 9, 9};
        size_t len = 5;
        if(increase_by_one(arr, len))
            printf("Negative test 1 for increase_by_one : PASSED\n");
        else
            printf("Negative test 1 for increase_by_one : FAILED          !!!\n");
    }
    printf("\n");
//////////////////
    {
        int arr[] = {1, 2, 3, 4, 5};
        int perfect_arr[] = {1, 2, 3, 4, 4};
        size_t len = 5;
        if(!reduce_by_one(arr, len) && is_arrays_equal(arr, len, perfect_arr, len))
            printf("Positive test 1 for reduce_by_one : PASSED\n");
        else
            printf("Positive test 1 for reduce_by_one : FAILED          !!!\n");
    }
    {
        int arr[] = {2, 0, 0, 0, 0};
        int perfect_arr[] = {1, 9, 9, 9, 9};
        size_t len = 5;
        if(!reduce_by_one(arr, len) && is_arrays_equal(arr, len, perfect_arr, len))
            printf("Positive test 2 for reduce_by_one : PASSED\n");
        else
            printf("Positive test 2 for reduce_by_one : FAILED          !!!\n");
    }
    {
        int arr[] = {0, 0, 0, 0, 0};
        size_t len = 5;
        if(reduce_by_one(arr, len))
            printf("Negative test 1 for reduce_by_one : PASSED\n");
        else
            printf("Negative test 1 for reduce_by_one : FAILED          !!!\n");
    }

    printf("\n");
//////////////////
    {
        int arr[] = {0, 0, 0};
        size_t len = 3;
        if(is_null_arr(arr, len))
            printf("Positive test 1 for is_null_arr : PASSED\n");
        else
            printf("Positive test 1 for is_null_arr : FAILED          !!!\n");
    }
    {
        int arr[] = {0, 1, 0};
        size_t len = 3;
        if(!is_null_arr(arr, len))
            printf("Positive test 2 for is_null_arr : PASSED\n");
        else
            printf("Positive test 2 for is_null_arr : FAILED          !!!\n");
    }
    printf("\n");
/////////////////
    {
        int arr[] = {1, 2, 3, 4, 5};
        int perfect_arr[] = {1, 2, 3, 4, 6};
        size_t len = 5;
        int sign = 0, perfect_sign = 0;

        increase_one_with_sign(arr, len, &sign);

        if(is_arrays_equal(arr, len, perfect_arr, len) &&
            sign == perfect_sign)
            printf("Positive test 1 for increase_one_with_sign : PASSED\n");
        else
            printf("Positive test 1 for increase_one_with_sign : FAILED          !!!\n");
    }

    {
        int arr[] = {1, 2, 3, 4, 5};
        int perfect_arr[] = {1, 2, 3, 4, 4};
        size_t len = 5;
        int sign = 1, perfect_sign = 1;

        increase_one_with_sign(arr, len, &sign);

        if(is_arrays_equal(arr, len, perfect_arr, len) &&
            sign == perfect_sign)
            printf("Positive test 2 for increase_one_with_sign : PASSED\n");
        else
            printf("Positive test 2 for increase_one_with_sign : FAILED          !!!\n");
    }

    {
        int arr[] = {0, 0, 0, 0, 0};
        int perfect_arr[] = {0, 0, 0, 0, 1};
        size_t len = 5;
        int sign = 0, perfect_sign = 0;

        increase_one_with_sign(arr, len, &sign);

        if(is_arrays_equal(arr, len, perfect_arr, len) &&
            sign == perfect_sign)
            printf("Positive test 3 for increase_one_with_sign : PASSED\n");
        else
            printf("Positive test 3 for increase_one_with_sign : FAILED          !!!\n");
    }

    {
        int arr[] = {0, 0, 0, 0, 1};
        int perfect_arr[] = {0, 0, 0, 0, 0};
        size_t len = 5;
        int sign = 1, perfect_sign = 0;

        increase_one_with_sign(arr, len, &sign);

        if(is_arrays_equal(arr, len, perfect_arr, len) &&
            sign == perfect_sign)
            printf("Positive test 4 for increase_one_with_sign : PASSED\n");
        else
            printf("Positive test 4 for increase_one_with_sign : FAILED          !!!\n");
    }
    printf("\n");
////////////////
    {
        int arr[] = {0, 0, 0, 0, 0};
        int perfect_arr[] = {0, 0, 0, 0, 1};
        size_t len = 5;
        int sign = 0, perfect_sign = 1;

        reduce_one_with_sign(arr, len, &sign);

        if(is_arrays_equal(arr, len, perfect_arr, len) &&
            sign == perfect_sign)
            printf("Positive test 1 for reduce_one_with_sign : PASSED\n");
        else
            printf("Positive test 1 for reduce_one_with_sign : FAILED          !!!\n");
    }

    {
        int arr[] = {0, 0, 0, 0, 1};
        int perfect_arr[] = {0, 0, 0, 0, 2};
        size_t len = 5;
        int sign = 1, perfect_sign = 1;

        reduce_one_with_sign(arr, len, &sign);

        if(is_arrays_equal(arr, len, perfect_arr, len) &&
            sign == perfect_sign)
            printf("Positive test 2 for reduce_one_with_sign : PASSED\n");
        else
            printf("Positive test 2 for reduce_one_with_sign : FAILED          !!!\n");
    }

    {
        int arr[] = {0, 0, 0, 0, 1};
        int perfect_arr[] = {0, 0, 0, 0, 0};
        size_t len = 5;
        int sign = 0, perfect_sign = 0;

        reduce_one_with_sign(arr, len, &sign);

        if(is_arrays_equal(arr, len, perfect_arr, len) &&
            sign == perfect_sign)
            printf("Positive test 3 for reduce_one_with_sign : PASSED\n");
        else
            printf("Positive test 3 for reduce_one_with_sign : FAILED          !!!\n");
    }
    printf("\n");
////////////////
    {
        int arr[] = {0, 0, 0, 0, 0};
        int perfect_arr[] = {0, 0, 0, 0, 1};
        size_t len = 5;

        if(rounding(arr, len) == NO_OVERFLOW &&
            is_arrays_equal(arr, len, perfect_arr, len))
            printf("Positive test 1 for rounding : PASSED\n");
        else
            printf("Positive test 1 for rounding : FAILED          !!!\n");
    }

    {
        int arr[] = {9, 9, 9, 9, 9};
        int perfect_arr[] = {1, 0, 0, 0, 0};
        size_t len = 5;

        if(rounding(arr, len) == WAS_OVERFLOW &&
            is_arrays_equal(arr, len, perfect_arr, len))
            printf("Positive test 2 for rounding : PASSED\n");
        else
            printf("Positive test 2 for rounding : FAILED          !!!\n");
    }
    printf("\n");
////////////////
    {
        int arr[] = {0, 9, 9, 9, 9};
        int perfect_arr[] = {9, 9, 9, 9, 1};
        size_t len = 5;
        int x = 1;

        if(!insert_end(arr, len, x) &&
            is_arrays_equal(arr, len, perfect_arr, len))
            printf("Positive test 1 for insert_end : PASSED\n");
        else
            printf("Positive test 1 for insert_end : FAILED          !!!\n");
    }

    {
        int arr[] = {9, 8, 7, 6, 5};
        size_t len = 5;
        int x = 1;

        if(insert_end(arr, len, x))
            printf("Positive test 2 for insert_end : PASSED\n");
        else
            printf("Positive test 2 for insert_end : FAILED          !!!\n");
    }
    printf("\n");
///////////////
    {
        int a[] = {1, 2, 3}, b[] = {1, 2, 3};
        size_t len_a = 3, len_b = 3;
        if(arr_cmp(a, len_a, b, len_b) == 0)
            printf("Positive test 1 for arr_cmp : PASSED\n");
        else
            printf("Positive test 1 for arr_cmp : FAILED          !!!\n");
    }

    {
        int a[] = {1, 2, 3, 4}, b[] = {1, 2, 3};
        size_t len_a = 4, len_b = 3;
        if(arr_cmp(a, len_a, b, len_b) > 0)
            printf("Positive test 2 for arr_cmp : PASSED\n");
        else
            printf("Positive test 2 for arr_cmp : FAILED          !!!\n");
    }

    {
        int a[] = {4, 2, 3}, b[] = {1, 2, 3, 4};
        size_t len_a = 3, len_b = 4;
        if(arr_cmp(a, len_a, b, len_b) < 0)
            printf("Positive test 3 for arr_cmp : PASSED\n");
        else
            printf("Positive test 3 for arr_cmp : FAILED          !!!\n");
    }

    {
        int a[] = {4, 2, 3}, b[] = {1, 2, 3};
        size_t len_a = 3, len_b = 3;
        if(arr_cmp(a, len_a, b, len_b) > 0)
            printf("Positive test 4 for arr_cmp : PASSED\n");
        else
            printf("Positive test 4 for arr_cmp : FAILED          !!!\n");
    }

    {
        int a[] = {2, 2, 3}, b[] = {2, 4, 3};
        size_t len_a = 3, len_b = 3;
        if(arr_cmp(a, len_a, b, len_b) < 0)
            printf("Positive test 5 for arr_cmp : PASSED\n");
        else
            printf("Positive test 5 for arr_cmp : FAILED          !!!\n");
    }
    printf("\n");
///////////////
    {
        int a[3], perfect_a[] = {2, 2, 2};
        size_t len_a = 3;
        int x = 2;

        fill_arr(a, len_a, x);

        if(is_arrays_equal(a, len_a, perfect_a, len_a))
            printf("Positive test 1 for fill_arr : PASSED\n");
        else
            printf("Positive test 1 for fill_arr : FAILED          !!!\n");
    }

    {
        int a[5], perfect_a[] = {0, 0, 0, 0, 0};
        size_t len_a = 5;
        int x = 0;

        fill_arr(a, len_a, x);

        if(is_arrays_equal(a, len_a, perfect_a, len_a))
            printf("Positive test 2 for fill_arr : PASSED\n");
        else
            printf("Positive test 2 for fill_arr : FAILED          !!!\n");
    }
    printf("\n");
///////////////
    {
        int a[] = {1, 2, 3}, perfect_a[] = {2, 3, 0};
        size_t len_a = 3;
        size_t x = 1;

        shift_left(a, len_a, x);

        if(is_arrays_equal(a, len_a, perfect_a, len_a))
            printf("Positive test 1 for shift_left : PASSED\n");
        else
            printf("Positive test 1 for shift_left : FAILED          !!!\n");
    }

    {
        int a[] = {1, 2, 3, 4, 5}, perfect_a[] = {0, 0, 0, 0, 0};
        size_t len_a = 5;
        size_t x = 5;

        shift_left(a, len_a, x);

        if(is_arrays_equal(a, len_a, perfect_a, len_a))
            printf("Positive test 2 for shift_left : PASSED\n");
        else
            printf("Positive test 2 for shift_left : FAILED          !!!\n");
    }

    printf("\n");
///////////////
    {
        int a[] = {1, 2, 3}, perfect_a[] = {0, 1, 2};
        size_t len_a = 3;
        size_t x = 1;

        shift_right(a, len_a, x);

        if(is_arrays_equal(a, len_a, perfect_a, len_a))
            printf("Positive test 1 for shift_right : PASSED\n");
        else
            printf("Positive test 1 for shift_right : FAILED          !!!\n");
    }
    {
        int a[] = {1, 2, 3, 4, 5}, perfect_a[] = {0, 0, 0, 0, 0};
        size_t len_a = 5;
        size_t x = 6;

        shift_right(a, len_a, x);

        if(is_arrays_equal(a, len_a, perfect_a, len_a))
            printf("Positive test 2 for shift_right : PASSED\n");
        else
            printf("Positive test 2 for shift_right : FAILED          !!!\n");
    }
    printf("\n");
///////////////
    {
        int a[] = {1, 2, 3, 4, 5}, perfect_b[] = {1, 2, 3, 4, 5}, b[5];
        size_t len_a = 5, len_b = 5;

        if(!arr_cpy(a, len_a, b, len_b) &&
            is_arrays_equal(b, len_b, perfect_b, len_b))
            printf("Positive test 1 for arr_cpy : PASSED\n");
        else
            printf("Positive test 1 for arr_cpy : FAILED          !!!\n");
    }
    {
        int a[] = {1, 2, 3, 4, 5}, b[6];
        size_t len_a = 5, len_b = 6;

        if(arr_cpy(a, len_a, b, len_b))
            printf("Negative test 1 for arr_cpy : PASSED\n");
        else
            printf("Negative test 1 for arr_cpy : FAILED          !!!\n");
    }
    printf("\n");
///////////////
    {
        int a[] = {1, 2, 3, 0, 0}, perfect_b[] = {0, 0, 1, 2, 3}, b[5];
        size_t len_a = 5, len_b = 5;

        if(!arr_cpy_to_end(a, len_a, b, len_b) &&
            is_arrays_equal(b, len_b, perfect_b, len_b))
            printf("Positive test 1 for arr_cpy_to_end : PASSED\n");
        else
            printf("Positive test 1 for arr_cpy_to_end : FAILED          !!!\n");
    }
    {
        int a[] = {1, 2, 3, 0, 0}, b[3];
        size_t len_a = 5, len_b = 3;

        if(arr_cpy_to_end(a, len_a, b, len_b))
            printf("Negative test 1 for arr_cpy_to_end : PASSED\n");
        else
            printf("Negative test 1 for arr_cpy_to_end : FAILED          !!!\n");
    }
    printf("\n");
///////////////
    {
        int a[] = {0, 0, 1, 2, 3}, perfect_b[] = {1, 2, 3, 0, 0}, b[5];
        size_t len_a = 5, len_b = 5;

        if(!arr_cpy_to_start(a, len_a, b, len_b) &&
            is_arrays_equal(b, len_b, perfect_b, len_b))
            printf("Positive test 1 for arr_cpy_to_start : PASSED\n");
        else
            printf("Positive test 1 for arr_cpy_to_start : FAILED          !!!\n");
    }
    {
        int a[] = {0, 0, 1, 2, 3}, perfect_b[] = {1, 2, 3, 0, 0, 0, 0}, b[7];
        size_t len_a = 5, len_b = 7;

        if(!arr_cpy_to_start(a, len_a, b, len_b) &&
            is_arrays_equal(b, len_b, perfect_b, len_b))
            printf("Positive test 2 for arr_cpy_to_start : PASSED\n");
        else
            printf("Positive test 2 for arr_cpy_to_start : FAILED          !!!\n");
    }
    printf("\n");
///////////////
    {
        int x[] = {1, 2, 3};
        int y[] = {2, 3, 0};
        int z[3];
        size_t x_len = 3, y_len = 3, z_len = 3;
        int perfect_z[] = {3, 5, 3};

        if(!add(x, x_len, y, y_len, z, z_len) && is_arrays_equal(z, z_len, perfect_z, z_len))
            printf("Positive test 1 for add : PASSED\n");
        else
            printf("Positive test 1 for add : FAILED          !!!\n");
    }
    {
        int x[] = {1, 9, 9};
        int y[] = {0, 0, 1};
        int z[3];
        size_t x_len = 3, y_len = 3, z_len = 3;
        int perfect_z[] = {2, 0, 0};

        if(!add(x, x_len, y, y_len, z, z_len) && is_arrays_equal(z, z_len, perfect_z, z_len))
            printf("Positive test 2 for add : PASSED\n");
        else
            printf("Positive test 2 for add : FAILED          !!!\n");

    }
    {
        int x[] = {1, 9, 9};
        int y[] = {0, 1};
        int z[3];
        size_t x_len = 3, y_len = 2, z_len = 3;

        if(add(x, x_len, y, y_len, z, z_len))
            printf("Negative test 1 for add : PASSED\n");
        else
            printf("Negative test 1 for add : FAILED          !!!\n");

    }
    {
        int x[] = {9, 9, 9};
        int y[] = {0, 0, 1};
        int z[3];
        size_t x_len = 3, y_len = 3, z_len = 3;

        if(add(x, x_len, y, y_len, z, z_len))
            printf("Negative test 2 for add : PASSED\n");
        else
            printf("Negative test 2 for add : FAILED          !!!\n");

    }
    printf("\n");
///////////////
    {
        int x[] = {1, 2, 3};
        int y[] = {2, 3};
        int z[3];
        size_t x_len = 3, y_len = 2, z_len = 3;
        int perfect_z[] = {1, 0, 0};

        if(!subtract(x, x_len, y, y_len, z, z_len) && is_arrays_equal(z, 3, perfect_z, 3))
            printf("Positive test 1 for subtract : PASSED\n");
        else
            printf("Positive test 1 for subtract : FAILED          !!!\n");

    }

    {
        int x[] = {2, 3};
        int y[] = {2, 3};
        int z[2];
        size_t x_len = 2, y_len = 2, z_len = 2;
        int perfect_z[] = {0, 0};

        if(!subtract(x, x_len, y, y_len, z, z_len) && is_arrays_equal(z, 2, perfect_z, 2))
            printf("Positive test 2 for subtract : PASSED\n");
        else
            printf("Positive test 2 for subtract : FAILED          !!!\n");

    }

    {
        int x[] = {2, 0};
        int y[] = {1, 1};
        int z[2];
        size_t x_len = 2, y_len = 2, z_len = 2;
        int perfect_z[] = {0, 9};

        if(!subtract(x, x_len, y, y_len, z, z_len) && is_arrays_equal(z, 2, perfect_z, 2))
            printf("Positive test 3 for subtract : PASSED\n");
        else
            printf("Positive test 3 for subtract : FAILED          !!!\n");

    }

    {
        int x[] = {1, 0};
        int y[] = {1, 1};
        int z[2];
        size_t x_len = 2, y_len = 2, z_len = 2;

        if(subtract(x, x_len, y, y_len, z, z_len))
            printf("Negative test 1 for subtract : PASSED\n");
        else
            printf("Negative test 1 for subtract : FAILED          !!!\n");

    }
///////////////////////////////////
    printf("\n");

    {
        int x[] = {4}, y[] = {2}, mod[1] = {0}, div[1] = {0};
        int perfect_div[] = {2}, perfect_mod[] = {0};
        size_t x_len = 1, y_len = 1, mod_len = 1, div_len = 1;

        if(!division(x, x_len, y, y_len, div, div_len, mod, mod_len) &&
                is_arrays_equal(mod, 1, perfect_mod, 1) &&
                is_arrays_equal(div, 1, perfect_div, 1))
            printf("Positive test 1 for division : PASSED\n");
        else
            printf("Positive test 1 for division : FAILED          !!!\n");

    }

    {
        int x[] = {1, 0}, y[] = {0, 3}, mod[2] = {0}, div[2] = {0};
        int perfect_div[] = {0, 3}, perfect_mod[] = {0, 1};
        size_t x_len = 2, y_len = 2, mod_len = 2, div_len = 2;

        if(!division(x, x_len, y, y_len, div, div_len, mod, mod_len) &&
                is_arrays_equal(mod, 2, perfect_mod, 2) &&
                is_arrays_equal(div, 2, perfect_div, 2))
            printf("Positive test 2 for division : PASSED\n");
        else
            printf("Positive test 2 for division : FAILED          !!!\n");

    }

    {
        int x[] = {0, 1, 0}, y[] = {0, 1, 0}, mod[3] = {0}, div[3] = {0};
        int perfect_div[] = {0, 0, 1}, perfect_mod[] = {0, 0, 0};
        size_t x_len = 3, y_len = 3, mod_len = 3, div_len = 3;

        if(!division(x, x_len, y, y_len, div, div_len, mod, mod_len) &&
                is_arrays_equal(mod, 3, perfect_mod, 3) &&
                is_arrays_equal(div, 3, perfect_div, 3))
            printf("Positive test 3 for division : PASSED\n");
        else
            printf("Positive test 3 for division : FAILED          !!!\n");

    }

    {
        int x[] = {0, 2, 0}, y[] = {0, 0, 4}, mod[3] = {0}, div[3] = {0};
        int perfect_div[] = {0, 0, 5}, perfect_mod[] = {0, 0, 0};
        size_t x_len = 3, y_len = 3, mod_len = 3, div_len = 3;

        if(!division(x, x_len, y, y_len, div, div_len, mod, mod_len) &&
                is_arrays_equal(mod, 3, perfect_mod, 3) &&
                is_arrays_equal(div, 3, perfect_div, 3))
            printf("Positive test 4 for division : PASSED\n");
        else
            printf("Positive test 4 for division : FAILED          !!!\n");

    }

    {
        int x[] = {1, 0, 0}, y[] = {0, 1, 9}, mod[3] = {0}, div[3] = {0};
        int perfect_div[] = {0, 0, 5}, perfect_mod[] = {0, 0, 5};
        size_t x_len = 3, y_len = 3, mod_len = 3, div_len = 3;

        if(!division(x, x_len, y, y_len, div, div_len, mod, mod_len) &&
                is_arrays_equal(mod, 3, perfect_mod, 3) &&
                is_arrays_equal(div, 3, perfect_div, 3))
            printf("Positive test 5 for division : PASSED\n");
        else
            printf("Positive test 5 for division : FAILED          !!!\n");

    }

    {
        int x[] = {0, 0, 9}, y[] = {0, 1, 0}, mod[3] = {0}, div[3] = {0};
        int perfect_div[] = {0, 0, 0}, perfect_mod[] = {0, 0, 9};
        size_t x_len = 3, y_len = 3, mod_len = 3, div_len = 3;

        if(!division(x, x_len, y, y_len, div, div_len, mod, mod_len) &&
                is_arrays_equal(mod, 3, perfect_mod, 3) &&
                is_arrays_equal(div, 3, perfect_div, 3))
            printf("Positive test 6 for division : PASSED\n");
        else
            printf("Positive test 6 for division : FAILED          !!!\n");

    }

    {
        int x[] = {0, 0, 0}, y[] = {0, 1, 0}, mod[3] = {0}, div[3] = {0};
        int perfect_div[] = {0, 0, 0}, perfect_mod[] = {0, 0, 0};
        size_t x_len = 3, y_len = 3, mod_len = 3, div_len = 3;

        if(!division(x, x_len, y, y_len, div, div_len, mod, mod_len) &&
                is_arrays_equal(mod, 3, perfect_mod, 3) &&
                is_arrays_equal(div, 3, perfect_div, 3))
            printf("Positive test 7 for division : PASSED\n");
        else
            printf("Positive test 7 for division : FAILED          !!!\n");

    }

    {
        int x[] = {1, 9};
        int y[] = {0, 1, 9};
        int mod[3] = {0};
        int div[3] = {0};
        size_t x_len = 2, y_len = 3, mod_len = 3, div_len = 3;

        if(division(x, x_len, y, y_len, div, div_len, mod, mod_len))
            printf("Negative test 1 for division : PASSED\n");
        else
            printf("Negative test 1 for division : FAILED          !!!\n");

    }

    {
        int x[] = {0, 0, 9};
        int y[] = {0, 0, 0};
        int mod[3] = {0};
        int div[3] = {0};
        size_t x_len = 3, y_len = 3, mod_len = 3, div_len = 3;

        if(division(x, x_len, y, y_len, div, div_len, mod, mod_len))
            printf("Negative test 2 for division : PASSED\n");
        else
            printf("Negative test 2 for division : FAILED          !!!\n");

    }
    printf("\n");
////////////////////////////////////////

    {
        char x = '0';
        int perfect_y = 0;
        int y = from_char_to_int_digit(x);
        if(y == perfect_y)
            printf("Positive test  1 for from_char_to_int_digit : PASSED\n");
        else
            printf("Positive test  1 for from_char_to_int_digit : FAILED          !!!\n");
    }
    {
        char x = '1';
        int perfect_y = 1;
        int y = from_char_to_int_digit(x);
        if(y == perfect_y)
            printf("Positive test  2 for from_char_to_int_digit : PASSED\n");
        else
            printf("Positive test  2 for from_char_to_int_digit : FAILED          !!!\n");
    }
    {
        char x = '2';
        int perfect_y = 2;
        int y = from_char_to_int_digit(x);
        if(y == perfect_y)
            printf("Positive test  3 for from_char_to_int_digit : PASSED\n");
        else
            printf("Positive test  3 for from_char_to_int_digit : FAILED          !!!\n");
    }
    {
        char x = '3';
        int perfect_y = 3;
        int y = from_char_to_int_digit(x);
        if(y == perfect_y)
            printf("Positive test  4 for from_char_to_int_digit : PASSED\n");
        else
            printf("Positive test  4 for from_char_to_int_digit : FAILED          !!!\n");
    }
    {
        char x = '4';
        int perfect_y = 4;
        int y = from_char_to_int_digit(x);
        if(y == perfect_y)
            printf("Positive test  5 for from_char_to_int_digit : PASSED\n");
        else
            printf("Positive test  5 for from_char_to_int_digit : FAILED          !!!\n");
    }
    {
        char x = '5';
        int perfect_y = 5;
        int y = from_char_to_int_digit(x);
        if(y == perfect_y)
            printf("Positive test  6 for from_char_to_int_digit : PASSED\n");
        else
            printf("Positive test  6 for from_char_to_int_digit : FAILED          !!!\n");
    }
    {
        char x = '6';
        int perfect_y = 6;
        int y = from_char_to_int_digit(x);
        if(y == perfect_y)
            printf("Positive test  7 for from_char_to_int_digit : PASSED\n");
        else
            printf("Positive test  7 for from_char_to_int_digit : FAILED          !!!\n");
    }
    {
        char x = '7';
        int perfect_y = 7;
        int y = from_char_to_int_digit(x);
        if(y == perfect_y)
            printf("Positive test  8 for from_char_to_int_digit : PASSED\n");
        else
            printf("Positive test  8 for from_char_to_int_digit : FAILED          !!!\n");
    }
    {
        char x = '8';
        int perfect_y = 8;
        int y = from_char_to_int_digit(x);
        if(y == perfect_y)
            printf("Positive test  9 for from_char_to_int_digit : PASSED\n");
        else
            printf("Positive test  9 for from_char_to_int_digit : FAILED          !!!\n");
    }
    {
        char x = '9';
        int perfect_y = 9;
        int y = from_char_to_int_digit(x);
        if(y == perfect_y)
            printf("Positive test 10 for from_char_to_int_digit : PASSED\n");
        else
            printf("Positive test 10 for from_char_to_int_digit : FAILED          !!!\n");
    }
    {
        char x = 'a';
        if(from_char_to_int_digit(x) == NOT_DIGIT)
            printf("Negative test  1 for from_char_to_int_digit : PASSED\n");
        else
            printf("Negative test  1 for from_char_to_int_digit : FAILED          !!!\n");
    }
    printf("\n");
////////////////////////////////////////

    {
        int x = 0;
        char perfect_y = '0';
        char y = from_int_to_char_digit(x);
        if(y == perfect_y)
            printf("Positive test  1 for from_int_to_char_digit : PASSED\n");
        else
            printf("Positive test  1 for from_int_to_char_digit : FAILED          !!!\n");
    }
    {
        int x = 1;
        char perfect_y = '1';
        char y = from_int_to_char_digit(x);
        if(y == perfect_y)
            printf("Positive test  2 for from_int_to_char_digit : PASSED\n");
        else
            printf("Positive test  2 for from_int_to_char_digit : FAILED          !!!\n");
    }
    {
        int x = 2;
        char perfect_y = '2';
        char y = from_int_to_char_digit(x);
        if(y == perfect_y)
            printf("Positive test  3 for from_int_to_char_digit : PASSED\n");
        else
            printf("Positive test  3 for from_int_to_char_digit : FAILED          !!!\n");
    }
    {
        int x = 3;
        char perfect_y = '3';
        char y = from_int_to_char_digit(x);
        if(y == perfect_y)
            printf("Positive test  4 for from_int_to_char_digit : PASSED\n");
        else
            printf("Positive test  4 for from_int_to_char_digit : FAILED          !!!\n");
    }
    {
        int x = 4;
        char perfect_y = '4';
        char y = from_int_to_char_digit(x);
        if(y == perfect_y)
            printf("Positive test  5 for from_int_to_char_digit : PASSED\n");
        else
            printf("Positive test  5 for from_int_to_char_digit : FAILED          !!!\n");
    }
    {
        int x = 5;
        char perfect_y = '5';
        char y = from_int_to_char_digit(x);
        if(y == perfect_y)
            printf("Positive test  6 for from_int_to_char_digit : PASSED\n");
        else
            printf("Positive test  6 for from_int_to_char_digit : FAILED          !!!\n");
    }
    {
        int x = 6;
        char perfect_y = '6';
        char y = from_int_to_char_digit(x);
        if(y == perfect_y)
            printf("Positive test  7 for from_int_to_char_digit : PASSED\n");
        else
            printf("Positive test  7 for from_int_to_char_digit : FAILED          !!!\n");
    }
    {
        int x = 7;
        char perfect_y = '7';
        char y = from_int_to_char_digit(x);
        if(y == perfect_y)
            printf("Positive test  8 for from_int_to_char_digit : PASSED\n");
        else
            printf("Positive test  8 for from_int_to_char_digit : FAILED          !!!\n");
    }
    {
        int x = 8;
        char perfect_y = '8';
        char y = from_int_to_char_digit(x);
        if(y == perfect_y)
            printf("Positive test  9 for from_int_to_char_digit : PASSED\n");
        else
            printf("Positive test  9 for from_int_to_char_digit : FAILED          !!!\n");
    }
    {
        int x = 9;
        char perfect_y = '9';
        char y = from_int_to_char_digit(x);
        if(y == perfect_y)
            printf("Positive test 10 for from_int_to_char_digit : PASSED\n");
        else
            printf("Positive test 10 for from_int_to_char_digit : FAILED          !!!\n");
    }
    {
        int x = 12434;
        if(from_int_to_char_digit(x) == NOT_DIGIT)
            printf("Negative test  1 for from_int_to_char_digit : PASSED\n");
        else
            printf("Negative test  1 for from_int_to_char_digit : FAILED          !!!\n");
    }
    return EXIT_SUCCESS;
}
