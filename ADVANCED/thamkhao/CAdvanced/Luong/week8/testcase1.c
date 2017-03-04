#include "digraph.h"

int main()
{
	Graph g = createGraph();
	int num, i;
	int output[20];

	insertEdge(g, 1, 2, 1);
	insertEdge(g, 2, 3, 1);
	insertEdge(g, 1, 4, 1);
	insertEdge(g, 4, 3, 1);
	insertEdge(g, 4, 5, 1);
	insertEdge(g, 5, 3, 1);

	addVertex(g, 1, "v1");
	addVertex(g, 2, "v2");
	addVertex(g, 3, "v3");
	addVertex(g, 4, "v4");
	addVertex(g, 5, "v5");

	num = inDegree(g, 3, output);
	printf("inDegree num = %d\n", num);
	for(i = 0; i < num; i++)
		printf("%-5d", output[i]);
	printf("\n");

	num = outDegree(g, 4, output);
	printf("outDegree num = %d\n", num);
	for(i = 0; i < num; i++)
		printf("%-5d", output[i]);
	printf("\n");

	printf("name of vertex 5: %s\n", getVertex(g, 5));

	if(hasEdge(g, 1, 2)){
		printf("true\n");
	}

	printf("tsort:\n");
	tsort(g);

	printf("check getWeight\n");
	printf("Weight of the edge (v1, v2) is %.2lf\n", getWeight(g, 1, 2));
	printf("Weight of the edge (v1, unknown) is %.2lf\n", getWeight(g, 1, 9));

	printf("check BFS\n");
	BFS(g, 1, visit);

	printf("check DFS\n");
	DFS(g, 1, visit);

	dropGraph(g);

	return 0;
}