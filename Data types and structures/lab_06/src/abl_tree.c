#include "../inc/abl_tree.h"

int height_of_node(abl_node_t *p);
int find_balance_for_node(abl_node_t *node);
void fix_height(abl_node_t* tree);
abl_node_t *rotate_right(abl_node_t *tree);
abl_node_t *rotate_left(abl_node_t *tree);
abl_node_t *balance(abl_node_t *tree);


abl_node_t *create_abl_node(int _data, int _height, abl_node_t *_left, abl_node_t *_right)
{
    abl_node_t *new_node = malloc(sizeof(abl_node_t));
    if(!new_node)
        return NULL;

    new_node->data = _data;
    new_node->height = _height;
    new_node->left = _left;
    new_node->right = _right;

    return new_node;
}

void free_abl_node(abl_node_t *node)
{
    free(node);
}

void free_abl_tree(abl_node_t *tree)
{
    if (tree == NULL)
        return;
    free_abl_tree(tree->left);
    free_abl_tree(tree->right);
    free(tree);
}

int height_of_node(abl_node_t *p)
{
    return (NULL != p) ? p->height:0;
}

int find_balance_for_node(abl_node_t *node)
{
    return height_of_node(node->right) - height_of_node(node->left);
}

// восстановить высоту дерева по его детям (работает только при правильных детях)
void fix_height(abl_node_t* tree)
{
    int height_left = height_of_node(tree->left);
    int height_right = height_of_node(tree->right);

    tree->height = height_left > height_right ? height_left : height_right;
    tree->height++;
}

abl_node_t *rotate_right(abl_node_t *tree)
{
    abl_node_t *t = tree->left;
    tree->left = t->right;
    t->right = tree;

    fix_height(tree);
    fix_height(t);

    return t;
}

abl_node_t *rotate_left(abl_node_t *tree)
{
    abl_node_t *t = tree->right;
    tree->right = t->left;
    t->left = tree;

    fix_height(tree);
    fix_height(t);

    return t;
}

abl_node_t *balance(abl_node_t *tree)
{
    fix_height(tree);
    if(find_balance_for_node(tree) == 2)
    {
        if(find_balance_for_node(tree->right) < 0)
            tree->right = rotate_right(tree->right);

        return rotate_left(tree);
    }

    if(find_balance_for_node(tree) == -2 )
    {
        if(find_balance_for_node(tree->left) > 0)
            tree->left = rotate_left(tree->left);

        return rotate_right(tree);
    }
    return tree;
}

abl_node_t *insert_to_abl_tree(int k, abl_node_t *tree)
{
    if(!tree)
        return create_abl_node(k, 0, NULL, NULL);

    if(k < tree->data)
        tree->left = insert_to_abl_tree(k, tree->left);
    else
        tree->right = insert_to_abl_tree(k, tree->right);

    return balance(tree);
}

abl_node_t *input_abl_tree_from_file(FILE *f)
{
    int data;
    if(fscanf(f, "%d", &data) != 1)
    {
        puts("Empty file");
        return NULL;
    }

    abl_node_t *new_tree = create_abl_node(data, 0, NULL, NULL);

    while(fscanf(f, "%d", &data) == 1)
        new_tree = insert_to_abl_tree(data, new_tree);

    return new_tree;
}

void print_abl_tree(abl_node_t *head, int down, int arrow)
{
    if (head)
    {
        print_abl_tree(head->right, down + 1, 2);
        for (int i = 0; i < down; i++)
        {
            printf("       ");
        }
        if (arrow == 1)
        {
            printf(" ➘ ");
        }
        else if (arrow == 2)
        {
            printf(" ➚ ");
        }
        else if (arrow == 0)
        {
            printf("   ");
        }

        printf(" %d (%d)\n", head->data, find_balance_for_node(head));

        print_abl_tree(head->left, down + 1, 1);
    }
}

abl_node_t *find_for_abl_tree(int *count_cmp, abl_node_t *tree, int data)
{
    while(NULL != tree)
    {
        int rc = data - tree->data;
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
