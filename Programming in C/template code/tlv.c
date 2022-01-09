#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define ERROR 100

typedef struct
{
    int tag;
    int len;
    int data[];
} tlv_t;

tlv_t *create_tlv(int _tag, int _len, int _data[])
{
    assert(_len > 0);

    tlv_t *new_tlv = malloc(sizeof(tlv_t) + _len * sizeof(int));
    if(!new_tlv)
        return NULL;

    new_tlv->tag = _tag;
    new_tlv->len = _len;

    memcpy(new_tlv->data, _data, _len * sizeof(int));
    return new_tlv;
}

void free_tlv(tlv_t *tlv)
{
    free(tlv);
}

void print_tlv(tlv_t *tlv)
{
    printf("Tag: %d\nLength: %d\nArray: ", tlv->tag, tlv->len);
    for(int i = 0; i < tlv->len; i++)
        printf("%d ", tlv->data[i]);
    printf("\n");
}

int write_to_file(FILE *f, tlv_t *tlv)
{
    if(fwrite(tlv, sizeof(tlv_t) + tlv->len * sizeof(int), 1, f) != 1)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

tlv_t *read_from_file(FILE *f)
{
    tlv_t t;
    if(fread(&t, sizeof(tlv_t), 1, f) != 1)
        return NULL;

    tlv_t *new_tlv = malloc(sizeof(tlv_t) + t.len * sizeof(int));
    if(!new_tlv)
        return NULL;

    memcpy(new_tlv, &t, sizeof(tlv_t));

    if(fread(new_tlv->data, new_tlv->len * sizeof(int), 1, f) != 1)
        return NULL;

    return new_tlv;
}

int main(void)
{
    int data[] = {1, 2, 3, 4, 5};
    tlv_t *tlv = create_tlv(10, 5, data);
    if(!tlv)
        return ERROR;

    print_tlv(tlv);

    FILE *f = fopen("..\\tlv.txt", "wb+");
    if(!f)
        return ERROR;

    write_to_file(f, tlv);
    free_tlv(tlv);

    rewind(f);

    tlv_t *new_tlv = read_from_file(f);
    if(new_tlv)
        print_tlv(new_tlv);

    fclose(f);
    free_tlv(new_tlv);
    return 0;
}
