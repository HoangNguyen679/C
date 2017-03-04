#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_jrb.h"

#define MAX_SIZE 100
void print_node(int i);
void print_adjacent_of_node(Graph g,int x);

int main()
{
  int i, n, output[MAX_SIZE];
  Graph g = creatGraph();

  addEdge(g, 0, 1);
  addEdge(g, 0, 2);
  addEdge(g, 1, 2);
  addEdge(g, 2, 0);
  addEdge(g, 2, 3);
  addEdge(g, 3, 3);

  print_adjacent_of_node(g,0);
  print_adjacent_of_node(g,1);
  print_adjacent_of_node(g,2);
  print_adjacent_of_node(g,3);
  /*
#define PRINT_ADJACENT_VERTIES(v) {                                 \
    n = getAdjacentVertices(g, v, output);			    \
    if(n == 0)							    \
      printf("No adjacent vertices of node" #v " \n");		    \
    else{							    \
      printf("Adjacent vertices of node "#v": ");		    \
      for(i = 0; i < n; i++)					    \
	printf("%5d", output[i]);				    \
      printf("\n");						    \
    }								    \
  }                                                              

     PRINT_ADJACENT_VERTIES(0);
     PRINT_ADJACENT_VERTIES(1);
     PRINT_ADJACENT_VERTIES(2);
     PRINT_ADJACENT_VERTIES(3);
#undef PRINT_ADJACENT_VERTIES

  */
 printf("\n\tTest traversal BFS: ");
 
     BFS(g, 2, -1, print_node);
     
     printf("\n\tTest traversal DFS: ");
     
     DFS(g, 2, -1, print_node);
     
     
     printf("\n\nTest drop !\n");
     
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


void print_node(int i)
{
     printf("\t\t%d", i);
}

void print_adjacent_of_node(Graph g,int x)
{
  int n1;
  int output1[MAX_SIZE];
  n1 = getAdjacentVertices(g, x, output1);
  if(!n1) printf("No adjacent vertices of node 1!\n");
  else
    {
      printf("Adjacent of node %d is:\n",x);
      int i;
      for(i = 0; i < n1; i++)
	printf("%5d\t",output1[i]);
      printf("\n");
    }
}
