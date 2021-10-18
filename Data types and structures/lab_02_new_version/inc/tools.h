#ifndef LAB_02_NEW_VERSION_TOOLS_H
#define LAB_02_NEW_VERSION_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BLANK_STRING -1
#define MAX_STR 30
#define COLUMNS 10
#define MAX_SIZE 1000
#define MAX_OUTPUT_COUNT 10

int is_adress_correct(char adr[]);

int is_dec_correct(char dec[]);

int is_bin_correct(char bin[]);

int is_data_correct(char data[][MAX_STR]);

void split(char str[], char arr[][MAX_STR], char delims[], size_t *n);

#endif //LAB_02_NEW_VERSION_TOOLS_H
