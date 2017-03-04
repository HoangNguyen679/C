#include <stdio.h>
#include <stdlib.h>

#define SIZE_MAX 100

typedef struct
{
  int **matrix;
  int sizemax;
} Graph;

Graph creatGraph(int sizemax);
void setEdge(Graph graph, int v1, int v2);
int isAdjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int v, int* output);
void dropGraph(Graph *graph);

/*  ---    Tao do thi   ---   */

Graph creatGraph(int sizemax)
{
  Graph g;
  g.sizemax = sizemax;
  g.matrix = (int **)malloc(sizemax*sizeof(int*));

  int i,j;
  for(i = 0; i < sizemax; i++) {
    g.matrix[i]=(int*)malloc(sizeof(int*)*sizemax);
    for(j = 0; j < sizemax; j++)
      g.matrix[i][j] = 0;
  }
  
  return g;
}

/*   ---   tao canh   ---   */

void setEdge(Graph g, int v1, int v2)
{
  g.matrix[v1][v2] = 1;
  g.matrix[v2][v1] = 1;
}

/*   ---   ktra canh   ---   */

int isAdjacent(Graph g, int v1, int v2)
{
  return g.matrix[v1][v2];
}

/*   ---   lay so dinh ke   ---   */
int getAdjacentVertices(Graph g, int v, int* output)
{
  int counter = 0;
  int i;
  for(i = 0; i < g.sizemax; i++)
    if(g.matrix[v][i] == 1)
      output[counter++] = i;

  return counter;
}

/*   ---   xoa do thi   ---   */
void dropGraph(Graph *g)
{
  int i;
  for( i = 0; i < g->sizemax; i++)    {
    free((g->matrix)[i]);
    (g->matrix)[i] = NULL;
  }

  free(g->matrix);
  (g->matrix) = NULL;
}



/*   ---  chuong tinh chinh   ---   */

int main(int argc, char * argv[])
{
  argc = argc;
  NULL == argv[argc];

  int n,i;
  int output[SIZE_MAX];

  Graph g = creatGraph(SIZE_MAX);

  setEdge(g,0,1);
  setEdge(g,0,2);
  setEdge(g,1,2);
  setEdge(g,1,3);

  n = getAdjacentVertices(g, 1, output);
  if(!n) printf("No adjacent vertices of node 1!\n");
  else {
    printf("Adjacent of node 1 is:\n");
    for(i = 0; i < n; i++)
      printf("%5d\t",output[i]);
    printf("\n");
  }
  dropGraph(&g);

  return 0;
}
