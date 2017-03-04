#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ARRSIZE 	10
#define RANGE 		10
#define EPSILON 	1E-7
#define MAX_BUFF 	512

#define INITIAL_SIZE 		10
#define INCREMENTAL_SIZE 	5
#define BUFF_SIZE			80

#define NEWLINE 	printf("%s", "\n");

typedef struct 
{
	int *matrix;
	int sizemax;
} Graph;

Graph CreateGraph(int sizemax);
int CheckValidVertex(Graph G, int v);
void AddEdge(Graph G, int v1, int v2);
int IsAdjacent(Graph G, int v1, int v2);
int GetAdjacentVerticle(Graph G, int v, int *output);
void DropGraph(Graph G);


int main(int argc, char const *argv[])
{
	Graph myGraph;
	myGraph = CreateGraph(INITIAL_SIZE);
	if (myGraph.sizemax == 0)
	{
		printf("%s\n", "Failed to Create Graph!");
		return 1;
	}

	AddEdge(myGraph, 0 ,1);
	AddEdge(myGraph, 1 ,3);
	AddEdge(myGraph, 2 ,5);
	AddEdge(myGraph, 2 ,6);
	AddEdge(myGraph, 2 ,9);
	AddEdge(myGraph, 4 ,9);

	int output[myGraph.sizemax];
	int n = GetAdjacentVerticle(myGraph, 2, output);

	if (n == 0) 
		printf("No adjacent vertices\n");
	else 
	{
		printf("Number of adjacent: %d\n", n);
		printf("Adjacent vertices:");
		int i;
		for (i=0; i< n; i++) printf("%5d", output[i]);
	}
	printf("%s\n", "");
	DropGraph(myGraph);
	return 0;
}


//---------------------------------------------------------
Graph CreateGraph(int sizemax)
{
	int *A = (int*)malloc(sizeof(int)*sizemax*sizemax);
	Graph G;
	G.matrix = A;
	if (A == NULL)
	{
		printf("%s\n", "Alloc Memory Failed!");
		G.sizemax = 0;
	}
	else
	{
		G.sizemax = sizemax;
	}
	return G;
}
//---------------------------------------------------------
int CheckValidVertex(Graph G, int v)
{
	if (v < 0 || v >= G.sizemax)
	{
		printf("%s\n", "Invalid Vertex!");
		return 0;
	}
	return 1;
}
//---------------------------------------------------------
void AddEdge(Graph G, int v1, int v2)
{
	if (!CheckValidVertex(G, v1) || !CheckValidVertex(G, v2))
	{
		return;
	}
	G.matrix[v1*G.sizemax+v2] = 1;
	G.matrix[v2*G.sizemax+v1] = 1;
	return;
}
//---------------------------------------------------------
int IsAdjacent(Graph G, int v1, int v2)
{
	if (!CheckValidVertex(G, v1) || !CheckValidVertex(G, v2))
	{
		return 0;
	}
	return G.matrix[v1*G.sizemax+v2];
}
//---------------------------------------------------------
int GetAdjacentVerticle(Graph G, int v, int *output)
{
	if (!CheckValidVertex(G, v))
	{
		return 0;
	}
	int i = 0, j = 0;
	int count = 0;
	for(i = 0; i < G.sizemax; i++)
	{
		if (G.matrix[v*G.sizemax+i] == 1)
		{
			count++;
			output[j++] = i;
		}
		else
		{
			//output[i] = 0;
		}
	}
	return count;
}
//---------------------------------------------------------
void DropGraph(Graph G)
{
	free(G.matrix);
	G.matrix = NULL;
	G.sizemax = 0;
}