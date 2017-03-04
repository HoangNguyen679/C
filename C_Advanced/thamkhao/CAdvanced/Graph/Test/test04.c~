#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../di_graph.h"

#define MAX 80

Graph buildGraphFrom(FILE *file);
int getNumEdges(Graph G);

int main(int argc, char* argv[]){
  if(argc != 2) {
    printf("Please specify source file!\n");
    exit(1);
  }

  char file_name[MAX];
  FILE *file;

  strcpy(file_name, argv[1]);
  file = fopen(file_name, "r");
  if(file == NULL) {
    printf("Cannot open file \"%s\"!\n", file_name);
    exit(1);
  }

  Graph G = buildGraphFrom(file);

  printf("Tong so mon hoc: %d\n", G.MAX_VERTICES);
  printf("Tong so cung: %d\n", getNumEdge(G));

  if(isDAG(G)) printf("Do thi khong co cycle!\n");
  else {
    printf("Do thi co cycle!\n");
    exit(1);
  }

  int choice = 1;

  do {
    char s[MAX];
    JRB node;
    int exist = 0;
    int u;

    printf("Nhap ma so mon hoc: ");
    scanf("%s", s);

    jrb_traverse(node, G.vertices) {
      if(strcmp(jval_s(node->val), s) == 0){
        exist = 1;
        u = jval_i(node->key);
      }
    }

    if(exist) {
      int n = getHighestID(G) + 1;
      int *out = (int*)malloc(sizeof(int) * n);
      int k;

      k = indegree(G, u, out);
      printf("So mon hoc phai hoc truoc la: %d\n", k);

    } else {
      printf("Ma mon hoc khong co trong chuong trinh!\n");
    }

    printf("Co thuc hien lai cong viec 3 khong? (1. Co, 0. Khong) : ");
    scanf("%d", &choice);

  } while(choice == 1);



  return 0;
}

Graph buildGraphFrom(FILE *file) {
  Graph G = create();

  char bar[MAX];
  int id = 1;
  int n;

  fscanf(file, "%d", &n);

  while(!feof(file)) {
    char *_sub = (char*)malloc(sizeof(char) * MAX );
    fscanf(file, "%s%[^\n]\n", _sub, bar);
    addVertex(&G, id++, _sub);
  }

  rewind(file);

  char foo;
  int j;
  int count;
  char s[MAX];
  int i = 0;

  fscanf(file, "%d", &n);

  while(!feof(file)) {
    char *sub = (char*)malloc(sizeof(char) * MAX );
    char *preSub = (char*)malloc(sizeof(char) * MAX );
    fscanf(file, "%s", sub);

    count = 0;

    do {
      fscanf(file, "%c", &foo);
      if(foo == ' ') count++;
      s[i++] = foo;
    } while(foo != '\n');

    s[--i] = '\0';

    fseek(file, -strlen(s)+1, SEEK_CUR);

    i = 0;

    for(j = 0; j < count-1; j++) {
      fscanf(file, "%s", preSub);

      JRB node;
      int u, v;

      jrb_traverse(node, G.vertices) {
        if(strcmp(sub, jval_s(node->val)) == 0)
          u = jval_i(node->key);
        if(strcmp(preSub, jval_s(node->val)) == 0)
          v = jval_i(node->key);
      }

      addEdge(G, v, u);
    }

    fscanf(file, "\n", &foo);
  }

  return G;
}

int getNumEdge(Graph G)
{
  int count = 0;
  JRB node, tree, tmp;

  jrb_traverse(tree, G.edges)
    {
      node = (JRB) jval_v(tree->val);
      jrb_traverse(tmp, node) count++;
    }

  return count;
}
