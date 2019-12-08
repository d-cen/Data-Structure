#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "huff.h"

LinkedList *initList(FILE *fp)
{
    int freqArray[256] = {0};
    char letter = fgetc(fp);
    while (letter != EOF)
    {
        freqArray[(int)letter]++;
        letter = fgetc(fp);
    }
    LinkedList *list = malloc(sizeof(LinkedList));
    list -> head = NULL;
    int i;
    for (i = 0; i < 256; i++)
    {
        if (freqArray[i] > 0)
        {
            TreeNode *tnode = malloc(sizeof(TreeNode));
            tnode -> letter = i;
            tnode -> freq = freqArray[i];
            tnode -> left = NULL;
            tnode -> right = NULL;
            Tree *tree = malloc(sizeof(Tree));
            tree -> root = tnode;
            ListNode *node = malloc(sizeof(ListNode));
            node -> tptr = tree;
            node -> next = NULL;
            insertList(list, node);
        }
    }
    return list;
}

void insertList(LinkedList *list, ListNode *node)
{
    ListNode *head = list -> head;
    if (head == NULL || (head -> tptr -> root -> freq) > (node -> tptr -> root -> freq))
    {
        list -> head = node;
        node -> next = head;
    }
    else
    {
        while (head != NULL)
        {
            if (head -> next == NULL || (head -> next -> tptr -> root -> freq) > (node -> tptr -> root -> freq))
            {
                node -> next = head -> next;
                head -> next = node;
                break;
            }
            head = head -> next;
        }
    }
}

void deleteList(LinkedList *list, ListNode *node)
{
    list -> head = node -> next;
}

Tree *buildTree(LinkedList *list)
{
    ListNode *curNode = list -> head;
    while (list -> head -> next != NULL)
    {
        ListNode *newNode = combineTree(curNode);
        deleteList(list, curNode);
        deleteList(list, curNode -> next);
        insertList(list, newNode);
        curNode = list -> head;
    }
    return curNode -> tptr;
}

ListNode *combineTree(ListNode *node)
{
    Tree *leftTree = node -> tptr;
    Tree *rightTree = node -> next -> tptr;
    TreeNode *newNode = malloc(sizeof(TreeNode));
    newNode -> letter = -1;
    newNode -> freq = (leftTree -> root -> freq) + (rightTree -> root -> freq);
    newNode -> left = leftTree -> root;
    newNode -> right = rightTree -> root;
    Tree *newTree = malloc(sizeof(Tree));
    newTree -> root = newNode;
    ListNode *listNode = malloc(sizeof(ListNode));
    listNode -> tptr = newTree;
    listNode -> next = NULL;
    return listNode;
}

void treeEncoder(TreeNode *node, char **arr, char *trav, char *tempArr, FILE *fp)
{
    int index = strlen(trav);
    if ((node -> left == NULL) && (node -> right == NULL))
    {
        int num = node -> letter;
        arr[num] = malloc(sizeof(char) * 15);
        strcpy(arr[num], tempArr);
        trav[index] = '1';
        trav[index + 1] = '1';
        trav[index + 2] = num;
        trav[index + 3] = '\0';
        return;
    }
    trav[index] = '0';
    trav[index + 1] = '\0';
    int len = strlen(tempArr);
    if (node -> left != NULL)
    {
        tempArr[len] = '0';
        tempArr[len + 1] = '\0';
        treeEncoder(node -> left, arr, trav, tempArr, fp);
    }
    if (node -> right != NULL)
    {
        tempArr[len] = '1';
        tempArr[len + 1] = '\0';
        treeEncoder(node -> right, arr, trav, tempArr, fp);
    }
}

void writeBits(FILE *fp, char *preorder, int *position, unsigned char *bit, int flag)
{
    int k = strlen(preorder);
    int cmp[2] = {0};
    int i;
    for (i = 0; i < k; i++)
    {
        char data = preorder[i];
        if(flag && (!cmp[0] || !cmp[1]))
        {
            if (data == '1')
            {
                cmp[1] = cmp[0];
                cmp[0] = 1;
                *bit = *bit | 1;
            }
            else
            {
                cmp[1] = 0;
                cmp[0] = 0;
            }
            (*position)++;
            if (*position == 8)
            {
                *position = 0;
                fwrite(bit, sizeof(char), 1, fp);
            }
            *bit = *bit << 1;
        }
        else if (!flag && (data == '1' || data == '0'))
        {
            if (data == '1')
            {
                cmp[1] = cmp[0];
                cmp[0] = 1;
                *bit = *bit | 1;
            }
            else
            {
                cmp[1] = 0;
                cmp[0] = 0;
            }
            (*position)++;
            if (*position == 8)
            {
                *position = 0;
                fwrite(bit, sizeof(char), 1, fp);
            }
            *bit = *bit << 1;
        }
        else
        {
            cmp[1] = 0;
            cmp[0] = 0;
            *bit = *bit << (7 - *position);
            char toBit = data >> *position;
            *bit = *bit | toBit;
            fwrite(bit, sizeof(char), 1, fp);
            *bit = data << 1;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Please provide input file.\n");
        return EXIT_FAILURE;
    }
    else if (argc > 2)
    {
        printf("Argument exceeded.\n");
        return EXIT_FAILURE;
    }
    FILE *infp = fopen(argv[1], "r");
    if (infp == NULL)
    {
        printf("Input file not found.\n");
        return EXIT_FAILURE;
    }
    LinkedList *list = initList(infp);
    Tree *tree = buildTree(list);
    strncat(argv[1], ".huff", 5);
    FILE *outfp = fopen(argv[1], "w+");
    char **arr = malloc(sizeof(char*) * 256);
    char *trav = malloc(sizeof(char) * 1024);
    char *tempArr = malloc(sizeof(char) * 15);
    trav[0] = '\0';
    tempArr[0] = '\0';
    treeEncoder(tree -> root, arr, trav, tempArr, outfp);
    int position = 0;
    unsigned char bit = 0;
    writeBits(outfp, trav, &position, &bit, 1);
    writeBits(outfp, "10", &position, &bit, 0);
    fseek(infp, 0, SEEK_SET);
    char trig[2];
    trig[0] = fgetc(infp);
    trig[1] = '\0';
    while (trig[0] != EOF)
    {
        writeBits(outfp, "1", &position, &bit, 0);
        writeBits(outfp, arr[(int)trig[0]], &position, &bit, 0);
        trig[0] = fgetc(infp);
    }
    writeBits(outfp, "0", &position, &bit, 0);
    bit = bit << (7 - position);
    fwrite(&bit, sizeof(char), 1, outfp);
    fclose(infp);
    fclose(outfp);
    return EXIT_SUCCESS;    
}
