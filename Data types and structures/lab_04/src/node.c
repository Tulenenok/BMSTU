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

void insert_data_to_node_list(char data, size_t index, Node_t *head)
{
    assert(head);

    Node_t *cur = head;
    for(size_t i = 0; i < index; i++, cur = cur->next);
    cur->data = data;
}

char take_data_by_index(int index, Node_t *head)
{
    Node_t *cur = head;
    for(size_t i = 0; i < index; i++, cur = cur->next);
    return cur->data;
}

Node_t *add_first_elem_to_node_list(char new_elem, Node_t *head)
{
    Node_t *new_node = malloc(sizeof(Node_t));
    new_node->data = new_elem;
    new_node->next = head;
    return new_node;
}

Node_t *del_first_elem_from_node_list(Node_t *head)
{
    Node_t *new_head = head->next;
    free(head);
    return new_head;
}

void print_node_list(Node_t *head)
{
    for(Node_t *cur = head; cur; cur = cur->next)
        printf("         %c     address = %p\n", cur->data, cur);
}

