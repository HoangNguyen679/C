/*Le Vinh Thien - 8C*/
// Date Create:
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.undirected.h"
#define INPUT "data.txt"

main()
{
  int total, path[MAX], i;
  double w;
  Graph G = createGraph();
  addEdge(G, 1, 2, 1.0);
  addEdge(G, 2, 3, 1);
  addEdge(G, 3, 4, 1);
  addEdge(G, 1, 4, 5);
  addEdge(G, 5, 6, 3);
  printf("DFS: \n");
  DFS(G, 1, -1, printVertex);
  printf("\n");
  printf("BFS: \n");
  BFS(G, 1, -1, printVertex);
  printf("\n");
  printGraph(G);
  printf("\n");
  w = shortestPath(G, 1, 4, path, &total);
  printf("Trong luong: %0.0f\n", w);
  for(i=total ;i>=0 ;i-- )
    printf("%d ", path[i]);
  total = 0;
  printf("\n");
  int ww = UFS(G, 1, 4, path, &total);
  printf("dinh %d\n", total);
  for( i=0;i<total ; i++ ) printf("%d ",path[i]);
  printf("\n");
  if(DFSAII(G) != 0) printf("Co chu trinh\n");
  else printf("Khong co chu trinh\n");
  printf("Co %d lien thong\n", countConnected(G));
  printf("So canh: %d\n", numEdges(G));
  freeGraph(G);
}

