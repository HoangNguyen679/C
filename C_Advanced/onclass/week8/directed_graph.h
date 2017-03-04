#include <libfdr/jrb.h>
#include <libfdr/dllist.h>
typedef struct {
  JRB edges;
  JRB vertices;
} Graph;

extern graph createGraph();
extern void addVertex(graph graph, int id, char *value);
extern char *getVertex(graph graph, int id);
extern void addEdge(graph g, int v, int v2);
extern int hasEdge(graph g, int v, int v2);
extern int inDegree(graph g, int vertex, int *output);
extern int outDegree(graph g, int vertex, int *output);
extern void dropGraph(graph *g);
extern void BFS(graph g, int start, int stop, void (*visited_func)(graph, int));
extern void DFS(graph g, int start, int stop, void (*visited_func)(graph, int));
extern int get_graph_max_id(graph g);
extern int get_graph_min_id(graph g);
extern int is_cyclic_util(graph g, int start);
extern int isCyclic(graph g);
extern void TSort(graph g, void (*visited_func)(graph, int));
