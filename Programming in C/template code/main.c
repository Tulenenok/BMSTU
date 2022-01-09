#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _POSIX_C_SOURCE 200809L
//#define _GNU_SOURCE_

#define STR "Natasha"

#define ERROR 100

int main(void)
{
//    char *str = malloc((strlen(STR) + 1) * sizeof(char));
//    if(!str)
//        return ERROR;
//
//    strncpy(str, STR, strlen(STR));
//
//    printf("%s", str);
//    printf("%d", str[strlen(str)] == '\0');

    char *str = strdup(STR);
    if(!str)
        return ERROR;
    printf("%s", str);
    free(str);

    ///ssize_t getline(char **buf, size_t *n, FILE *f);

//    char *str = NULL;
//    size_t n = 0;
//    FILE *f = fopen("C:\\projects\\exam_preparation\\test.txt", "r");
//    if(!f) {
//        printf("Error file");
//        return 100;
//    }
//
//    int rc = getline(&str, &n, f);
//    if(rc == -1)
//    {
//        printf("Error with getline");
//        return 200;
//    }
//
//    printf("%s", str);
//    free(str);
//    fclose(f);
}