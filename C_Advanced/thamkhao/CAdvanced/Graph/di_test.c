#include <stdio.h>
#include <stdlib.h>
#include "di_w_graph.h"

void visit(int v){ 
	printf("%3d", v);
}

int main(int argc, char const *argv[])
{
	Graph G = create();

	addVertex(&G, 1, "A");
	addVertex(&G, 2, "B");
	addVertex(&G, 3, "C");
	addVertex(&G, 4, "D");
	addVertex(&G, 5, "E");
	addVertex(&G, 6, "F");
	addVertex(&G, 7, "G");
	addVertex(&G, 8, "H");

	addEdge(G, 1, 4, 1.5);
	addEdge(G, 1, 5, 1.5);
	addEdge(G, 2, 5, 1.5);
	addEdge(G, 3, 1, 2.5);
	addEdge(G, 3, 2, 1.5);
	addEdge(G, 3, 6, 3.5);
	addEdge(G, 3, 7, 1.5);
	addEdge(G, 4, 6, 1.5);
	addEdge(G, 4, 5, 1.5);
	addEdge(G, 5, 6, 1.5);
	addEdge(G, 6, 8, 1.5);

	showVertices(G);
	printf("\n");
	showEdges(G);

	printf("BFT: ");
	BFT(G, 1, -1, visit);
	printf("\n");

	printf("DFT: ");
	DFT(G, 1, -1, visit);
	printf("\n");

	if(isDAG(G) == 0) {
		printf("Has cycle! Cannot make topo sort!\n");
		return 1;
	} 

	TSort(G, visit);
	printf("\n");

	int n = getHighestID(G) + 1;

	int path[100];
	double length[100];
	double w = shortestPath(G, 1, 5, path, length);

	printf("w = %.2lf\n", w);

	int i, j;
	for(i = 0; i < 100; i++)
		if(path[i] == -1) break;

	for(j = i-1; j >=0; j--)
		printf("%3d", path[j]);

	printf("\n");

	drop(&G);

	return 0;
}