#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.directed.h"

int main()
{
  int a[MAX], n, i, total, path[MAX];
  Graph G = createGraph();
  addVertex(&G, 1, "Thien");
  addVertex(&G, 2, "Then");
  addVertex(&G, 3, "Tien");
  addVertex(&G, 4, "Tien");
  addVertex(&G, 5, "Tien");
  addVertex(&G, 6, "Tien");
  addVertex(&G, 7, "Tien");

  addEdge(G, 1, 2, 1);
  addEdge(G, 2, 1, 1);
  addEdge(G, 5, 6, 9);
  addEdge(G, 1, 4, 20);
  addEdge(G, 1, 3, 1.3);
  addEdge(G, 2, 3, 1.5);
  addEdge(G, 3, 4, 1.5);
  addEdge(G, 7, 1, 1);

  printf("%s\n",getVertex(G,4));
  printf("=>%d\n",G.MAX_VERTICES);

  printVertex(G);
  
  printEdge(G);
  
  printf("vao tu dinh 1:");
  n = outdegree(G, 1, a);
  for(i = 0 ;i< n ;i++ ) printf("%d ",a[i]);
    printf("\n");
  
  printf("ra tu dinh 2:");
  n = indegree(G, 2, a);
  for(i = 0 ;i< n ;i++ ) printf("%d ",a[i]);
    printf("\n%f\n", hasEdge(G, 1,3));
  
  if(DAG(G) == 1) printf("Co chu trinh\n");
  else printf("Khong co chu trinh\n");
  
  printf("BFS: ");
  BFS(G, 1, 6, pVertex);
  printf("\n");
  
  printf("DFS: ");
  DFS(G, 1, -1, pVertex);

  printf("\ntotal connected =>%d\n\n", totalConnected(G, 1, -1));
  
  printf("connected component: %d\n\n", countConnected(G));
  
  int ww = UFS(G, 2, 7, path, &total);
  printf("dinh %d\n", total);
  for( i=0;i<total ; i++ ) printf("%d ",path[i]);
    total = 0;
  if(!UFS(G, 2, 7, path, &total))
  {
    double  w = shortestPath(G, 2, 7, path, &total);
    if(w != INFINITIVE_VALUE){
      printf("Trong luong: %0.0f\n", w);
      for(i=total ;i>=0 ;i-- )
        printf("%d ", path[i]);
    }
  } else printf("Khong co duong di\n");
  printf("\n\n");
  printf("Topo:\n");
  total = topo(G, path);
  for(i=0 ;i<total ;i++ )
    printf("%d ", path[i]);

  return 0;
}
