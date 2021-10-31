#include <string.h>

#include "../inc/modes.h"
#include "../inc/sparse_matrix.h"
#include "../inc/matrix.h"
#include "../inc/index_matrix.h"
#include "../inc/take_time.h"

int mode_print_matrix_from_file_to_sparse_matrix(char filename[], int *num_matrix)
{
    FILE *f = fopen(filename, "r");

    if(!f)
    {
        printf("Open file:                   ----> FAILURE\n");
        return ERROR_WITH_FILE;
    }

    printf("Open file:                   ----> SUCCESS\n");

    int rc;
    sparse_matrix_t matrix = { 0 };
    if((rc = input_sparse_matrix_from_file(f, &matrix)))
    {
        printf("Input matrix:                ----> FAILURE\n");
        return rc;
    }

    printf("Input matrix:                ----> SUCCESS\n");

    print_sparse_matrix_to_file(stdout, &matrix);

    free_matrix(matrix);
    rewind(f);

    save_matrix_in_file(f, num_matrix, false);
    fclose(f);
    return EXIT_SUCCESS;
}

int mode_print_matrix_from_stdin_to_sparse_matrix(int *num_matrix)
{
    int rc;

    if((rc = save_matrix_in_file(stdin, num_matrix, true)))
    {
        printf("Input matrix:                ----> FAILURE\n");
        return rc;
    }

    printf("Input matrix:                ----> SUCCESS\n");


    char fileout[MAX_LEN_STR];
    sparse_matrix_t matrix = { 0 };
    find_filename_by_name(*num_matrix, fileout);

    FILE *f = fopen(fileout, "r");

    input_sparse_matrix_from_file(f, &matrix);
    print_sparse_matrix_to_file(stdout, &matrix);

    free_matrix(matrix);
    fclose(f);
    return EXIT_SUCCESS;
}

int help_func_input_vector_from_file(void)
{
    printf("\nWARNING : You have already entered vector, it will be lost when you enter a new one\n");
    printf("How resolve this problem?\n");
    printf("    0 - stop input new vector\n");
    printf("    1 - input vector without save\n");
    printf("    2 - save vector and input new vector\n");
    printf("Input command:");

    int choose = 0;
    if (INPUT_ONE_ELEM != fscanf(stdin, "%d", &choose) || (choose != 0 && choose != 1 && choose != 2)) {
        printf("Invalid command\n");
        return EXIT_FAILURE;
    }

    if (0 == choose)
        return EXIT_FAILURE;

    if (2 == choose)
        return save_vector_to_file();
    return EXIT_SUCCESS;
}

int help_func_input_matrix_from_file(void)
{
    printf("\nWARNING : You have already entered matrix, it will be lost when you enter a new one\n");
    printf("How resolve this problem?\n");
    printf("    0 - stop input new matrix\n");
    printf("    1 - input matrix without save\n");
    printf("    2 - save matrix and input new matrix\n");
    printf("Input command:");

    int choose = 0;
    if (INPUT_ONE_ELEM != fscanf(stdin, "%d", &choose) || (choose != 0 && choose != 1 && choose != 2)) {
        printf("Invalid command\n");
        return EXIT_FAILURE;
    }

    if (0 == choose)
        return EXIT_FAILURE;

    if (2 == choose)
        save_matrix_to_file();

    return EXIT_SUCCESS;
}

int mode_input_matrix_from_file(bool *is_matrix_input)
{
    if(*is_matrix_input)
        if(help_func_input_matrix_from_file())
            return EXIT_FAILURE;

    printf("Input name of file for read matrix:");
    char s[1000];
    if(INPUT_ONE_ELEM != scanf("%s", s))
        return 200;

    FILE *fin = fopen(s, "r");
    if(!fin)
    {
        printf("Invalid file");
        return EXIT_FAILURE;
    }

    int rc;

    FILE *f = fopen("..\\shared\\matrix.txt", "w");
    if((rc = input_matrix_from_file_and_save(fin, f)))
        return rc;

    printf("Input matrix              ---->SUCCESS");
    *is_matrix_input = true;

    fclose(f);
    fclose(fin);
    return rc;
}

