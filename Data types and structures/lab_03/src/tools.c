#include "../inc/tools.h"
#include "dirent.h"
#include "../inc/index_matrix.h"
#include "../inc/node.h"


void concatenate_strings(char str1[], char str2[], char *result_str)
{
    strncpy(result_str, str1, MAX_LEN_STR);
    strncat(result_str, str2, MAX_LEN_STR);
}

int input_size_of_matrix(FILE *f, size_t *r, size_t *c, bool print_comments)
{
    if(print_comments)
        printf("Input count rows:");
    if(INPUT_ONE_ELEM != fscanf(f, "%zu", r))
    {
        if(print_comments)
            printf("Input count rows    ----> FAILURE");
        return INVALID_INPUT_COUNT_ROWS;
    }
    if(print_comments)
        printf("Input count rows             ----> SUCCESS");

    if(print_comments)
        printf("\nInput count columns:");

    if(INPUT_ONE_ELEM != fscanf(f, "%zu", c))
    {
        if(print_comments)
            printf("Input count columns   ----> FAILURE");
        return INVALID_INPUT_COUNT_COLS;
    }
    if(print_comments)
        printf("Input count columns          ----> SUCCESS\n");
    return EXIT_SUCCESS;
}

int input_matrix_from_file_and_save(FILE *fin, FILE *fout)
{
    size_t r, c;
    int rc, t;
    if((rc = input_size_of_matrix(fin, &r, &c, true)))
        return rc;

    fprintf(fout,"%zu %zu", r, c);

    printf("Input matrix:\n");
    for(size_t i = 0; i < r; i++)
    {
        fprintf(fout, "\n");
        for (size_t j = 0; j < c; j++)
            if (1 != fscanf(fin, "%d", &t))
                return INVALID_MATRIX;
            else
                fprintf(fout, " %d", t);
    }
    return EXIT_SUCCESS;
}

int input_vector_from_file_and_save(FILE *fin, FILE *fout)
{
    size_t r, c;
    int rc, t;
    if((rc = input_size_of_matrix(fin, &r, &c, true)))
        return rc;

    if(r == 0 || c != 1)
        return EXIT_FAILURE;

    fprintf(fout,"%zu %zu", r, c);

    printf("Input vector:\n");
    for(size_t i = 0; i < r; i++)
    {
        fprintf(fout, "\n");
        for (size_t j = 0; j < c; j++)
            if (1 != fscanf(fin, "%d", &t))
                return INVALID_MATRIX;
            else
                fprintf(fout, " %d", t);
    }
    return EXIT_SUCCESS;
}

void print_array(FILE *f, size_t count_elems_in_a, size_t size_of_elems, void *a, char format_str[])
{
    for(size_t i = 0; i < count_elems_in_a; i++)
        fprintf(f, format_str, (char *)a + size_of_elems * i);
}

void print_int_array(FILE *f, size_t n, int a[])
{
    for(size_t i = 0; i < n; i++)
        fprintf(f, "%d ", a[i]);
}

void print_size_t_array(FILE *f, size_t n, size_t a[])
{
    for(size_t i = 0; i < n; i++)
        fprintf(f, "%zu ", a[i]);
}

