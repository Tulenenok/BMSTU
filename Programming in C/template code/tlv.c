#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct
{
    int tag;
    int size;
    int data[];
} tlv_t;

tlv_t *create_tlv(int tag, int size, int data[])
{
    assert(size != 0);

    tlv_t *new = malloc(sizeof(tlv_t) + size * sizeof(int));
    if(!new)
        return NULL;

    new->tag = tag;
    new->size = size;
    memcpy(new->data, data, size * sizeof(int));

    return new;
}

void free_tlv(tlv_t *p)
{
    free(p);
}

int write_tlv(FILE *f, tlv_t *tlv)
{
    printf("%llu ", fwrite(tlv, sizeof(*tlv) + tlv->size * sizeof(int), 1, f));
    return EXIT_SUCCESS;
}

tlv_t *read_tlv(FILE *f)
{
    tlv_t t;

    if(fread(&t, sizeof(tlv_t), 1, f) != 1)
        return NULL;

    tlv_t *n = malloc(sizeof(tlv_t) + t.size * sizeof(int));
    if(!n)
        return NULL;

    memcpy(n, &t, sizeof(tlv_t));

    if(fread(n->data, t.size * sizeof(int), 1, f) != 1)
    {
        free(n);
        return NULL;
    }

    return n;
}

void print_tlv(tlv_t *t)
{
    printf("\n");
    printf("%d %d\n", t->tag, t->size);
    for(int i = 0; i < t->size; i++)
        printf("%d ", t->data[i]);
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5, 6};
    tlv_t *tlv = create_tlv(-1, 6, a);
    if(tlv == NULL)
        return 100;

    FILE *f = fopen("..\\tlv.txt", "wb+");
    if(!f)
    {
        free_tlv(tlv);
        return 200;
    }

    print_tlv(tlv);

    write_tlv(f, tlv);

    rewind(f);

    tlv_t *new_tlv = read_tlv(f);
    if(new_tlv != NULL)
        print_tlv(new_tlv);


    fclose(f);
    free_tlv(new_tlv);
    free_tlv(tlv);
}
