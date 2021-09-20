#include <string.h>
#include <ctype.h>

#include "tools.h"

int is_scientific(char s[])
{
    // [+-]? (\d+ ([.]\d*)? ([E][+-]? \d+)? |
    // [+-]?  [.]\d+        ([E][+-]? \d+)?

    size_t i = 0;
    int was_point = 0;
    int was_e = 0;

    for (; s[i] && isspace((int)s[i]); i++);

    if (s[i] == '+' || s[i] == '-')
        i++;

    if (s[i] == '.')
    {
        was_point = 1;
        i++;
    }

    if (!isdigit((int)s[i]))
        return FALSE;

    for (; s[i] && isdigit((int)s[i]); i++);

    if (s[i] && !was_point && s[i] == '.')
        i++;

    for (; s[i] && isdigit((int)s[i]); i++);

    for (; s[i] && isspace((int)s[i]); i++);             // До и после Е может быть любое число пробельных символов
    if (s[i] == 'E' || s[i] == 'e')
    {
        was_e = 1;
        i++;
    }
    for (; s[i] && isspace((int)s[i]); i++);

    if (was_e && (s[i] == '+' || s[i] == '-'))
        i++;

    if (was_e && !isdigit((int)s[i]))
        return FALSE;

    for (; was_e && s[i] && isdigit((int)s[i]); i++);
    for (; s[i] && isspace((int)s[i]); i++);

    if (!s[i])
        return TRUE;
    return FALSE;
}

int increase_by_one(int arr[], size_t len)
{
    int transfer = 0;
    for(size_t i = len; i > 0; i--)
    {
        int s = arr[i - 1] + transfer + 1 * (i == len);
        arr[i - 1] = s - s / 10 * 10;
        transfer = s / 10;
    }

    if(transfer != 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int is_null_arr(int arr[], size_t len)
{
    for(size_t i = 0; i < len; i++)
        if(arr[i] != 0)
            return FALSE;
    return TRUE;
}

int reduce_by_one(int arr[], size_t len)
{
    if(is_null_arr(arr, len))
        return EXIT_FAILURE;

    int transfer = 0;
    for(size_t i = len; i > 0; i--)
    {
        int d = arr[i - 1] - transfer - 1 * (i == len);
        transfer = d < 0;
        d += transfer * 10;

        arr[i - 1] = d - d / 10 * 10;

    }

    return EXIT_SUCCESS;
}

int reduce_one_with_sign(int arr[], size_t len, int *sign)
{
    int rc = EXIT_SUCCESS;

    if(is_null_arr(arr, len))
        *sign = 1;

    if(*sign == 1)
        rc = increase_by_one(arr, len);
    else
        rc = reduce_by_one(arr, len);

    if(is_null_arr(arr, len))
        *sign = 0;
    return rc;
}

int increase_one_with_sign(int arr[], size_t len, int *sign)
{
    int rc = EXIT_SUCCESS;

    if(is_null_arr(arr, len))
        *sign = 0;

    if(*sign == 0)
        rc = increase_by_one(arr, len);
    else
        rc = reduce_by_one(arr, len);

    if(is_null_arr(arr, len))
        *sign = 0;
    return rc;
}

int rounding(int arr[], size_t len)
{
    if(increase_by_one(arr, len))
    {
        for(size_t i = len; i > 1; i--)
            arr[i - 1] = arr[i - 2];
        arr[0] = 1;
        return WAS_OVERFLOW;
    }
    return NO_OVERFLOW;
}

int insert_end(int arr[], size_t len, int x)
{
    if(arr[0] != 0)
        return WAS_OVERFLOW;

    for(size_t i = 0; i < len - 1; i++)
        arr[i] = arr[i + 1];
    arr[len - 1] = x;

    return NO_OVERFLOW;
}

int from_char_to_int_digit(char x)
{
    switch (x)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    default:
        return NOT_DIGIT;
    }
}

char from_int_to_char_digit(int x)
{
    switch (x)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    default:
        return NOT_DIGIT;
    }
}

int arr_cmp(int arr_a[], size_t len_a, int arr_b[], size_t len_b)
{
    if(len_a != len_b)
        return (int) (len_a - len_b);

    for(size_t i = 0; i < len_a; i++)
        if(arr_a[i] != arr_b[i])
            return arr_a[i] - arr_b[i];
    return 0;
}

void fill_arr(int arr[], size_t len, int x)
{
    for(size_t i = 0; i < len; i++)
        arr[i] = x;
}

