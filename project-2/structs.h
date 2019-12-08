#ifndef __STRUCTS
#define __STRUCTS

typedef struct Binary_Tree
{
    struct Tree_Node *root;
}Tree;

typedef struct Tree_Node
{
    int letter;
    int freq;
    struct Tree_Node *left;
    struct Tree_Node *right;
}TreeNode;

typedef struct List_Node
{
    struct Binary_Tree *tptr;
    struct List_Node *next;
}ListNode;

typedef struct List
{
    struct List_Node * head;
}LinkedList;

#endif
