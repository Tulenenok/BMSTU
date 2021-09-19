#ifndef _BIG_DOUBLE_H_
#define _BIG_DOUBLE_H_

#include <stdio.h>
#include <stdlib.h>

#define M_LEN 30
#define E_LEN 5

typedef struct
{
    int is_negative_m;
    int mantissa[M_LEN];
    int is_negative_e;
    int exponent[E_LEN];
} big_double_t;

int is_big_double(char s[]);

int from_str_to_big_double(char s[], big_double_t *x);

void from_big_double_to_str(char s[], big_double_t *x);

int division_big_double(big_double_t *x, big_double_t *y, big_double_t *z);

#endif // _BIG_DOUBLE_H_
