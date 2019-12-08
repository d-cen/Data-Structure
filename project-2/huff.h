#ifndef __HUFF
#define __HUFF

LinkedList *initList(FILE *fp);
void insertList(LinkedList *list, ListNode *node);
void deleteList(LinkedList *list, ListNode *node);
Tree *buildTree(LinkedList *list);
ListNode *combineTree(ListNode *node);
void treeEncoder(TreeNode *node, char **array, char *traversal, char *tempArray, FILE *fp);
void writeBits(FILE *fp, char *preorder, int *position, unsigned char *bit, int trigger);

#endif