int clean_directory(char dirname[])
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dirname)))
    {
        while ((ent = readdir(dir)))
        {
            if( *(ent->d_name) == '.')
                continue;

            char dir_copy[MAX_LEN_STR];
            strncpy(dir_copy, dirname, MAX_LEN_STR);
            strncat(dir_copy, ent->d_name, MAX_LEN_STR);

            if(remove(dir_copy) == -1)
                printf("Error with delete");

        }

        closedir(dir);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int save_matrix_in_file(FILE *f, int *const num_matrix, bool print_comments)
{
    int rc;

    char filename[MAX_LEN_STR];
    find_filename_by_name(*num_matrix + 1, filename);

    FILE *fout = fopen(filename, "w");

    rc = input_matrix_from_file_and_save(f, fout);

    (*num_matrix)++;
    fclose(fout);
    return rc;
}

void find_filename_by_name(int n, char filename[])
{
    char num_m[MAX_LEN_STR];
    snprintf(num_m, MAX_LEN_STR, "%d", n);

    concatenate_strings(SHARED_DIRECTORY, "matrix_", filename);
    concatenate_strings(filename, num_m, filename);
    concatenate_strings(filename, ".txt", filename);
}


int alloc_memory_for_array(int count_elems, size_t size_elem, int **a)
{
    *a = calloc(count_elems, size_elem);
    if(!a)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int count_not_null_elems_in_file(FILE *const f, const size_t r, const size_t c, size_t *const count)
{
    *count = 0;
    int t;
    for(size_t i = 0; i < r; i++)
        for(size_t j = 0; j < c; j++)
        {
            if(INPUT_ONE_ELEM != fscanf(f, "%d", &t))
                return INVALID_MATRIX;
            if(0 != t)
                (*count)++;
        }

    return EXIT_SUCCESS;
}

//int help_func_input_new_elem()
//
//int input_sparse_matrix_from_stdin(FILE *fout)
//{
//    int rc;
//    size_t r, c, n;
//
//    if((rc = input_size_of_matrix(stdin, &r, &c, true)))
//        return rc;
//
//    printf("Input count of not null elems:");
//    if(INPUT_ONE_ELEM != fscanf(stdin, "%zu", &n) || n == 0)
//    {
//        printf("Invalid count elems\n");
//        return EXIT_FAILURE;
//    }
//
//    index_matrix_t new_matrix;
//    if(create_new_index_matrix(&new_matrix, n))
//    {
//        printf("Error with input");
//        return EXIT_FAILURE;
//    }
//
//    for(size_t i = 0; i < n; i++)
//    {
//        size_t r_elem, c_elem;
//        int elem;
//
//        printf("Input row for new not null elem:");
//        if(INPUT_ONE_ELEM != scanf("%zu", &r_elem) || r_elem == 0)
//        {
//            printf("Input row                ---->FAILURE\n");
//            return EXIT_FAILURE;
//        }
//        printf("Input column for new not null elem:");
//        if(INPUT_ONE_ELEM != scanf("%zu", &c_elem) || c_elem == 0)
//        {
//            printf("Input column                ---->FAILURE");
//            return EXIT_FAILURE;
//        }
//        printf("Input new not null elem:");
//        if(INPUT_ONE_ELEM != scanf("%d", &elem) || elem == 0)
//        {
//            printf("Input elem                 ---->FAILURE");
//            return EXIT_FAILURE;
//        }
//    }
//
//}


int input_matrix(int r, int c)
{
    int *matr = calloc(r*c, sizeof(int));

    int count;
    printf("Number of not null elems (matrix) (max: %d) >> ", r*c);
    if(scanf("%d", &count) != 1 || count < 1 || count > r*c)
        return 1;

    printf("     |r c el\n");
    int x, y;
    for (int i = 0; i < count; ++i)
    {
        printf("%d(%d) |", i + 1, count);
        if(scanf("%d", &y) != 1 || y < 0 || y >= r)
            return 1;

        if(scanf("%d", &x) != 1 || x < 0 || x >= c)
            return 1;

        if(scanf("%d", &matr[y*c + x]) != 1)
            return 1;
    }

    FILE *f;

    if ((f = fopen("..\\shared\\matrix.txt", "w")) == NULL)
        return 1;

    fprintf(f, "%d %d\n", r, c);
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
            fprintf(f, "%d ", matr[i*c + j]);

        fprintf(f, "\n");
    }
    fclose(f);

    free(matr);

    return 0;
}

int input_vector(int r, int c)
{
    int *vector = calloc(r, sizeof(int));

    int count;

    FILE *fv;
    int x;

    printf("Number of nunnul elems (vector) (max: %d) >> ", r);
    if(scanf("%d", &count) != 1 || count < 1 || count > r)
        return 1;
    printf("   |r el\n");
    for (int i = 0; i < count; ++i)
    {
        printf("%d(%d) |", i + 1, count);
        if(scanf("%d", &x) != 1 || x < 0 || x >= r)
            return 1;

        if(scanf("%d", &vector[x]) != 1)
            return 1;
    }

    if ((fv = fopen("..\\shared\\vector.txt", "w")) == NULL)
        return 1;

    fprintf(fv, "%d %d\n", r, c);
    for (int i = 0; i < r; ++i)
        fprintf(fv, "%d\n", vector[i]);

    free(vector);
    fclose(fv);

    return 0;
}

int save_vector_to_file(void)
{
    {
        printf("Enter name of file for save:");
        char s[1000];
        if (INPUT_ONE_ELEM != scanf("%s", s)) {
            printf("Error with input filename");
            return EXIT_FAILURE;
        }

        FILE *fout = fopen(s, "w");
        if (!fout) {
            printf("Invalid filename");
            return EXIT_SUCCESS;
        }

        FILE *fin = fopen("..\\shared\\vector.txt", "r");
        if (!fin) {
            printf("Invalid fin");
            return EXIT_FAILURE;
        }

        int rc;
        if ((rc = input_matrix_from_file_and_save(fin, fout)))
            return rc;

        printf("Save vector               ---->SUCCESS\n\n");
        fclose(fin);
        fclose(fout);
    }
    return EXIT_SUCCESS;
}

int save_matrix_to_file(void)
{
    printf("Enter name of file for save:");
    char s[1000];
    if (INPUT_ONE_ELEM != scanf("%s", s)) {
        printf("Error with input filename");
        return EXIT_FAILURE;
    }

    FILE *fout = fopen(s, "w");
    if (!fout) {
        printf("Invalid filename");
        return EXIT_SUCCESS;
    }

    FILE *fin = fopen("..\\shared\\matrix.txt", "r");
    if (!fin) {
        printf("Invalid fin");
        return EXIT_FAILURE;
    }

    int rc;
    if ((rc = input_matrix_from_file_and_save(fin, fout)))
    {
        printf("Save matrix                     ----> FAILURE\n");
        return rc;
    }

    printf("Save matrix                     ----> SUCCESS\n");
    fclose(fin);
    fclose(fout);

    return EXIT_SUCCESS;
}

int read_data_from_node(Node_t *head, int ind)
{
    Node_t cur = *head;
    for (int i = 0; i < ind; ++i)
        cur = *cur.next;
    return cur.data;
}

void write_node(Node_t *head, int ind, int data)
{
    Node_t *cur = head;
    for (int i = 0; i < ind; ++i)
        cur = cur->next;
    cur->data = data;
}

void generate_matrix(int c, int r, int d)
{
    char command[100] = "python ..\\generate\\gen.py";
    char args[50];
    sprintf(args, " %d %d %d", c, r, d);
    strcat(command, args);
    system(command);
}

void generate_vector(int r, int d)
{

    char command[100] = "python ..\\generate\\gen_v.py";
    char args[50];
    sprintf(args, " %d %d", r, d);
    strcat(command, args);
    system(command);
}