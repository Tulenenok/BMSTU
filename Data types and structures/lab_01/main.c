#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "big_double.h"

int main(void)
{
    {
        char x_str[] = "10", y_str[] = "5", res_str[] = "";
        big_double_t x = { 0 }, y = { 0 }, res = { 0 };

        if(from_str_to_big_double(x_str, &x))
            printf("Error with from_str_to_big_double x");

        if(from_str_to_big_double(y_str, &y))
            printf("Error with from_str_to_big_double y");

        if(division_big_double(&x, &y, &res))
            printf("Error with division");

        from_big_double_to_str(res_str, &res);

        printf("Success your result = %s\n", res_str);
    }

    {
        char x_str[] = "2.125", y_str[] = "0.125", res_str[] = "";
        big_double_t x = { 0 }, y = { 0 }, res = { 0 };

        if(from_str_to_big_double(x_str, &x))
            printf("Error with from_str_to_big_double x");

        if(from_str_to_big_double(y_str, &y))
            printf("Error with from_str_to_big_double y");

        if(division_big_double(&x, &y, &res))
            printf("Error with division");

        from_big_double_to_str(res_str, &res);

        printf("Success, your result = %s\n", res_str);
    }

    {
        char x_str[] = "-1", y_str[] = "11", res_str[] = "";
        big_double_t x = { 0 }, y = { 0 }, res = { 0 };

        if(from_str_to_big_double(x_str, &x))
            printf("Error with from_str_to_big_double x");

        if(from_str_to_big_double(y_str, &y))
            printf("Error with from_str_to_big_double y");

        if(division_big_double(&x, &y, &res))
            printf("Error with division");

        from_big_double_to_str(res_str, &res);

        printf("Success, your result = %s\n", res_str);
    }

    {
        char x_str[] = "-9.89e14", y_str[] = "-86e-3", res_str[] = "";
        big_double_t x = { 0 }, y = { 0 }, res = { 0 };

        if(from_str_to_big_double(x_str, &x))
            printf("Error with from_str_to_big_double x");

        if(from_str_to_big_double(y_str, &y))
            printf("Error with from_str_to_big_double y");

        if(division_big_double(&x, &y, &res))
            printf("Error with division");

        from_big_double_to_str(res_str, &res);

        printf("Success, your result = %s\n", res_str);
    }

    {
        char x_str[] = "-0.12345", y_str[] = "-0.134", res_str[] = "";
        big_double_t x = { 0 }, y = { 0 }, res = { 0 };

        if(from_str_to_big_double(x_str, &x))
            printf("Error with from_str_to_big_double x");

        if(from_str_to_big_double(y_str, &y))
            printf("Error with from_str_to_big_double y");

        if(division_big_double(&x, &y, &res))
            printf("Error with division");

        from_big_double_to_str(res_str, &res);

        printf("Success, your result = %s\n", res_str);
    }

    {
        char x_str[] = "-0.12", y_str[] = "-0.678", res_str[] = "";
        big_double_t x = { 0 }, y = { 0 }, res = { 0 };

        if(from_str_to_big_double(x_str, &x))
            printf("Error with from_str_to_big_double x");

        if(from_str_to_big_double(y_str, &y))
            printf("Error with from_str_to_big_double y");

        if(division_big_double(&x, &y, &res))
            printf("Error with division");

        from_big_double_to_str(res_str, &res);

        printf("Success, your result = %s\n", res_str);
    }
}
