# ECE 36800 Project 3: Map Routing

## Description
In this project, you will implement Dijkstra’s shortest path algorithm for weighted undirected graphs. Variants/enhancements of this algorithm are widely used in geographic information systems including MapQuest and GPS-based car navigation systems.

## Implementation

### Input
You will be given two input files. The first input file will represent a map, which is an undirected graph whose vertices are points on a plane and are connected by edges whose weights are Euclidean distances. Think of the vertices as cities and the edges as roads connected to them. To represent such a map in a file, we list the number of vertices and edges on the first line, then list all the vertices (index followed by its x and y coordinates), and then list all the edges (pairs of vertices).

The second input file contains a list of search queries with the first line containing the number of such queries (this is just to make your job of reading the file easier) and each of the following lines containing one query in the form of a source vertex and destination vertex pair. For example, the query input that is listed below contains two queries, one from node 0 to node 5, and the other from node 4 to node 3.

### Goal
Given a map file and a query file as inputs, your goal is to compute the shortest path from each source listed in the query file to the corresponding destination using Dijkstra’s algorithm. Your program takes the name of the map file and the name of the query file. Given these files, your program should then compute the shortest path for each query in the query file. 

For example, given the files map6.txt and query2.txt, we expect your program (shortestpath) to produce the following output:
```
$ ./shortestpath map6.txt query2.txt
6273
0  1  2  5
5245
4  5  3
INF
6 7
```

In this example, your program prints out four lines, where:
<pre>
Line 1 and 2 contain result for the 1st query in the input file query2.txt
	Line 1: the shortest distance from node 0 to node 5, which is 6273
	Line 2: all nodes on the shortest path from node 0 to node 5, delimited by a space character
Line 3 and 4 contain result for the 2nd query in the input file query2.txt
	Line 3: the shortest distance from node 4 to node 3, which is 5245
	Line 4: all nodes on the shortest path from node 4 to node 3, delimited by a space character
Line 5 and 6 contain result for the 3rd query in the input file query2.txt
	Line 5 & 6: node 6 and 7 are disconnected and their distance is infinity.
</pre>

## Testing
Test your shortestpath.c by compiling them with the following command:
```
gcc -Werror -Wall shortestpath.c -o shortestpath
```
