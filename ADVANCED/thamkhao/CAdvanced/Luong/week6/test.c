#include "adjgraph.h"




void isadj(Graph g, int a, int b)
{
	printf("%d - %d: ", a, b);
	if(adjacent(g, ji(a), ji(b), &cmpInt))
		printf("true\n");
	else
		printf("false\n");
}


int main()
{
	Graph g = createGraph();
	int num, i;
	int adjlist[100] = {0};

	addEdge(g, ji(1), ji(2), &cmpInt);
	addEdge(g, ji(1), ji(3), &cmpInt);
	addEdge(g, ji(2), ji(1), &cmpInt);
	addEdge(g, ji(2), ji(3), &cmpInt);
	addEdge(g, ji(1), ji(4), &cmpInt);
	addEdge(g, ji(2), ji(4), &cmpInt);
	addEdge(g, ji(3), ji(4), &cmpInt);

	isadj(g, 1, 2);
	isadj(g, 2, 1);
	isadj(g, 3, 1);
	isadj(g, 2, 3);
	isadj(g, 3, 4);

	num = getAdjVerticesI(g, ji(4), adjlist, &cmpInt);
	if(num == 0){
		printf("Num == 0\n");
	}else{
		printf("Adjlist of %d is: ", 4);
		for(i = 0; i < num; i++){
			printf("%d, ", adjlist[i]);
		}
	}

	return 0;
}