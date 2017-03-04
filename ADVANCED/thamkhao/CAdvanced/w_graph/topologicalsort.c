#include<stdio.h>
#include<stdlib.h>
#include"w_graph.h"
void main() {
  FILE *f;
  char s1[100], s2[100];
  int x1, x2, n, i;
  int output[100];
  graph g=createGraph();
  f=fopen("class.txt", "r");
  while (!feof(f)) {
    fscanf(f, "%d %s %d %s\n", &x1, s1, &x2, s2);
    addVertex(g, x1, s1);
    addVertex(g, x2, s2);
    addVector(g, x2, x1, 100);
    }
  close(f);
  topologicalsort(g, output, &n);
  for (i=0; i<n; i++) 
    printf("%s ", getVertex(g, output[i]));
    printf("\n");
}
