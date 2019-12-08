#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "structs.h"
#include "shortestpath.h"

Node * createNode(long index, long length)
{
	Node *node = malloc(sizeof(Node *));
	node -> index = index;
	node -> length = length;
	return node;
}

AdjNode * createEdge(int index, long distance)
{
	AdjNode *node = malloc(sizeof(AdjNode));
	node -> length = distance;
	node -> target = index;
	node -> next = NULL;
	return node;
}

void fillEdge(Vertex *map, int index1, int index2)
{
	long distance = sqrt(pow(map[index2].xcoord - map[index1].xcoord, 2) + pow(map[index2].ycoord - map[index1].ycoord, 2));
    AdjNode *node = createEdge(index2, distance);

    if (map[index1].head == NULL)
    {
    	map[index1].head = node;
    }
    else if (map[index1].head -> next == NULL)
    {
    	if ((map[index1].head -> target) >= index2)
    	{
    		node -> next = map[index1].head;
    	}
    	else
    	{
    		map[index1].head -> next = node;
    	}
    }
    else if ((map[index1].head -> target) > (node -> target))
    {
    	node -> next = map[index1].head;
    	map[index1].head = node;
    }
    else
    {
    	AdjNode *head = map[index1].head;
    	while (head -> next != NULL)
    	{
    		AdjNode *tmp = head -> next;
    		if ((node -> target) < (tmp -> target))
    		{
    			break;
    		}
       		head = head -> next;
    	}
    	if (head -> next == NULL)
    	{
    		head -> next = node;
    	}
    	else
    	{
    		node -> next = head -> next;
    		head -> next = node;
    	}
    }
}

long fillMap(Vertex *map, char *fileName)
{
	int i, verticeNum, edgeNum, index, index1, index2;

	FILE *fp = fopen(fileName, "r");
	fscanf(fp, "%d %d", &verticeNum, &edgeNum);

	for (i = 0; i < verticeNum; i++)
	{
		fscanf(fp, "%d %f %f", &index, &map[i].xcoord, &map[i].ycoord);
	}
	for (i = 0; i < edgeNum; i++)
	{
		fscanf(fp, "%d %d", &index1, &index2);
		fillEdge(map, index1, index2);
		fillEdge(map, index2, index2);
	}
	fclose(fp);
	return verticeNum;
}

void updateIndex(Node ** node, long * position, long index, long length)
{
	node[index] -> length = length;
	long flag = node[index] -> length < node[(index - 1) / 2] -> length;
	while(flag && index > 0)
	{
		position[node[index] -> index] = (index - 1) / 2;
		position[node[(index - 1) / 2] -> index] = index;
		swap(&node[index], &node[(index - 1) / 2]);
		index = (index - 1) / 2;
		flag = node[index] -> length < node[(index - 1) / 2] -> length;
	}
}

void Dijkstra(Vertex *map, long src, long dest, long verticeNum)
{
	long i, num;
	num = verticeNum;
	Node ** node = malloc(MAP_SIZE * sizeof(Node *));
	long *position = malloc(MAP_SIZE * sizeof(long));

	for (i = 0; i < verticeNum; i++)
	{
		if (i != src)
		{
			node[i] = createNode(i, INFINITE);
		}
	}
	int *size = malloc(verticeNum * sizeof(int));
	long *path = malloc(verticeNum * sizeof(long));
	for (i = 0; i < verticeNum; i++)
	{
		position[i] = i;
		path[i] = -1;
		if (i == src)
		{
			size[i] = 0;
		}
		else
		{
			size[i] = INFINITE;
		}
	}
	node[src] = createNode(src, 0);
	updateIndex(node, position, position[src], 0);
	while(size[dest] == INFINITE && num > 0)
	{
		Node *heapNode = extractMin(node, &num, position);
		AdjNode *head = map[heapNode->index].head;
		while (head != NULL)
		{
			long flag1 = (head -> length + size[heapNode -> index]) < size[head -> target];
			long flag2 = position[head -> target] < num;
			long flag3 = size[heapNode -> index] != INFINITE;
			if (flag1 && flag2 && flag3)
			{
				size[head -> target] = size[heapNode -> index] + head -> length;
				path[head -> target] = heapNode -> index;
				updateIndex(node, position, position[head -> target], size[head -> target]);
			}
			head = head -> next;
		}
	}
	long * printPath = malloc(verticeNum * sizeof(long));
	i = 0;
	printf("%ld\n", (long int)size[dest]);
	free(size);
	while (dest >= 0)
	{
		printPath[i++] = dest;
		dest = path[dest];
	}
	while (i > 0)
	{
		i -= 1;
		printf("%ld ", printPath[i]);
	}
	printf("\n");
	free(printPath);
	free(path);
}

void findShortestPaths(Vertex *map, long verticeNum, char * fileName)
{
	FILE *fp = fopen(fileName, "r");
	long src, dest, queryNum, i;
	fscanf(fp, "%ld", &queryNum);
	for (i = 0; i< queryNum; i++)
	{
		fscanf(fp, "%ld %ld", &src, &dest);
		Dijkstra(map, src, dest, verticeNum);
	}
}

void destroyMap(AdjNode *head)
{
	AdjNode *tmp = head;
	while(head != NULL)
	{
		tmp = head;
		head = head -> next;
		free(tmp);
	}
}

int main(int argc, char ** argv)
{
	if (argc != 3)
	{
		printf("Invalid number of arguments\n");
		return EXIT_FAILURE;
	}

	// Initialize the map
	Vertex map[MAP_SIZE];
	int i;
	for (i = 0; i < MAP_SIZE; i++)
	{
		map[i].xcoord = -1;
		map[i].ycoord = -1;
		map[i].head = NULL;
	}

	// Create the map
	long verticeNum = fillMap(map, argv[1]);

	// Find shortest path for each query
	findShortestPaths(map, verticeNum, argv[2]);

	// Destroy map
	for (i = 0; i < verticeNum; i++)
	{
		destroyMap(map[i].head);
	}

	return EXIT_SUCCESS;
}