typedef struct {
  int **matrix;
  int sizemax;
} Graph;

extern Graph creatGraph(int sizemax);
extern void setEdge(Graph graph, int v1, int v2);
extern int isAdjacent(Graph graph, int v1, int v2);
extern int getAdjacentVertices(Graph graph, int v, int* output);
extern void dropGraph(Graph *graph);