int mode_input_matrix_from_keyboard(bool *is_matrix_input)
{
    if(*is_matrix_input)
        if(help_func_input_matrix_from_file())
            return EXIT_FAILURE;

    int rc;
    size_t r, c;
    if((rc = input_size_of_matrix(stdin, &r, &c, true)))
        return rc;

    if(input_matrix((int) r, (int) c))
        return EXIT_FAILURE;

    *is_matrix_input = true;
    return rc;
}

int mode_input_vector_from_file(bool *is_vector_input)
{
    if(*is_vector_input)
        if(help_func_input_vector_from_file())
            return EXIT_FAILURE;

    printf("Input name of file for read vector:");
    char s[1000];
    if(INPUT_ONE_ELEM != scanf("%s", s))
        return 200;

    FILE *fin = fopen(s, "r");
    if(!fin)
    {
        printf("Invalid file");
        return EXIT_FAILURE;
    }

    int rc;

    FILE *f = fopen("..\\shared\\vector.txt", "w");
    if((rc = input_vector_from_file_and_save(fin, f)))
        return rc;

    printf("Input vector              ---->SUCCESS");
    *is_vector_input = true;

    fclose(f);
    fclose(fin);
    return rc;
}

int mode_input_vector_from_keyboard(bool *is_vector_input)
{
    if(*is_vector_input)
        if(help_func_input_vector_from_file())
            return EXIT_FAILURE;

    int rc;
    size_t r, c = 1;
    printf("Input count rows in vector:");
    if(INPUT_ONE_ELEM != scanf("%zu", &r) || r == 0)
    {
        printf("Invalid count rows\n");
        return EXIT_FAILURE;
    }

    if(r == 0)
    {
        printf("Invalid size\n");
        return EXIT_FAILURE;
    }

    if(input_vector((int) r, (int) c))
        return EXIT_FAILURE;

    *is_vector_input = true;
    return rc;
}

void mode_save_matrix(bool is_matrix_input)
{
    if(!is_matrix_input)
        printf("Matrix was not input\n");
    else
        save_matrix_to_file();
}

void mode_save_vector(bool is_vector_input)
{
    if(!is_vector_input)
        printf("Vector was not input\n");
    else
        save_vector_to_file();
}

int mode_print_classic_matrix(bool is_matrix_input)
{
    if(!is_matrix_input)
        printf("Matrix was not input\n");
    else
    {
        FILE *f = fopen("..\\shared\\matrix.txt", "r");
        if(!f)
        {
            printf("Problems with print\n");
            return EXIT_FAILURE;
        }

        matrix_t m;
        if(input_matrix_from_file(f, &m))
        {
            printf("FAILURE\n");
            fclose(f);
            return EXIT_FAILURE;
        }

        fclose(f);
        printf("\nYOUR MATRIX:\n");
        print_matrix_to_file(stdout, &m);
        printf("\n");
        free_classic_matrix(&m);
    }
    return EXIT_SUCCESS;
}

int mode_print_classic_vector(bool is_vector_input)
{
    if(!is_vector_input)
        printf("Vector was not input\n");
    else
    {
        FILE *f = fopen("..\\shared\\vector.txt", "r");
        if(!f)
        {
            printf("Problems with print\n");
            return EXIT_FAILURE;
        }

        matrix_t m;
        if(input_matrix_from_file(f, &m))
        {
            printf("FAILURE\n");
            fclose(f);
            return EXIT_FAILURE;
        }

        fclose(f);

        printf("\nYOUR VECTOR:\n");
        print_matrix_to_file(stdout, &m);
        printf("\n");
        free_classic_matrix(&m);
    }
    return EXIT_SUCCESS;
}

void mode_print_classic(bool is_matrix_input, bool is_vector_input)
{
    mode_print_classic_matrix(is_matrix_input);
    mode_print_classic_vector(is_vector_input);
}

