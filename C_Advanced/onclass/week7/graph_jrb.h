#include <libfdr/jrb.h>
#include <libfdr/dllist.h>

typedef JRB Graph;

extern Graph creatGraph();
extern void addEdge(Graph graph, int v1, int v2);
extern int isAdjacent(Graph graph, int v1, int v2);
extern int getAdjacentVertices(Graph graph, int v, int* output);
extern void dropGraph(Graph *graph);
extern void BFS(Graph graph, int start, int stop, void(*visited_func)(int));
extern void DFS(Graph graph, int start, int stop, void(*visited_func)(int));

