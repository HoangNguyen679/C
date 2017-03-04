#include"w_graph.h"
void main() {
  FILE *f;
  char place1[100], place2[100];
  int output[MAX_SIZE], n, i;
  double len;
  int select=1;
  graph g=createGraph();
  f=fopen("map.txt", "r");
  while(!feof(f)) {
    fscanf(f, "%s %s %lf\n", place1, place2, &len);
    addVertex(g, newKey(g, place1), place1);
    addVertex(g, newKey(g, place2), place2);
    addEdge(g, getVertexKey(g, place1), getVertexKey(g, place2), len);
  }
  while (select!=2) {
    printf("Menu:\n");
    printf("1. Find the shortest path\n");
    printf("2. Quit\n");
    printf("Select:");
    scanf("%d", &select);
    switch (select) {
    case 1:
      printf("Enter 2 places:");
      scanf("%s %s", place1, place2);
      printf("From %s to %s: ", place1, place2);
      len=single_pair(g, getVertexKey(g, place1), getVertexKey(g, place2), output, &n);
      for (i=0; i<n; i++)
	printf("%s ", getVertex(g, output[i]));
      printf("\nTotal distance: %d km\n", (int)len);
      break;  
    }
  }
}
