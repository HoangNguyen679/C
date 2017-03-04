#include "lib/libfdr/jrb.h"
#include "lib/libfdr/dllist.h"

typedef JRB Graph;

/**
 * Create a new Graph
 * @param: void
 * @return: Graph G
 */
extern Graph create();

/**
 * Add edge v1-v2 to graph G
 * @params: Graph G, vertices v1, v2
 * @return: void
 */
extern void addEdge(Graph G, int v1, int v2);

/**
 * Check if vertices v1, v2 are adjacent
 * @params: Graph G, vertices v1, v2
 * @return: 1 if adjacent, 0 if not
 */
extern int isAdjacent(Graph G, int v1, int v2);

/**
 * Get adjacent vertices of vertex v
 * @params: Graph G, vertex v, array to store output
 * @return: number of adjacent vertices found
 */
extern int getAdjacentNodes(Graph G, int v, int *output);

/**
 * Drop (free) graph G
 * @param: Graph G
 * @return: void
 */
extern void drop(Graph *ptr_G);

/**
 * Get number of nodes of graph G
 * @param: Graph G
 * @return: int number of nodes
 */
extern int getNumNode(Graph G);

/**
 * Get number of edges of graph G
 * @param: Graph G
 * @return: int number of edges
 */
extern int getNumEdge(Graph G);

/**
 * Breadth-first traverse
 * @param: Graph G, index of starting node, ending node, report function
 * @return: void
 */
extern void BFT(Graph G, int start, int stop, void (*visit)(Dllist));

/**
 * Depth-first traverse
 * @param: Graph G, index of starting node, ending node, report function
 * @return: void
 */
extern void DFT(Graph G, int start, int stop, void (*visit)(Dllist));

/**
 * Print the graph
 * @param: graph G
 * @return: void
 */
extern void showGraph(Graph G);

//-------------------------------------------------------------------------

/**
 * Add edge with weight
 * @param: graph G, vertices v1, v2, weight w
 * @return: void
 */
extern void addEdge2(Graph G, int v1, int v2, double w);

/**
 * Get weight of edge v1-v2
 * @param: graph G, vertices v1, v2
 * @return: weight w, INFINITE_VALUE if no edge
 */
extern double getWeight(Graph G, int v1, int v2);