#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "unhuff.h"

void createTree(char *fileName, FILE *fp)
{
    char *trav = malloc(sizeof(char) * 1024);
    unsigned char c = fgetc(fp);
    unsigned char nextc = fgetc(fp);
    int i = 0;
    int count = 0;
    while(1)
    {
        if (c >> 7 == 0)
        {
            trav[i] = '0';
            trav[i + 1] = '\0';
            i++;
            addChar(fp, &count, &c, &nextc);
        }
        else
        {
            if ((c >> 6) == 2)
            {
                addChar(fp, &count, &c, &nextc);
                addChar(fp, &count, &c, &nextc);
                break;
            }
            addChar(fp, &count, &c, &nextc);
            addChar(fp, &count, &c, &nextc);
            c = c | (nextc >> (8 - count));
            trav[i] = '1';
            trav[i + 1] = c;
            trav[i + 2] = '\0';
            i++;
            i++;
            c = nextc << count;
            nextc = fgetc(fp);
            c = c + (nextc >> (8 - count));
        }
    }
    int len = 0;
    TreeNode *head = recurseTree(trav, &len);
    TreeNode *curNode = head;
    strncat(fileName, ".unhuff", 7);
    FILE *outfp = fopen(fileName, "w+");
    if ((c >> 7) != 0)
    {
        addChar(fp, &count, &c, &nextc);
    }
    else
    {
        return;
    }
    while (1)
    {
        if ((curNode -> right == NULL) && (curNode -> left == NULL))
        {
            fprintf(outfp, "%c", curNode -> letter);
            curNode = head;
            if ((c >> 7) != 0)
            {
                addChar(fp, &count, &c, &nextc);
            }
            else
            {
                break;
            }
        }
        if ((c >> 7) == 0)
        {
            curNode = curNode -> left;
        }
        else
        {
            curNode = curNode -> right;
        }
        addChar(fp, &count, &c, &nextc);
    }
    fclose(outfp);
}

void addChar(FILE *fp, int *count, unsigned char *c, unsigned char *nextc)
{
    *count += 1;
    if (*count != 8)
    {
        *c = (*c) << 1;
    }
    else
    {
        *count = 0;
        *c = *nextc;
        *nextc = fgetc(fp);
    }
}

TreeNode *recurseTree(char *trav, int *len)
{
    if (trav[*len] == '1')
    {
        *len += 1;
        TreeNode *endNode = malloc(sizeof(TreeNode));
        endNode -> letter = trav[*len];
        endNode -> left = NULL;
        endNode -> right = NULL;
        return endNode;
    }
    else if (trav[*len] == '0')
    {
        *len += 1;
        TreeNode *left = recurseTree(trav, len);
        *len += 1;
        TreeNode *right = recurseTree(trav, len);
        TreeNode *root = malloc(sizeof(TreeNode));
        root -> left = left;
        root -> right = right;
        return root;
    }
    else
    {
        return NULL;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Wrong arguments.\n");
        return EXIT_FAILURE;
    }
    FILE *fp = fopen(argv[1], "r");
    createTree(argv[1], fp);
    fclose(fp);
    return EXIT_SUCCESS;
}
