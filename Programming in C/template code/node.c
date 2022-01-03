#include "node.h"

node_t *create_node(void *data)
{
    node_t *new_node = malloc(sizeof(node_t));
    if(!new_node)
        return NULL;

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

void free_node(node_t *node)
{
    free(node);
}

// возвращает указатель на новую голову
node_t *push_front_node(node_t *new_node, node_t *head)
{
    new_node->next = head;
    return new_node;
}

// меняет указатель на голову
void push_front_node_2(node_t *new_node, node_t **head)
{
    new_node->next = *head;
    *head = new_node;
}

node_t *push_back_node(node_t *new_node, node_t *head)
{
    if(head == NULL)
        return new_node;

    node_t *cur = head;
    for(; cur->next; cur = cur->next);
    cur->next = new_node;

    return head;
}

int cmp_int(const void *x, const void *y)
{
    return *(int *)x - *(int *)y;
}

node_t *find_node(void *data, node_t *head, int (*cmp)(const void *, const void *))
{
    for(node_t *cur = head; cur; cur = cur->next)
        if(cmp(data, cur->data) == 0)
            return cur;

    return NULL;
}

void print_node(node_t *node, void *arg)
{
    char *format = arg;
    int *data = (int *)node->data;
    printf(format, *data);
}

void count_elems_in_list(node_t *node, void *arg)
{
    int *counter = arg;
    (*counter)++;
}

void list_apply(node_t *head, void (*action)(node_t *, void *), void *arg)
{
    for(node_t *cur = head; cur; cur = cur->next)
        action(cur, arg);
}

/// вызов: list_apply(head, print_node, "%d");
/// вызов: list_apply(head, count_elems_in_list, &n); (int n = 0; где-то)

/// плохая реализация
/*
 * так делать нельзя, так как мы теряем указатель на сл элемент
void free_list(node_t *head)
{
    for(; head; head = head->next)
        free_node(head);
}
*/

/// хорошая реализация
void free_list(node_t *head)
{
    node_t *next;
    for(; head; head = next)
    {
        next = head->next;
        free_node(head);
    }
}

int push_after_node(node_t *new_node, node_t *node, node_t *head)
{
    for(node_t *cur = head; cur; cur = cur->next)
        if(cur == node)
        {
            new_node->next = cur->next;
            cur->next = new_node;
            return EXIT_SUCCESS;
        }

    return EXIT_FAILURE;  // случай, когда такого узла не существует
}

void swap_data(void *x, void *y)
{
    int *t = x;
    x = (int *)y;
    y = t;
}

node_t *push_before_node_2(node_t *new_node, node_t *node, node_t *head,
                           void (*swap_data)(void *, void *))
{
    for(node_t *cur = head; cur; cur = cur->next)
        if(cur == node)
        {
            new_node->next = cur->next;
            cur->next = new_node;
            swap_data(cur->data, cur->next->data);   //  меняем данные нового и текущего узла

            return head;
        }
    return NULL;
}

node_t *push_before_node(node_t *new_node, node_t *node, node_t *head)
{
    if(node == NULL)
        return push_back_node(new_node, head);

    for(node_t *cur = head; cur->next; cur = cur->next)
        if(cur->next == node)
        {
            new_node->next = cur->next;
            cur->next = new_node;

            return head;
        }

    return NULL;
}

node_t *pop_node(void *data, node_t *head, int (*cmp_data)(const void *, const void *))
{
    node_t *cur = head, *prev = NULL;

    for(; cur; cur = cur->next)
    {
        if (cmp_data(cur->data, data) == 0)
        {
            if (prev == NULL)
                head = cur->next;
            else
                prev->next = cur->next;

            free(cur);
            return head;
        }
        prev = prev->next;     // или cur
    }
    return NULL;   // считается, что лучше возвращать head, чтобы случайно его не потереть
}
