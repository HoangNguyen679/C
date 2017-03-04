#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_jrb.h"
#define SIZE_MAX 100

int main(int argc, char *argv[])
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
  else
    {
      printf("Adjacent of node 1 is:\n");
      for(i = 0; i < n; i++)
	printf("%5d\t",output[i]);
      printf("\n");
    }
  dropGraph(&g);

  n = getAdjacentVertices(g, 1, output);
 
     if(n == 0)
          printf("No adjacent vertices of node 1 \n");
     else{
          printf("Adjacent vertices of node 1: ");
          for(i = 0; i < n; i++)
               printf("%5d", output[i]);
     }
     printf("\n");
return 0;
}


