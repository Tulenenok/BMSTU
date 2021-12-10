#include "../inc/binary_search_tree.h"

tree_node_t *create_tree_node(tree_data_t data)
{
    tree_node_t *new_node = malloc(sizeof(tree_node_t));
    if(!new_node)
        return NULL;

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

tree_node_t *create_tree_from_file(FILE *f, int (*cmp)(tree_data_t, tree_data_t), bool comment_flag)
{
    tree_data_t data;
    if(fscanf(f, TREE_DATA_SPECIFIER, &data) != 1)
    {
        puts("Empty file");
        return NULL;
    }

    tree_node_t *new_tree = create_tree_node(data);

    while(fscanf(f, TREE_DATA_SPECIFIER, &data) == 1)
    {
        tree_node_t *new_node = create_tree_node(data);
        insert(new_tree, new_node, cmp, comment_flag);
    }

    return new_tree;
}

tree_node_t *insert(tree_node_t *tree, tree_node_t *new_node, int (*cmp)(tree_data_t, tree_data_t), bool comment_flag)
{
    if(NULL == tree)
    {
        if(comment_flag)
            printf("INSERT element %d ----> SUCCESS (tree was empty - new create)\n", new_node->data);
        return new_node;
    }

    int rc = cmp(new_node->data, tree->data);
    if(0 == rc)
    {
        if (comment_flag)
            puts("INSERT element ----> FAILURE (such an element already exists)");
    }
    else if (rc < 0)
        tree->left = insert(tree->left, new_node, cmp, false);
    else
        tree->right = insert(tree->right, new_node, cmp, false);

    if (comment_flag)
        printf("INSERT element %d ----> SUCCESS\n", new_node->data);

    return tree;
}

tree_node_t *find(int *count_cmp, tree_node_t *tree, tree_data_t data, int (*cmp)(tree_data_t, tree_data_t))
{
    while(NULL != tree)
    {
        int rc = cmp(data, tree->data);
        (*count_cmp)++;

        if(0 == rc)
            return tree;
        else if(rc < 0)
            tree = tree->left;
        else
            tree = tree->right;
    }

    return tree;
}

void print_bin_search_tree(tree_node_t *head, int down, int strelochka)
{
    if (head)
    {
        print_bin_search_tree(head->right, down + 1, 2);
        for (int i = 0; i < down; i++)
        {
            printf("       ");
        }
        if (strelochka == 1)
        {
            printf(" ➘ ");
        }
        else if (strelochka == 2)
        {
            printf(" ➚ ");
        }
        else if (strelochka == 0)
        {
            printf("   ");
        }

        printf(" %d\n", head->data);

        print_bin_search_tree(head->left, down + 1, 1);
    }
}

// обратный обход дерева
void reverse_go(tree_node_t *root) {
    if (root == NULL) return;
    reverse_go(root->left);
    reverse_go(root->right);
    printf("%d ->", root->data);
}

void free_bin_search_tree(tree_node_t *tree)
{
    if (tree == NULL)
        return;
    free_bin_search_tree(tree->left);
    free_bin_search_tree(tree->right);
    free(tree);
}
