#include <assert.h>

#include "tree_node.h"

tree_node_t *create_tree_node(void *data)
{
    tree_node_t *new_node = malloc(sizeof(tree_node_t));
    if(!new_node)
        return NULL;

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

tree_node_t *insert(tree_node_t *new_elem, tree_node_t *head, int (*cmp_data)(void *, void *))
{
    if(head == NULL)
        return new_elem;

    int rc_cmp = cmp_data(new_elem->data, head->data);
    assert(rc_cmp != 0);      // обычно предполагается, что в дереве нет дубликатов

    if(rc_cmp < 0)
        head->left = insert(new_elem, head->left, cmp_data);
    else
        head->right = insert(new_elem, head->right, cmp_data);

    return head;
}

tree_node_t *find(tree_node_t *node, tree_node_t *head, int (*cmp_data)(void *, void *))
{
    if(head == NULL)
        return NULL;

    int rc_cmp = cmp_data(node->data, head->data);
    if(rc_cmp == 0)
        return head;

    if(rc_cmp < 0)
        return find(node, head->left, cmp_data);
    else
        return find(node, head->right, cmp_data);
}

tree_node_t *find_with_while(tree_node_t *node, tree_node_t *head, int (*cmp_data)(void *, void *))
{
    while(head != NULL)
    {
        int rc_cmp = cmp_data(node->data, head->data);
        if(rc_cmp == 0)
            return head;

        if(rc_cmp < 0)
            head = head->left;
        else
            head = head->right;
    }
    return NULL;
}

void print_tree_node(tree_node_t *node, void *arg)
{
    char *format = arg;
    int *data = node->data;
    printf(format, *data);
}

void pre_order(tree_node_t *head, void (*action)(tree_node_t *, void *), void *arg)
{
    if(head == NULL)
        return ;

    action(head, arg);
    pre_order(head->left, action, arg);
    pre_order(head->right, action, arg);
}

void in_order(tree_node_t *head, void (*action)(tree_node_t *, void *), void *arg)
{
    if(head == NULL)
        return ;

    in_order(head->left, action, arg);
    action(head, arg);
    in_order(head->right, action, arg);
}

void post_order(tree_node_t *head, void (*action)(tree_node_t *, void *), void *arg)
{
    if(head == NULL)
        return ;

    post_order(head->left, action, arg);
    post_order(head->right, action, arg);
    action(head, arg);
}

void to_dot_help_func(struct tree_node *tree, void *arg)
{
    FILE *f = arg;

    if (tree->left)
        fprintf(f, "%d -> %d;\n", *(int *)tree->data, *(int *)tree->left->data);

    if (tree->right)
        fprintf(f, "%d -> %d;\n", *(int *)tree->data, *(int *)tree->right->data);
}

void export_to_dot(FILE *f, const char *tree_name, tree_node_t *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);
    pre_order(tree, to_dot_help_func, f);
    fprintf(f, "}\n");
}

void free_tree_node(tree_node_t *node, void *arg)
{
    free(node);
}

void free_tree(tree_node_t *head)
{
    post_order(head, free_tree_node, NULL);
}
