#include <stdio.h>
#include <stdlib.h>
#include "graph_array.h"


// Tao do thi.........................................................
Graph creatGraph(int sizemax)
{
  Graph g;
  g.sizemax = sizemax;
  g.matrix = (int **)malloc(sizemax*sizeof(int*));
  int i,j;
  for(i = 0; i < sizemax; i++)
    {
      g.matrix[i]=(int*)malloc(sizeof(int*)*sizemax);
      for(j = 0; j < sizemax; j++)
	g.matrix[i][j] = 0;
    }
  return g;
}

// tao canh  v1-v2 ...................................................
void setEdge(Graph g, int v1, int v2)
{
  g.matrix[v1][v2] = 1;
  g.matrix[v2][v1] = 1;
}

// ktra co canh giua v1-v2 kh..........................................
int isAdjacent(Graph g, int v1, int v2)
{
  return g.matrix[v1][v2];
}

// lay so dinh ke............. .........................................
int getAdjacentVertices(Graph g, int v, int* output)
{
  int counter = 0;
  int i;
  for(i = 0; i < g.sizemax; i++)
    if(g.matrix[v][i] == 1)
      output[counter++] = i;

  return counter;
}

// Xoa do thi
void dropGraph(Graph *g)
{
  int i;
     for( i = 0; i < g->sizemax; i++)
       {
	 free((g->matrix)[i]);
	 (g->matrix)[i] = NULL;
       }

     free(g->matrix);
     (g->matrix) = NULL;
}
