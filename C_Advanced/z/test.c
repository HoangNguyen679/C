#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void print_node(Graph, int);
void print_adjacent_vertices(Graph, int);

int main()
{
  int i, n , output[100];
  Graph g = createGraph();
  
  
  addVertex(g, 0, "C");
  addVertex(g, 1, "G");
  addVertex(g, 2, "B");
  addVertex(g, 3, "A");
  addVertex(g, 4, "D");
  addVertex(g, 5, "E");
  addVertex(g, 6, "F");
  addVertex(g, 7, "H");
  
  addEdge(g, 0, 2, 1);
  addEdge(g, 0, 3, 1);
  addEdge(g, 0, 1, 1);
  addEdge(g, 0, 6, 1);
  addEdge(g, 2, 5, 1);
  addEdge(g, 3, 4, 1);
  addEdge(g, 3, 5, 1);
  addEdge(g, 4, 5, 1);
  addEdge(g, 4, 6, 1);
  addEdge(g, 5, 6, 1);
  addEdge(g, 6, 7, 1);

  //  print_adjacent_vertices(g,0);
  // print_adjacent_vertices(g,1);
  // print_adjacent_vertices(g,2);
  //print_adjacent_vertices(g,3);
  // print_adjacent_vertices(g,4);
  //print_adjacent_vertices(g,5);

  int path[100];
  double len[100]={};
for(i = 0; i < 100; i++) path[i] = -2;
 double out_val = shortest_path(g, 0, 7, path, len);
  if (out_val == INFINITY)
    {
      printf("Not found path !!\n");
    }
  else
    {
      printf("%.2f !!!\n", out_val);
      for (i = 0; i < 9; ++i)
	{
	  printf("%d  %.2f    %d\n", i, len[i], path[i]);
	}
      
    }
  
  printf("\n\tTest traversal BFS: ");
  
  BFS(g, 2, -1, print_node);
  
  printf("\n\tTest traversal DFS: ");

  DFS(g, 2, -1, print_node);

  printf("\n%s\n", "Check TSort");
   TSort(g, print_node);
  
  printf("\n");

  printf("%s\n", "Check cycle");
  // if (is_cyclic(g))
  if(!DAG(g))
    {
      printf("%s\n", "graph has cycle");
    }
  else
    {
      printf("%s\n", "graph has no cycle");
    }
  
  printf("\n\nTest drop !\n");

  dropGraph(g);

  return 0;
}


void print_node(Graph g, int i)
{
     printf("\t\t%s", getVertex(g, i));
}

void print_adjacent_vertices(Graph g,int v)
{
  int i, n, output[100];
  n = outDegree(g, v, output);
  if(n == 0)                                                
    printf("No adjacent vertices of node %d  \n",v);     
  else
    {                                                     
      printf("Adjacent vertices of node %d : ",v);          
      for(i = 0; i < n; i++)                               
	printf("%5d", output[i]);                       
      printf("\n");                                        
    }
}
