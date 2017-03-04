#include "digraph.h"

int main()
{
	Graph g = createGraph();
	addVertex(g, 102, "CS102");
	addVertex(g, 140, "CS140");
	insertEdge(g, 102, 140);
	addVertex(g, 160, "CS160");
	insertEdge(g, 102, 160);
	addVertex(g, 302, "CS302");
	insertEdge(g, 140, 302);
	addVertex(g, 311, "CS311");
	addVertex(g, 300, "MATH300");
	insertEdge(g, 300, 311);
	insertEdge(g, 302, 311);

	tsort(g);
}