#include "../inc/node.h"

node_t *create_node(node_data_t data)
{
    node_t *new_node = malloc(sizeof(node_t));
    if(!new_node)
        return NULL;
    
    new_node->next = NULL;
    new_node->is_data_fill = true;
    new_node->data = data;
    
    return new_node;
}

void free_for_node_list(node_t *head)
{
    node_t *t = head;
    while(t)
    {
        t = head->next;
        free(head);
        head = t;
    }
}

void insert_data_to_node_list(node_data_t data, size_t index, node_t *head)
{
    node_t *cur = head;
    for(size_t i = 0; i < index; i++, cur = cur->next);
    cur->data = data;
    cur->data = true;
}

void push_back(node_data_t data, node_t **head)
{
    if(NULL == *head)
        *head = create_node(data);

    node_t *cur = *head;
    for(; cur->next; cur = cur->next);
    cur->next = create_node(data);
}

void print_node_list(node_t *head)
{
    while(head->next)
    {
        if(head->is_data_fill == true)
        {
            printf(NODE_DATA_SPECIFIER, head->data);
            printf(" -> ");
        }
        head = head->next;
    }
    if(head->is_data_fill == true)
        printf(NODE_DATA_SPECIFIER, head->data);
    printf("\n");
}

node_t *find_data_in_node_list(int *count_cmp, node_data_t data, node_t *head)
{
    while(head)
    {
        (*count_cmp)++;
        if(head->data == data && head->is_data_fill == true)
            return head;
        head = head->next;
    }
    return NULL;
}