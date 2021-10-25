#include "../inc/node.h"

#include <assert.h>

void malloc_for_node_list(size_t count_elems, Node_t **head)
{
    *head = malloc(sizeof(Node_t));
    (*head)->data = ONLY_NULL_ELEM_IN_COLUMN;

    Node_t *cur = *head;
    for(size_t i = 1; i < count_elems; i++)
    {
        cur->next = malloc(sizeof(Node_t));
        cur->next->data = -1;
        cur = cur->next;
    }
    cur->next = NULL;
}

void free_for_node_list(Node_t *head)
{
    Node_t *cur = head;
    while(cur)
    {
        Node_t *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}

void insert_data_to_node_list_if_data_empty(int data, size_t index, Node_t *head)
{
    assert(head);

    Node_t *cur = head;
    for(size_t i = 0; i < index; i++, cur = cur->next);
    if(ONLY_NULL_ELEM_IN_COLUMN == cur->data)
        cur->data = data;
}

void print_node_list(FILE *f, Node_t *head)
{
    for(Node_t *cur = head; cur; cur = cur->next)
        if(ONLY_NULL_ELEM_IN_COLUMN != cur->data)
            fprintf(f, "%d ", cur->data);
        else
            fprintf(f, "- ");
}