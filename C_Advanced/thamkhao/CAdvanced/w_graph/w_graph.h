#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
#include"dllist.h"
#define MAX_SIZE 1000
#define INFINITIVE 999999999
typedef struct{
  char *name;
  double *len;
} *vertex_info;
typedef struct{
  JRB edge;
  JRB vertex;
} graph;
graph createGraph();
void addVertex(graph g, int v, char *name);
char *getVertex(graph g, int v);
int getVertexkey(graph g, char *name);
void addVertexLen(graph g, int v, double len);
double getVertexLen(graph g, int v);
void addEdge(graph g, int v1, int v2, double len);
void addVector(graph g, int v1, int v2, double len);
int adjacent(graph g, int v1, int v2);
int isVector(graph g, int v1, int v2);
int getAdjacentVertices(graph g, int v, int *output);
int outDgree(graph g, int v, int *output);
int inDgree(graph g, int v, int *output);
void dropGraph(graph g);
void DFS(graph g, int v1, int v2, void(*func)(int));
void BFS(graph g, int v1, int v2, void(*func)(int));
void graph_traverse(graph g, int v1, int v2, void(*func)(int));
int DAG(graph g);
void topologicalsort(graph g, int *output, int *n); 
double vectorLenght(graph g, int v1, int v2);
double edgeLenght(graph g, int v1, int v2);
double single_pair(graph g, int v1, int v2, int *output, int *n);
int makeNewKey(graph g, char *name);
