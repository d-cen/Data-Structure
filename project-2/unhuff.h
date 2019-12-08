#ifndef __UN_HUFF
#define __UN_HUFF

void createTree(char *fileName, FILE *fp);
void addChar(FILE *fp, int *count, unsigned char *c, unsigned char *nextc);
TreeNode *recurseTree(char *trav, int *len);

#endif
