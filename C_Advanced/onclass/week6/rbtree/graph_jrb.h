#include <libfdr/jrb.h>

typedef JRB Graph;

extern Graph creatGraph();
extern void setEdge(Graph graph, int v1, int v2);
extern int isAdjacent(Graph graph, int v1, int v2);
extern int getAdjacentVertices(Graph graph, int v, int* output);
extern void dropGraph(Graph *graph);



