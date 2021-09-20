#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdio.h>
#include <stdlib.h>

#define NOT_DIGIT 100

#define TRUE 1
#define FALSE 0

#define WAS_OVERFLOW 1
#define NO_OVERFLOW 0

// #define ERROR_WITH_FILE 2
#define BLANK_STRING 3

// Проверяет, является ли строка вещественным числом
// Возвращает 1, если является, и 0, если не является
// Не проверяет, является ли строка вещественным числом типа big_double (не учитывает количество разрядов)
int is_scientific(char s[]);

// Увеличивает число-массив на 1
// Возвращает 0, если сложение было произведено успешно, иначе любое ненулевое число (в случае, когда происходит переполнение)
int increase_by_one(int arr[], size_t len);

// Уменьшает число-массив на 1
// Возвращает 0, если вычетание было произведено успешно, иначе любое ненулевое число (в случае, когда идет попытка вычесть из 0)
int reduce_by_one(int arr[], size_t len);

// Проверяет, состоит ли массив только из нулей
// Возвращает 1, если да, иначе 0
int is_null_arr(int arr[], size_t len);

// Прибавить к числу-массиву единицу (с учетом знака)
int increase_one_with_sign(int arr[], size_t len, int *sign);

// Вычесть из массива единицу (с учетом знака)
int reduce_one_with_sign(int arr[], size_t len, int *sign);

// Функция помогает реализовать округление (прибавляет 1 и при переполнении сдвигает разряды вправо)
// Возвращает 0, если переполнения не было, иначе 1
int rounding(int arr[], size_t len);

// Функция добавляет элемент x в конец массива arr предваритеьно сдвигая элементы массива влево на одну позицию
// Возвращает 0, если переполнения не произошло, иначе любое ненулевое число
int insert_end(int arr[], size_t len, int x);

// Функция сравнивает по-элементно два массива
// Возвращает 0, если массивы равны, отрицательное значение, если первый массив меньше второго, иначе положительное значение
int arr_cmp(int arr_a[], size_t len_a, int arr_b[], size_t len_b);

// Функция заполняет массив элементом x
void fill_arr(int arr[], size_t len, int x);

// Сдвигает элементы массива на pos позиций влево, дополняет массив нулями при необходимости
void shift_left(int arr[], size_t len, size_t pos);

// Сдвигает элементы массива на pos позиций вправо, дополняет массив нулями при необходимости
void shift_right(int arr[], size_t len, size_t pos);

// Функция копирует один массив в другой
int arr_cpy(int arr_a[], size_t len_a, int arr_b[], size_t len_b);

// Функция копирует один массив в другой со сдвигом влево
// [1, 2, 3, 0, 0] -> [0, 0, 1, 2, 3]
int arr_cpy_to_end(int arr_a[], size_t len_a, int arr_b[], size_t len_b);

// Функция копирует один массив в другой со сдвигом вправо
// [0, 0, 3, 2, 1] -> [3, 2, 1, 0, 0]
int arr_cpy_to_start(int arr_a[], size_t len_a, int arr_b[], size_t len_b);

// Функция складывает два числа-массива и записывает результат в третий массив.
// Длины всех массивов должны быть одинаковы, при переполнении вызвращает число отличное от нуля.
int add(int x[], size_t x_len, int y[], size_t y_len, int z[], size_t z_len);

// Реализует вычитание для двух целых положительных чисел, представленных в виде массива
// Уменьшаемое должно быть >= вычитаемого, длина массива-разности должна быть >= длинне уменьшаемого
int subtract(int minuend[], size_t m_len, int subtrahend[], size_t s_len, int residual[], size_t r_len);

// Функция делит x на y и находит частное и остаток от деления, длины x, y, mod_len должны совпадать
int division(int x[], size_t x_len, int y[], size_t y_len, int div[], size_t div_len, int mod[], size_t mod_len);

// Функция переводит цифру из типа char в тип int
// Если передана не цифра, возвращает код ошибки NOT_DIGIT
int from_char_to_int_digit(char x);

// Функция переводит цифру из типа int в тип char
// Если передана не цифра, возвращает код ошибки NOT_DIGIT
char from_int_to_char_digit(int x);

// Функция считывает строку максимальной длины max_len из файла
// Возвращает BLANK_STRING, если строка пустая
//            ERROR_WITH_FILE, если в процессе чтения возникли ошибки с файлом
//            EXIT_SUCCESS, в ином случае
int input_str(FILE *f, char s[]);

#endif // _TOOLS_H_
