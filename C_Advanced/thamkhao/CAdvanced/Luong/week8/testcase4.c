#include "digraph.h"

int main()
{
	Graph g = createGraph();

	addVertex(g, 1, "a");
	addVertex(g, 2, "b");
	addVertex(g, 3, "c");
	addVertex(g, 4, "d");
	addVertex(g, 5, "e");
	addVertex(g, 6, "z");

	insertEdge(g, 1, 2, 4);
	insertEdge(g, 1, 3, 2);
	insertEdge(g, 3, 2, 1);
	insertEdge(g, 2, 4, 5);
	insertEdge(g, 3, 4, 8);
	insertEdge(g, 3, 5, 10);
	insertEdge(g, 4, 5, 2);
	insertEdge(g, 4, 6, 6);
	insertEdge(g, 5, 6, 3);

	int s = 1, t = 6, length, path[1000], i;
	double weight = shortestPath(g, s, t, path, &length);

	if (weight == DBL_MAX)
		printf("No path between %d and %d\n", s, t);
	else {
		printf("Path between %d and %d:", s, t);
		for (i=0; i<length; i++) printf("%4d", path[i]);
		printf("\nTotal weight: %lf\n", weight);
	}

}