int mode_print_sparse_matrix(bool is_matrix_input)
{
    if(!is_matrix_input)
        printf("\nMatrix was not input\n");
    else
    {
        FILE *f = fopen("..\\shared\\matrix.txt", "r");
        if(!f)
        {
            printf("Problems with print\n");
            return EXIT_FAILURE;
        }

        int rc;
        sparse_matrix_t matrix = { 0 };
        if((rc = input_sparse_matrix_from_file(f, &matrix)))
        {
            printf("Input matrix:                ----> FAILURE\n");
            return rc;
        }

        printf("\nYOUR MATRIX:\n");
        print_sparse_matrix_to_file(stdout, &matrix);

        free_matrix(matrix);
        fclose(f);
    }
    return EXIT_SUCCESS;
}


int mode_print_sparse_vector(bool is_vector_input)
{
    if(!is_vector_input)
        printf("\nVector was not input\n");
    else
    {
        FILE *f = fopen("..\\shared\\vector.txt", "r");
        if(!f)
        {
            printf("Problems with print\n");
            return EXIT_FAILURE;
        }

        int rc;
        sparse_matrix_t matrix = { 0 };
        if((rc = input_sparse_vector_from_file(f, &matrix)))
        {
            printf("Input vector:                ----> FAILURE\n");
            return rc;
        }

        fclose(f);

        printf("\nYOUR VECTOR:\n");
        print_sparse_matrix_to_file(stdout, &matrix);

        free_matrix(matrix);
        fclose(f);
    }
    return EXIT_SUCCESS;
}

void mode_print_sparse(bool is_matrix_input, bool is_vector_input)
{
    mode_print_sparse_matrix(is_matrix_input);
    mode_print_sparse_vector(is_vector_input);
}


