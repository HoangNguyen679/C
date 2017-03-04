#include <stdio.h>
#include <string.h>
#include "jval.h"
#include "jrb.h"

#define ji(i) (new_jval_i(i))

typedef JRB Graph;

Graph createGraph(); // create an empty rb tree

int addEdge(Graph, Jval, Jval,
			int (*cmp)(Jval, Jval)); // add an edge to the graph

int adjacent(Graph, Jval, Jval,
				int (*cmp)(Jval, Jval)); // check if two vertices are adjacent

JRB getAdjVertices(Graph, Jval,
						int (*cmp)(Jval, Jval)); // get adjacent vertices

int cmpInt(Jval, Jval);  // function to compare two integers

int cmpStr(Jval, Jval); // function to compare two strings


/********************
* API FOR INT DATA
********************/

int getAdjVerticesI(Graph, Jval, int*,
						int (*cmp)(Jval, Jval));

int addEdgeI(Graph, int, int); // used for graph with int vertices

int adjacentI(Graph, int, int);