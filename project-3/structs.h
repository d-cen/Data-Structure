#ifndef __STRUCTS
#define __STRUCTS

typedef struct Heap_Node
{
	long index;
	long length;
} Node;

typedef struct Adjacent_Node
{
	struct Adjacent_Node *next;
	int target;
	float length;
} AdjNode;

typedef struct Vertex
{
	float xcoord;
	float ycoord;
	AdjNode *head;
} Vertex;

#endif