int mode_multiply_sparse_method(bool is_matrix_input, bool is_vector_input)
{
    if(!is_vector_input)
    {
        printf("\nVector was not input\n");
        return EXIT_SUCCESS;
    }

    if(!is_matrix_input)
    {
        printf("\nMatrix was not input\n");
        return EXIT_SUCCESS;
    }

    FILE *f_matrix = fopen("..\\shared\\matrix.txt", "r");
    if(!f_matrix)
    {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    index_matrix_t mat;
    if(input_index_matrix_from_file(f_matrix, &mat))
    {
        printf("ERROR WITH MATRIX\n");
        fclose(f_matrix);
        return EXIT_FAILURE;
    }

    fclose(f_matrix);

    FILE *f_vector = fopen("..\\shared\\vector.txt", "r");
    if(!f_vector)
    {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    index_matrix_t vec;
    if(input_index_matrix_from_file(f_vector, &vec))
    {
        printf("ERROR WITH VECTOR\n");
        fclose(f_vector);
        return EXIT_FAILURE;
    }

    fclose(f_vector);

//    printf("[DBG]: Matrix:\n");
//    print_index_matrix(stdout, &mat);
//    printf("[DBG]: Vector:\n");
//    print_index_matrix(stdout, &vec);
//    printf("\n");

    index_matrix_t res;
    if(mat.count_columns != vec.count_rows)
    {
        printf("Invalid sizes of matrix and vector");
        return EXIT_FAILURE;
    }
    if(multiply_index_matrix(&mat, &vec, &res))
    {
        printf("ERROR WITH MULTIPLY\n");
        return EXIT_FAILURE;
    }

    FILE *fout = fopen("..\\shared\\multiply_sparse.txt", "w");
    print_index_matrix_in_usual_format(fout, &res);

    fclose(fout);

    sparse_matrix_t m;
    FILE *f = fopen("..\\shared\\multiply_sparse.txt", "r");
    if(input_sparse_vector_from_file(f, &m))
    {
        printf("STRANGE ERROR, DONT CRY");
        fclose(f);
        return EXIT_FAILURE;
    }

    printf("Result matrix:\n");
    print_sparse_matrix_to_file(stdout, &m);

    fclose(f);
    return EXIT_SUCCESS;
}

int mode_multiply_classic_method(bool is_matrix_input, bool is_vector_input)
{
    if(!is_vector_input)
    {
        printf("\nVector was not input\n");
        return EXIT_SUCCESS;
    }

    if(!is_matrix_input)
    {
        printf("\nMatrix was not input\n");
        return EXIT_SUCCESS;
    }

    FILE *f_matrix = fopen("..\\shared\\matrix.txt", "r");
    if(!f_matrix)
    {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    matrix_t mat;
    if( input_matrix_from_file(f_matrix, &mat))
    {
        printf("ERROR WITH MATRIX\n");
        fclose(f_matrix);
        return EXIT_FAILURE;
    }

    fclose(f_matrix);

    FILE *f_vector = fopen("..\\shared\\vector.txt", "r");
    if(!f_vector)
    {
        printf("FAILURE\n");
        return EXIT_FAILURE;
    }

    matrix_t vec;
    if(input_matrix_from_file(f_vector, &vec) || vec.rows == 0 ||vec.columns != 1)
    {
        printf("ERROR WITH VECTOR\n");
        fclose(f_vector);
        return EXIT_FAILURE;
    }

    fclose(f_vector);

    matrix_t res;
    if(mat.columns != vec.rows)
    {
        printf("Invalid sizes of matrix and vector");
        return EXIT_FAILURE;
    }
    if(multiply_matrix(&mat, &vec, &res))
    {
        printf("ERROR WITH MULTIPLY\n");
        return EXIT_FAILURE;
    }

    FILE *fout = fopen("..\\shared\\multiply_classic.txt", "w");
    print_matrix_to_file(fout, &res);

    fclose(fout);

    printf("\nYOUR MATRIX:\n");
    print_matrix_to_file(stdout, &res);
    return EXIT_SUCCESS;
}

int mode_generate_matrix(bool *is_matrix_input)
{
    if(*is_matrix_input)
        if(help_func_input_matrix_from_file())
            return EXIT_FAILURE;

    size_t r = 0, c = 0, d = 0;
    if(input_size_of_matrix(stdin, &r, &c, true))
        return EXIT_FAILURE;

    printf("Input density:");
    if(INPUT_ONE_ELEM != scanf("%zu", &d))
    {
        printf("Invalid density\n");
        return EXIT_FAILURE;
    }
    generate_matrix((int)c, (int)r, (int)d);

    printf("\nGenerate matrix         ---> SUCCESS\n");

    *is_matrix_input = true;
    return EXIT_SUCCESS;
}

int mode_generate_vector(bool *is_vector_input)
{
    if(*is_vector_input)
        if(help_func_input_vector_from_file())
            return EXIT_FAILURE;

    size_t r = 0, d = 0;
    printf("Input count rows:");
    if(INPUT_ONE_ELEM != scanf("%zu", &r))
    {
        printf("Invalid count rows\n");
        return EXIT_FAILURE;
    }

    printf("Input density:");
    if(INPUT_ONE_ELEM != scanf("%zu", &d))
    {
        printf("Invalid density\n");
        return EXIT_FAILURE;
    }
    generate_vector((int)r, (int)d);

    printf("\nGenerate vector         ---> SUCCESS\n");

    *is_vector_input = true;
    return EXIT_SUCCESS;
}

int mode_report(bool is_matrix_input, bool is_vector_input)
{
    take_time_t sparse_time = { 0 };
    take_time_t classic_time = { 0 };

    int rc;
    if((rc = multiply_sparse_method_with_time(is_matrix_input, is_vector_input, &sparse_time)))
    {
        printf("\nInvalid multiply for sparse method\n");
        return rc;
    }

    if((rc = multiply_classic_method_with_time(is_matrix_input, is_vector_input, &classic_time)))
    {
        printf("\nInvalid multiply for classic method\n");
        return rc;
    }

    unsigned long sparse_memory = 0;
    unsigned long classic_memory = 0;
    if((rc = multiply_sparse_method_with_memory(is_matrix_input, is_vector_input, &sparse_memory)))
    {
        printf("\nInvalid find memory for sparse\n");
        return rc;
    }

    if((rc = multiply_classic_method_with_memory(is_matrix_input, is_vector_input, &classic_memory)))
    {
        printf("\nInvalid find memory for classic\n");
        return rc;
    }


    printf("Method                Time           Memory     \n");
    printf("Sparse       | %10.3lf     | %10.3lu       |\n", (double)sparse_time.time, sparse_memory);
    printf("Classic      | %10.3lf     | %10.3lu       |\n", (double)classic_time.time, classic_memory);

    return EXIT_SUCCESS;
}
