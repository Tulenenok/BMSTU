#define _GNU_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//    char *str = strdup(STR);
//    if(!str)
//        return ERROR;
//    printf("%s", str);
//    free(str);

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

//    char *str = NULL;
//
//    int n = snprintf(NULL, 0, STR);
//    if(n > 0)
//    {
//        str = calloc(n + 1, sizeof(char));
//        if(!str)
//            return 100;
//
//        snprintf(str, n + 1, STR);
//        printf("%s", str);
//        free(str);
//    }

    char *str = NULL;
    int n = asprintf(&str, STR);
    if(n > 0)
    {
        printf("%s", str);
        free(str);
    }

    return 0;
}