#include "./lib/libfdr/jrb.h"
#include "./lib/libfdr/dllist.h"

typedef struct
{
	JRB edges;
	JRB vertices;
	int MAX_VERTICES;
} Graph;

/**
 * Create a new Graph
 * @param: void
 * @return: Graph G
 */
extern Graph create();

/**
 * Add new vertex to graph
 * @param: graph pointer, id of node, name of node
 * @return: void
 */
extern void addVertex(Graph *ptr_G, int id, char* name);

/* Get vertex information
 * @param: graph G, id of node
 * @return: name of node
 */
extern char* getVertex(Graph G, int id);

/**
 * Add edge v1->v2 to graph G (not inverse)
 * @params: Graph G, vertices v1, v2
 * @return: 1 if add successfully, 0 if failed
 */
extern int addEdge(Graph G, int v1, int v2);

/**
 * Check if there is a path v1->v2
 * @param: graph G, id of v1 and v2
 * @return: 1 if has edge, 0 if not
 */
extern int hasEdge(Graph G, int v1, int v2);

/**
 * Drop (free) graph G
 * @param: Graph pointer G
 * @return: void
 */
extern void drop(Graph *ptr_G);

/**
 * Breadth-first traverse
 * @param: Graph G, index of starting node, ending node, report function
 * @return: void
 */
extern void BFT(Graph G, int start, int stop, void (*visit)(int));

/**
 * Depth-first traverse
 * @param: Graph G, index of starting node, ending node, report function
 * @return: void
 */
extern void DFT(Graph G, int start, int stop, void (*visit)(int));

/**
 * Get nodes that come into vertex v
 * @param: graph G, vertex v, output array storing nodes
 * @return: number of nodes come into v
 */
extern int indegree(Graph G, int v, int *output);

/**
 * Get nodes that go out of vertex v
 * @param: graph G, vertex v, output array storing nodes
 * @return: number of nodes go out of v
 */
extern int outdegree(Graph G, int v, int *output);

/**
 * Check if graph is directed acycle graph (no cycle)
 * @param: graph G
 * @return: 1 if is DAG (no cycle), 0 if not (has cycle)
 */
extern int isDAG(Graph G);

/**
 * Print all vertices of graph
 * @param: graph G
 * @return: void
 */
extern void showVertices(Graph G);

/**
 * Print all edges of graph
 * @param: graph G
 * @return: void
 */
extern void showEdges(Graph G);

/**
 * Topological sort
 * Print out linear order
 * @param: graph G (no cycle), visit function
 * @return: void
 */
extern void TSort(Graph G, void (*visit)(Graph, int));

/**
 * Get highest id of graph G
 * @param: graph G
 * @return: highest id
 */
extern int getHighestID(Graph G);