void shift_left(int arr[], size_t len, size_t pos)
{
    size_t j = 0;
    for(size_t i = pos; i < len; i++, j++)
        arr[j] = arr[i];
    for(; j < len; j++)
        arr[j] = 0;
}
void shift_right(int arr[], size_t len, size_t pos)
{
    size_t j = len;
    for(size_t i = len; i > pos; i--, j--)
        arr[j - 1] = arr[i - 1 - pos];

    for(; j > 0; j--)
        arr[j - 1] = 0;
}

int arr_cpy(int arr_a[], size_t len_a, int arr_b[], size_t len_b)
{
    if(len_a != len_b)
        return EXIT_FAILURE;
    for(size_t i = 0; i < len_a; i++)
        arr_b[i] = arr_a[i];
    return EXIT_SUCCESS;
}
int arr_cpy_to_end(int arr_a[], size_t len_a, int arr_b[], size_t len_b)
{
    if(len_a > len_b)
        return EXIT_FAILURE;

    size_t i = len_a, j = len_b;
    for(; i > 0 && arr_a[i - 1] == 0; i--);

    for(; i > 0 && j > 0; i--, j--)
        arr_b[j - 1] = arr_a[i - 1];

    for(; j > 0; j--)
        arr_b[j - 1] = 0;

    return EXIT_SUCCESS;
}

int arr_cpy_to_start(int arr_a[], size_t len_a, int arr_b[], size_t len_b)
{
//    if(len_a < len_b)
//        return EXIT_FAILURE;

    size_t i = 0, j = 0;
    for(; i < len_a && arr_a[i] == 0; i++);

    for(; i < len_a && j < len_b; i++, j++)
        arr_b[j] = arr_a[i];

    for(; j < len_b; j++)
        arr_b[j] = 0;

    return EXIT_SUCCESS;
}

int add(int x[], size_t x_len, int y[], size_t y_len, int z[], size_t z_len)
{
    if(x_len != y_len || x_len != z_len)
        return EXIT_FAILURE;

    int transfer = 0;
    for(size_t i = x_len; i > 0; i--)
    {
        int s = x[i - 1] + y[i - 1] + transfer;
        transfer = s / 10;
        z[i - 1] = s - s / 10 * 10;
    }

    if(transfer != 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

// Реализует вычитание для двух целых положительных чисел, представленных в виде массива
// Уменьшаемое должно быть >= вычитаемого, длина массива-разности должна быть >= длинне уменьшаемого
int subtract(int minuend[], size_t m_len, int subtrahend[], size_t s_len, int residual[], size_t r_len)
{
    int m_s_cmp = arr_cmp(minuend, m_len, subtrahend, s_len);
    if(m_s_cmp < 0 || r_len < m_len)
        return EXIT_FAILURE;

    fill_arr(residual, r_len, 0);

//    if(m_s_cmp == 0)
//        return EXIT_SUCCESS;

    int transfer = 0;
    size_t i = m_len, j = s_len, k = r_len;
    for(; j > 0; i--, j--, k--)
    {
        int d = minuend[i - 1] - subtrahend[j - 1] - transfer;
        transfer = d < 0;
        d += transfer * 10;

        residual[k - 1] = d - d / 10 * 10;
    }

    for(; i > 0; i--, k--)
    {
        int d = minuend[i - 1] - transfer;
        transfer = d < 0;
        residual[k - 1] = d - d / 10 * 10;
    }
    return EXIT_SUCCESS;
}


int division(int x[], size_t x_len, int y[], size_t y_len, int div[], size_t div_len, int mod[], size_t mod_len)
{
    if(is_null_arr(y, y_len))
        return EXIT_FAILURE;

    if(arr_cpy(x, x_len, mod, mod_len) || x_len != y_len)
        return EXIT_FAILURE;

    fill_arr(div, div_len, 0);

     while(arr_cmp(x, x_len, y, y_len) >= 0)
        {
            subtract(x, x_len, y, y_len, mod, mod_len);
            arr_cpy(mod, mod_len, x, x_len);
            increase_by_one(div, div_len);
//            for(size_t i = 0; i < x_len; i++)
//                printf("%d", x[i]);
//            printf("\n");
        }

     return EXIT_SUCCESS;
}

int input_str(FILE *f, char s[])
{
    char buf;
    int i = 0;
    int is_blank_str = TRUE;

    for (; fscanf(f, "%c", &buf) == 1 && buf != '\n'; i++)
    {
        s[i] = buf;
        if (buf != ' ')
            is_blank_str = FALSE;
    }

//    if (ferror(f))
//        return ERROR_WITH_FILE;

    s[i] = '\0';

    if (i == 0 || is_blank_str)
        return BLANK_STRING;

    return EXIT_SUCCESS;
}



