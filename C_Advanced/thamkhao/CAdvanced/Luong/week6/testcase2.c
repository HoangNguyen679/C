#include "adjgraph.h"

int main()
{
	Graph g = createGraph();
	int i, num;
	int adjlist[100]={0};

	addEdgeI(g, 1, 2);
	addEdgeI(g, 1, 3);
	addEdgeI(g, 1, 4);
	addEdgeI(g, 2, 1);
	addEdgeI(g, 2, 3);
	addEdgeI(g, 2, 4);
	addEdgeI(g, 3, 4);
	addEdgeI(g, 2, 1);
	addEdgeI(g, 3, 1);

	if(adjacentI(g, 4, 3))
		printf("4 and 3 is adjacent: true\n");
	else
		printf("4 and 3 is adjacent: false\n");

	num = getAdjVerticesI(g, ji(4), adjlist, &cmpInt);
	if(num == 0){
		printf("Num == 0\n");
	}else{
		printf("Adjlist of %d is: ", 4);
		for(i = 0; i < num; i++){
			printf("%d, ", adjlist[i]);
		}
	}
}