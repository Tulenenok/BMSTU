#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "big_int.h"
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
        char x[] = "abcde";
        if(is_big_int(x) == 0)
            printf("Negative test 1 for is_big_int : PASSED\n");
        else
            printf("Negative test 1 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "123a";
        if(is_big_int(x) == 0)
            printf("Negative test 2 for is_big_int : PASSED\n");
        else
            printf("Negative test 2 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "1.23";
        if(is_big_int(x) == 0)
            printf("Negative test 3 for is_big_int : PASSED\n");
        else
            printf("Negative test 3 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "1-23";
        if(is_big_int(x) == 0)
            printf("Negative test 4 for is_big_int : PASSED\n");
        else
            printf("Negative test 4 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "++123";
        if(is_big_int(x) == 0)
            printf("Negative test 5 for is_big_int : PASSED\n");
        else
            printf("Negative test 5 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "1234567891234567891234567891234";
        if(is_big_int(x) == 0)
            printf("Negative test 6 for is_big_int : PASSED\n");
        else
            printf("Negative test 6 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-1234567891234567891234567891234";
        if(is_big_int(x) == 0)
            printf("Negative test 7 for is_big_int : PASSED\n");
        else
            printf("Negative test 7 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-";
        if(is_big_int(x) == 0)
            printf("Negative test 8 for is_big_int : PASSED\n");
        else
            printf("Negative test 8 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "-123456789123456789123456789123";
        if(is_big_int(x) == 1)
            printf("Positive test 1 for is_big_int : PASSED\n");
        else
            printf("Positive test 1 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "123456789123456789123456789123";
        if(is_big_int(x) == 1)
            printf("Positive test 2 for is_big_int : PASSED\n");
        else
            printf("Positive test 2 for is_big_int : FAILED          !!!\n");
    }

    {
        char x[] = "+0";
        if(is_big_int(x) == 1)
            printf("Positive test 3 for is_big_int : PASSED\n");
        else
            printf("Positive test 3 for is_big_int : FAILED          !!!\n");
    }

    printf("\n");

    {
        char str[] = "1234567891234567891234567891234";
        big_int_t x = {0};
        if(from_str_to_big_int(str, &x))
            printf("Negative test for 1 from_str_to_big_int : PASSED\n");
        else
            printf("Negative test for 1 from_str_to_big_int : FAILED          !!!\n");
    }

    {
        char str[] = "12345678912.";
        big_int_t x = {0};
        if(from_str_to_big_int(str, &x))
            printf("Negative test for 2 from_str_to_big_int : PASSED\n");
        else
            printf("Negative test for 2 from_str_to_big_int : FAILED          !!!\n");
    }

    {
        char str[] = "123";
        big_int_t x = {0};
        big_int_t perfect_x = {.is_negative = 0, .data = { 0 }};
        perfect_x.data[DATA_LEN - 1] = 3;
        perfect_x.data[DATA_LEN - 2] = 2;
        perfect_x.data[DATA_LEN - 3] = 1;

        if(!from_str_to_big_int(str, &x) &&
           x.is_negative == perfect_x.is_negative &&
           is_arrays_equal(x.data, DATA_LEN, perfect_x.data, DATA_LEN))
            printf("Positive test 1 for from_str_to_big_int : PASSED\n");
        else
            printf("Positive test 1 for from_str_to_big_int : FAILED          !!!\n");
    }

    {
        char str[] = "-99567";
        big_int_t x = {0};
        big_int_t perfect_x = {.is_negative = 1, .data = { 0 }};
        perfect_x.data[DATA_LEN - 1] = 7;
        perfect_x.data[DATA_LEN - 2] = 6;
        perfect_x.data[DATA_LEN - 3] = 5;
        perfect_x.data[DATA_LEN - 4] = 9;
        perfect_x.data[DATA_LEN - 5] = 9;

        if(!from_str_to_big_int(str, &x) &&
            x.is_negative == perfect_x.is_negative &&
            is_arrays_equal(x.data, DATA_LEN, perfect_x.data, DATA_LEN))
            printf("Positive test 2 for from_str_to_big_int : PASSED\n");
        else
            printf("Positive test 2 for from_str_to_big_int : FAILED          !!!\n");
    }

    printf("\n");

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 3;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;
        char str[DATA_LEN];
        char perfect_str[] = "+123";

        from_big_int_to_str(&x, str);

        if(strcmp(str, perfect_str) == 0)
            printf("Positive test 1 for from_big_int_to_str : PASSED\n");
        else
            printf("Positive test 1 for from_big_int_to_str : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        x.data[DATA_LEN - 1] = 7;
        x.data[DATA_LEN - 2] = 6;
        x.data[DATA_LEN - 3] = 5;
        x.data[DATA_LEN - 4] = 9;
        x.data[DATA_LEN - 5] = 9;
        char str[DATA_LEN];
        char perfect_str[] = "-99567";

        from_big_int_to_str(&x, str);

        if(strcmp(str, perfect_str) == 0)
            printf("Positive test 2 for from_big_int_to_str : PASSED\n");
        else
            printf("Positive test 2 for from_big_int_to_str : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 7;
        x.data[DATA_LEN - 2] = 6;
        x.data[DATA_LEN - 3] = 5;
        x.data[DATA_LEN - 4] = 9;
        x.data[DATA_LEN - 5] = 9;
        char str[DATA_LEN];
        char perfect_str[] = "+99567";

        from_big_int_to_str(&x, str);

        if(strcmp(str, perfect_str) == 0)
            printf("Positive test 3 for from_big_int_to_str : PASSED\n");
        else
            printf("Positive test 3 for from_big_int_to_str : FAILED          !!!\n");
    }

    printf("\n");

    {
        int x = 123;
        big_int_t y = {0};
        big_int_t perfect_y = {.is_negative = 0, .data = { 0 }};
        perfect_y.data[DATA_LEN - 1] = 3;
        perfect_y.data[DATA_LEN - 2] = 2;
        perfect_y.data[DATA_LEN - 3] = 1;

        from_int_to_big_int(x, &y);

        if(y.is_negative == perfect_y.is_negative &&
           is_arrays_equal(y.data, DATA_LEN, perfect_y.data, DATA_LEN))
            printf("Positive test 1 for from_big_int_to_str : PASSED\n");
        else
            printf("Positive test 1 for from_big_int_to_str : FAILED          !!!\n");
    }

    {
        int x = -90909009;
        big_int_t y = {0};
        big_int_t perfect_y = {.is_negative = 1, .data = { 0 }};
        perfect_y.data[DATA_LEN - 1] = 9;
        perfect_y.data[DATA_LEN - 2] = 0;
        perfect_y.data[DATA_LEN - 3] = 0;
        perfect_y.data[DATA_LEN - 4] = 9;
        perfect_y.data[DATA_LEN - 5] = 0;
        perfect_y.data[DATA_LEN - 6] = 9;
        perfect_y.data[DATA_LEN - 7] = 0;
        perfect_y.data[DATA_LEN - 8] = 9;

        from_int_to_big_int(x, &y);

        if(y.is_negative == perfect_y.is_negative &&
           is_arrays_equal(y.data, DATA_LEN, perfect_y.data, DATA_LEN))
            printf("Positive test 2 for from_big_int_to_str : PASSED\n");
        else
            printf("Positive test 2 for from_big_int_to_str : FAILED          !!!\n");
    }

    printf("\n");
////////////////////////

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        big_int_t y = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 3;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 3;
        y.data[DATA_LEN - 2] = 2;
        y.data[DATA_LEN - 3] = 1;

        if(big_int_cmp(&x, &y) == 0)
            printf("Positive test 1 for big_int_cmp : PASSED\n");
        else
            printf("Positive test 1 for big_int_cmp : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        big_int_t y = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 3;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 3;
        y.data[DATA_LEN - 2] = 2;
        y.data[DATA_LEN - 3] = 1;

        if(big_int_cmp(&x, &y) < 0)
            printf("Positive test 2 for big_int_cmp : PASSED\n");
        else
            printf("Positive test 2 for big_int_cmp : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        big_int_t y = {.is_negative = 1, .data = { 0 }};

        x.data[DATA_LEN - 1] = 3;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 3;
        y.data[DATA_LEN - 2] = 2;
        y.data[DATA_LEN - 3] = 1;

        if(big_int_cmp(&x, &y) > 0)
            printf("Positive test 3 for big_int_cmp : PASSED\n");
        else
            printf("Positive test 3 for big_int_cmp : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        big_int_t y = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 3;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 4;
        y.data[DATA_LEN - 2] = 3;
        y.data[DATA_LEN - 3] = 2;
        y.data[DATA_LEN - 3] = 1;

        if(big_int_cmp(&x, &y) < 0)
            printf("Positive test 4 for big_int_cmp : PASSED\n");
        else
            printf("Positive test 4 for big_int_cmp : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = {1, 2, 3, 4, 5}};
        big_int_t y = {.is_negative = 0, .data = {1, 2, 3, 4}};
        x.data[DATA_LEN - 1] = 5;
        x.data[DATA_LEN - 2] = 4;
        x.data[DATA_LEN - 3] = 3;
        x.data[DATA_LEN - 4] = 2;
        x.data[DATA_LEN - 5] = 1;

        y.data[DATA_LEN - 1] = 4;
        y.data[DATA_LEN - 2] = 3;
        y.data[DATA_LEN - 3] = 2;
        y.data[DATA_LEN - 4] = 1;

        if(big_int_cmp(&x, &y) > 0)
            printf("Positive test 5 for big_int_cmp : PASSED\n");
        else
            printf("Positive test 5 for big_int_cmp : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        big_int_t y = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 5;
        x.data[DATA_LEN - 2] = 4;
        x.data[DATA_LEN - 3] = 3;
        x.data[DATA_LEN - 4] = 2;
        x.data[DATA_LEN - 5] = 1;

        y.data[DATA_LEN - 1] = 4;
        y.data[DATA_LEN - 2] = 3;
        y.data[DATA_LEN - 3] = 2;
        y.data[DATA_LEN - 4] = 1;

        if(big_int_cmp(&x, &y) < 0)
            printf("Positive test 6 for big_int_cmp : PASSED\n");
        else
            printf("Positive test 6 for big_int_cmp : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        big_int_t y = {.is_negative = 1, .data = { 0 }};
        x.data[DATA_LEN - 1] = 5;
        x.data[DATA_LEN - 2] = 4;
        x.data[DATA_LEN - 3] = 3;
        x.data[DATA_LEN - 4] = 2;
        x.data[DATA_LEN - 5] = 1;

        y.data[DATA_LEN - 1] = 4;
        y.data[DATA_LEN - 2] = 3;
        y.data[DATA_LEN - 3] = 2;
        y.data[DATA_LEN - 4] = 1;

        if(big_int_cmp(&x, &y) < 0)
            printf("Positive test 7 for big_int_cmp : PASSED\n");
        else
            printf("Positive test 7 for big_int_cmp : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = {5, 2, 3, 4}};
        big_int_t y = {.is_negative = 0, .data = {1, 2, 3, 4}};
        x.data[DATA_LEN - 1] = 4;
        x.data[DATA_LEN - 2] = 3;
        x.data[DATA_LEN - 3] = 2;
        x.data[DATA_LEN - 4] = 5;

        y.data[DATA_LEN - 1] = 4;
        y.data[DATA_LEN - 2] = 3;
        y.data[DATA_LEN - 3] = 2;
        y.data[DATA_LEN - 4] = 1;

        if(big_int_cmp(&x, &y) > 0)
            printf("Positive test 8 for big_int_cmp : PASSED\n");
        else
            printf("Positive test 8 for big_int_cmp : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        big_int_t y = {.is_negative = 1, .data = { 0 }};
        x.data[DATA_LEN - 1] = 4;
        x.data[DATA_LEN - 2] = 3;
        x.data[DATA_LEN - 3] = 2;
        x.data[DATA_LEN - 4] = 5;

        y.data[DATA_LEN - 1] = 4;
        y.data[DATA_LEN - 2] = 3;
        y.data[DATA_LEN - 3] = 2;
        y.data[DATA_LEN - 4] = 1;

        if(big_int_cmp(&x, &y) < 0)
            printf("Positive test 9 for big_int_cmp : PASSED\n");
        else
            printf("Positive test 9 for big_int_cmp : FAILED          !!!\n");
    }

    printf("\n");

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 4;
        x.data[DATA_LEN - 2] = 3;
        x.data[DATA_LEN - 3] = 2;
        x.data[DATA_LEN - 4] = 5;

        big_int_t y = {.is_negative = 0, .data = { 0 }};
        y.data[DATA_LEN - 1] = 4;
        y.data[DATA_LEN - 2] = 3;
        y.data[DATA_LEN - 3] = 2;
        y.data[DATA_LEN - 4] = 1;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 0, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 8;
        perfect_z.data[DATA_LEN - 2] = 6;
        perfect_z.data[DATA_LEN - 3] = 4;
        perfect_z.data[DATA_LEN - 4] = 6;

        if(!big_int_add(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 1 for big_int_add : PASSED\n");
        else
            printf("Positive test 1 for big_int_add : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 9;
        x.data[DATA_LEN - 2] = 9;
        x.data[DATA_LEN - 3] = 9;
        x.data[DATA_LEN - 4] = 9;

        big_int_t y = {.is_negative = 0, .data = { 0 }};
        y.data[DATA_LEN - 1] = 9;
        y.data[DATA_LEN - 2] = 9;
        y.data[DATA_LEN - 3] = 9;
        y.data[DATA_LEN - 4] = 9;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 0, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 8;
        perfect_z.data[DATA_LEN - 2] = 9;
        perfect_z.data[DATA_LEN - 3] = 9;
        perfect_z.data[DATA_LEN - 4] = 9;
        perfect_z.data[DATA_LEN - 5] = 1;


        if(!big_int_add(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 2 for big_int_add : PASSED\n");
        else
            printf("Positive test 2 for big_int_add : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        x.data[DATA_LEN - 1] = 9;
        x.data[DATA_LEN - 2] = 9;
        x.data[DATA_LEN - 3] = 9;
        x.data[DATA_LEN - 4] = 9;

        big_int_t y = {.is_negative = 1, .data = { 0 }};
        y.data[DATA_LEN - 1] = 9;
        y.data[DATA_LEN - 2] = 9;
        y.data[DATA_LEN - 3] = 9;
        y.data[DATA_LEN - 4] = 9;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 1, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 8;
        perfect_z.data[DATA_LEN - 2] = 9;
        perfect_z.data[DATA_LEN - 3] = 9;
        perfect_z.data[DATA_LEN - 4] = 9;
        perfect_z.data[DATA_LEN - 5] = 1;

        if(!big_int_add(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 3 for big_int_add : PASSED\n");
        else
            printf("Positive test 3 for big_int_add : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = {9, 9, 9, 9}};
        x.data[DATA_LEN - 1] = 9;
        x.data[DATA_LEN - 2] = 9;
        x.data[DATA_LEN - 3] = 9;
        x.data[DATA_LEN - 4] = 9;

        big_int_t y = {.is_negative = 1, .data = {9, 9, 9, 9}};
        y.data[DATA_LEN - 1] = 9;
        y.data[DATA_LEN - 2] = 9;
        y.data[DATA_LEN - 3] = 9;
        y.data[DATA_LEN - 4] = 9;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 0, .data = {0}};

        if(!big_int_add(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 4 for big_int_add : PASSED\n");
        else
            printf("Positive test 4 for big_int_add : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 9;
        x.data[DATA_LEN - 2] = 9;
        x.data[DATA_LEN - 3] = 9;
        x.data[DATA_LEN - 4] = 9;

        big_int_t y = {.is_negative = 1, .data = { 0 }};
        y.data[DATA_LEN - 1] = 8;
        y.data[DATA_LEN - 2] = 9;
        y.data[DATA_LEN - 3] = 9;
        y.data[DATA_LEN - 4] = 9;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 0, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 1;

        if(!big_int_add(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 5 for big_int_add : PASSED\n");
        else
            printf("Positive test 5 for big_int_add : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        x.data[DATA_LEN - 1] = 9;
        x.data[DATA_LEN - 2] = 9;
        x.data[DATA_LEN - 3] = 9;
        x.data[DATA_LEN - 4] = 9;

        big_int_t y = {.is_negative = 0, .data = { 0 }};
        y.data[DATA_LEN - 1] = 8;
        y.data[DATA_LEN - 2] = 9;
        y.data[DATA_LEN - 3] = 9;
        y.data[DATA_LEN - 4] = 9;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 1, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 1;

        if(!big_int_add(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 6 for big_int_add : PASSED\n");
        else
            printf("Positive test 6 for big_int_add : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        x.data[DATA_LEN - 1] = 8;
        x.data[DATA_LEN - 2] = 9;
        x.data[DATA_LEN - 3] = 9;
        x.data[DATA_LEN - 4] = 9;

        big_int_t y = {.is_negative = 0, .data = { 0 }};
        y.data[DATA_LEN - 1] = 9;
        y.data[DATA_LEN - 2] = 9;
        y.data[DATA_LEN - 3] = 9;
        y.data[DATA_LEN - 4] = 9;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 0, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 1;

        if(!big_int_add(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 7 for big_int_add : PASSED\n");
        else
            printf("Positive test 7 for big_int_add : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        for(size_t i = 0; i < DATA_LEN; i++)
            x.data[i] = 9;

        big_int_t y = {.is_negative = 1, .data = { 0 }};
        y.data[DATA_LEN - 1] = 1;

        big_int_t z = {0};

        if(big_int_add(&x, &y, &z))
            printf("Negative test 1 for big_int_add : PASSED\n");
        else
            printf("Negative test 1 for big_int_add : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        for(size_t i = 0; i < DATA_LEN; i++)
            x.data[i] = 9;

        big_int_t y = {.is_negative = 0, .data = { 0 }};
        y.data[DATA_LEN - 1] = 1;

        big_int_t z = {0};

        if(big_int_add(&x, &y, &z))
            printf("Negative test 2 for big_int_add : PASSED\n");
        else
            printf("Negative test 2 for big_int_add : FAILED          !!!\n");
    }

    printf("\n");
////////////////////////////

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        big_int_t y = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 3;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 3;
        y.data[DATA_LEN - 2] = 2;
        y.data[DATA_LEN - 3] = 1;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 0, .data = { 0 }};

        if(!big_int_diff(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 1 for big_int_diff : PASSED\n");
        else
            printf("Positive test 1 for big_int_diff : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        big_int_t y = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 2;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 3;
        y.data[DATA_LEN - 2] = 2;
        y.data[DATA_LEN - 3] = 1;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 1, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 1;

        if(!big_int_diff(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 2 for big_int_diff : PASSED\n");
        else
            printf("Positive test 2 for big_int_diff : FAILED          !!!\n");
    }


    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        big_int_t y = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 3;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 2;
        y.data[DATA_LEN - 2] = 2;
        y.data[DATA_LEN - 3] = 1;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 0, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 1;

        if(!big_int_diff(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 3 for big_int_diff : PASSED\n");
        else
            printf("Positive test 3 for big_int_diff : FAILED          !!!\n");
    }


    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        big_int_t y = {.is_negative = 0, .data = { 0 }};
        x.data[DATA_LEN - 1] = 3;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 3;
        y.data[DATA_LEN - 2] = 2;
        y.data[DATA_LEN - 3] = 1;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 1, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 6;
        perfect_z.data[DATA_LEN - 2] = 4;
        perfect_z.data[DATA_LEN - 3] = 2;

        if(!big_int_diff(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 4 for big_int_diff : PASSED\n");
        else
            printf("Positive test 4 for big_int_diff : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        big_int_t y = {.is_negative = 1, .data = { 0 }};
        x.data[DATA_LEN - 1] = 3;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 3;
        y.data[DATA_LEN - 2] = 2;
        y.data[DATA_LEN - 3] = 1;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 0, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 6;
        perfect_z.data[DATA_LEN - 2] = 4;
        perfect_z.data[DATA_LEN - 3] = 2;

        if(!big_int_diff(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 5 for big_int_diff : PASSED\n");
        else
            printf("Positive test 5 for big_int_diff : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        big_int_t y = {.is_negative = 1, .data = { 0 }};
        x.data[DATA_LEN - 1] = 3;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 2;
        y.data[DATA_LEN - 2] = 2;
        y.data[DATA_LEN - 3] = 1;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 1, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 1;

        if(!big_int_diff(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 6 for big_int_diff : PASSED\n");
        else
            printf("Positive test 6 for big_int_diff : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        big_int_t y = {.is_negative = 1, .data = { 0 }};
        x.data[DATA_LEN - 1] = 2;
        x.data[DATA_LEN - 2] = 2;
        x.data[DATA_LEN - 3] = 1;

        y.data[DATA_LEN - 1] = 3;
        y.data[DATA_LEN - 2] = 2;
        y.data[DATA_LEN - 3] = 1;

        big_int_t z = {0};
        big_int_t perfect_z = {.is_negative = 0, .data = { 0 }};
        perfect_z.data[DATA_LEN - 1] = 1;

        if(!big_int_diff(&x, &y, &z) &&
            z.is_negative == perfect_z.is_negative &&
            is_arrays_equal(z.data, DATA_LEN, perfect_z.data, DATA_LEN))
            printf("Positive test 7 for big_int_diff : PASSED\n");
        else
            printf("Positive test 7 for big_int_diff : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 1, .data = { 0 }};
        for(size_t i = 0; i < DATA_LEN; i++)
            x.data[i] = 9;

        big_int_t y = {.is_negative = 0, .data = { 0 }};
        y.data[DATA_LEN - 1] = 1;

        big_int_t z = {0};

        if(big_int_diff(&x, &y, &z))
            printf("Negative test 1 for big_int_diff : PASSED\n");
        else
            printf("Negative test 1 for big_int_diff : FAILED          !!!\n");
    }

    {
        big_int_t x = {.is_negative = 0, .data = { 0 }};
        for(size_t i = 0; i < DATA_LEN; i++)
            x.data[i] = 9;

        big_int_t y = {.is_negative = 1, .data = { 0 }};
        y.data[DATA_LEN - 1] = 1;

        big_int_t z = {0};

        if(big_int_diff(&x, &y, &z))
            printf("Negative test 2 for big_int_diff : PASSED\n");
        else
            printf("Negative test 2 for big_int_diff : FAILED          !!!\n");
    }


    return EXIT_SUCCESS;
}
