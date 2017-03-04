#include "digraph.h"

int main()
{
	Graph g = createGraph();

	insertEdge(g, 5, 2, 1);
	insertEdge(g, 5, 0, 1);
	insertEdge(g, 4, 0, 1);
	insertEdge(g, 4, 1, 1);
	insertEdge(g, 2, 3, 1);
	insertEdge(g, 3, 1, 1);

	addVertex(g, 0, "v0");
	addVertex(g, 1, "v1");
	addVertex(g, 2, "v2");
	addVertex(g, 3, "v3");
	addVertex(g, 4, "v4");
	addVertex(g, 5, "v5");

	tsort(g);
}