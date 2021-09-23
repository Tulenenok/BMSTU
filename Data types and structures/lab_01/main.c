#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"
#include "big_int.h"
#include "big_double.h"
#include "big_double_tools.h"
#include "big_types.h"

int main(void)
{
    int rc = EXIT_SUCCESS;

    big_int_t bi = { 0 };
    big_double_t bd = { 0 };
    big_double_t res = { 0 };

    setbuf(stdout, 0);

    printf("                 : s||||5||||0||||5||||0||||5||||0\n");
    printf("Input big_int    : ");
    if((rc = big_int_scan(stdin, &bi)))
    {
//        if(rc == ERROR_WITH_FILE)
//            printf("Invalid input big_int, error with reading from file.");
        if(rc == BLANK_STRING)
            printf("Invalid input big_int, input is empty.");
        if(rc == IS_NOT_BIG_INT)
            printf("Invalid input big_int, your input is not big_int number.");
        return rc;
    }

    printf("Input big_double : ");
    if((rc = big_double_scan(stdin, &bd)))
    {
//        if(rc == ERROR_WITH_FILE)
//            printf("Invalid input big_double, error with reading from file.");
        if(rc == BLANK_STRING)
            printf("Invalid input big_double, input is empty.");
        if(rc == IS_NOT_SCIENTIFIC)
            printf("Invalid input big_double, your input is not scientific number.");
        if(rc == OVERFLOW)
            printf("Invalid input big_double, the number is too large.");
        return rc;
    }

    if((rc = division_bi_bd(&bi, &bd, &res)))
    {
        if(rc == DIVISION_BY_ZERO)
            printf("Division by zero");
        if(rc == OVERFLOW)
            printf("Overflow");
        return rc;
    }

    printf("Answer : ");
    big_double_print(stdout, &res);

    return EXIT_SUCCESS;
}
