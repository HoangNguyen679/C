#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mylibrary.h"
#include"w_graph.h"
int str_i(char *s) {
  int i=0, n;
  int x=0;
  while (s[i]!='\0')
    i++;
  n=i;
  for (i=0; i<n; i++)
    x=x*10+(s[i]-48);
  printf("%d\n", x);
  return x;
}
void main(int argc, char *argv[]) {
  int select=1;
  FILE *f;
  int site, link, i, n, output[MAX_SIZE];
  char name[100];
  int u, v, id, z, k;
  graph g;
  int maxD;
  if(strcmp(argv[1], "about")==0)
    select=1;
  if(strcmp(argv[1], "size")==0)
    select=2;
  if(strcmp(argv[1], "out")==0)
    select=3;
  if(strcmp(argv[1], "maxin")==0)
    select=4;
  if(strcmp(argv[1], "selfref")==0)
    select=5;
  if(strcmp(argv[1], "list")==0)
    select=6;
  switch (select) {
  case 1:
    if (argc==2)
      printf("Bai thi lap trinh C nang cao HK2-2014-2015\n");
      break;
  case 2:
    if (argc==3) {
      g=createGraph();
      f=fopen(argv[2], "r");
      fscanf(f, "%d\n", &site);
      for (i=0; i<site; i++) {
	fscanf(f, "%s %d\n", name, &id);
	addVertex(g, id, name);
      }
      fscanf(f, "%d\n", &link);
      for (i=0; i<link; i++) {
	fscanf(f, "%d %d\n", &u, &v);
	addVector(g, u, v, 1);
      }
      fclose(f);
      printf("%d %d\n", site, link);
    }
    break;
  case 3:
    if (argc==4) {
      g=createGraph();
      f=fopen(argv[2], "r");
      fscanf(f, "%d\n", &site);
      for (i=0; i<site; i++) {
	fscanf(f, "%s %d\n", name, &id);
	addVertex(g, id, name);
      }
      fscanf(f, "%d\n", &link);
      for (i=0; i<link; i++) {
	fscanf(f, "%d %d\n", &u, &v);
	addVector(g, u, v, 1);
      }
      fclose(f);
      id=str_i(argv[3]);
      n=outDegree(g, id, output);
      for (i=0; i<n; i++)
	printf("%s\n", getVertex(g, output[i]));
    }
    break;
  case 4:
    if (argc==3) {
      g=createGraph();
      f=fopen(argv[2], "r");
      fscanf(f, "%d\n", &site);
      for (i=0; i<site; i++) {
	fscanf(f, "%s %d\n", name, &id);
	addVertex(g, id, name);
      }
      fscanf(f, "%d\n", &link);
      for (i=0; i<link; i++) {
	fscanf(f, "%d %d\n", &u, &v);
	addVector(g, u, v, 1);
      }
      fclose(f);
      maxD=-1;
      void func1(int x) {
	if (inDegree(g, x, output)>=inDegree(g, maxD, output))
	  maxD=x;
      }
      graph_traverse(g, jval_i(g.edge->flink->key), -1, func1);
      printf("%s\n", getVertex(g, maxD));  
    }  
    break;
  case 5:
    if (argc==3) {
      g=createGraph();
      f=fopen(argv[2], "r");
      fscanf(f, "%d\n", &site);
      for (i=0; i<site; i++) {
	fscanf(f, "%s %d\n", name, &id);
	addVertex(g, id, name);
      }
      fscanf(f, "%d\n", &link);
      for (i=0; i<link; i++) {
	fscanf(f, "%d %d\n", &u, &v);
	addVector(g, u, v, 1);
      }
      fclose(f);
      if (DAG(g)==1)
	printf("OK\n");
      else {
	void func2(int x) {
	  int out_put[MAX_SIZE], out_put2[MAX_SIZE];
	  int m;
	  z=-1;
	  n=inDegree(g, x, out_put);
	  for (i=0; i<n; i++)
	    if (single_pair(g, x, out_put[i], out_put2, &m)!=INFINITIVE)
	      z=x;
	}
	graph_traverse(g, jval_i(g.edge->flink->key), -1, func2);
	if (z!=-1) 
	  printf("%s\n", getVertex(g, z));
      }
    }
    break;
  case 6:
    if (argc==5) {
      g=createGraph();
      f=fopen(argv[2], "r");
      fscanf(f, "%d\n", &site);
      for (i=0; i<site; i++) {
	fscanf(f, "%s %d\n", name, &id);
	addVertex(g, id, name);
      }
      fscanf(f, "%d\n", &link);
      for (i=0; i<link; i++) {
	fscanf(f, "%d %d\n", &u, &v);
	addVector(g, u, v, 1);
      }
      fclose(f);
      id=str_i(argv[3]);
      k=str_i(argv[4]);
      void func3(int x) {
	int out_put[MAX_SIZE];
	int m;
	if (single_pair(g, id, x, out_put, &m)<=k)
	  printf("%s\n", getVertex(g, x));
      }
      graph_traverse(g, jval_i(g.edge->flink->key), -1, func3);
    }
    break;
  }
}
