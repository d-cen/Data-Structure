#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "structs.h"

#define MAP_SIZE 100000
#define INFINITE INT_MAX

void swap(Node **node1, Node **node2)
{
	Node *tmp = *node1;
	*node1 = *node2;
	*node2 = tmp;
}

void heapify(Node ** node, long *position, long i, long size)
{
	long root = i;
	long leftChild = 2 * root + 1;
	long rightChild = 2 * root + 2;

	if (leftChild < size && node[leftChild] -> length < node[root] -> length)
	{
		root = leftChild;
	}
	if (rightChild < size && node[rightChild] -> length < node[root] -> length)
	{
		root = rightChild;
	}
	if (root != i)
	{
		position[node[root] -> index] = i;
		position[node[i] -> index] = root;
		swap(&node[root], &node[i]);
		heapify(node, position, root, size);
	}
}

Node * extractMin(Node ** node, long *size, long *position)
{
	if (*size == 0)
	{
		return NULL;
	}
	else
	{
		long num = *size - 1;
		Node * root = node[0];
		Node * prev = node[num];
		node[0] = prev;
		position[root -> index] = num;
		position[prev -> index] = 0;
		*size = num;
		heapify(node, position, 0, *size);
		return root;
	}
}
