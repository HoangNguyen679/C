#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_jrb.h"
#define MAX 81
#define BIGNUM 99999999
typedef struct
{
  char name[MAX];
}station;

station *data;
void print_metro(int node)
{
  printf(" %s ", data[node - 1].name);
}

int UShortestPath(Graph g, int v1, int v2)
{
  int v = 0;
  JRB tmp;
  jrb_traverse(tmp,g) v++;
  int *visited = (int *)malloc(v * sizeof(int));
  int *d = (int *)malloc(v * sizeof(int));
  if(visited == NULL || d == NULL)
    {
      printf("Failed malloc\n");return -1;
    }
  int i;
  for(i = 0; i < v; i++)
    {
      visited[i] = 0;
      d[i] = BIGNUM;
    }
  
  Dllist queue = new_dllist();

  JRB node = jrb_find_int(g,v1);
  if(node == NULL)
    goto end;
  
  
  dll_append(queue,new_jval_i(v1));
  d[v1] = 0;
  visited[v1] = 1;
  
  while(!dll_empty(queue))
    {
      Dllist node = dll_first(queue);
      int u = jval_i(node->val);
      dll_delete_node(node); 

      JRB u_node = jrb_find_int(g,u);
      if(u_node == NULL) continue;

      JRB v_connect_to_u = (JRB)jval_v(u_node->val);
      jrb_traverse(tmp,v_connect_to_u)
	if(!visited[tmp->key.i])
	  {
	    visited[tmp->key.i] = 1;
	    d[tmp->key.i] = d[u] + 1;
	    
	    if(tmp->key.i == v2)
	      goto end;
	    dll_append(queue,new_jval_i(tmp->key.i));
	  }
	 
    }
 end:
  free(visited);
  free_dllist(queue);
  return d[v2];
}

int main()
{
  Graph g = creatGraph();

  char filename[]="line.txt";
  FILE *f = fopen(filename,"r");
  if(f == NULL)
    {printf("Failed open file\n");return 1;}
  char s[MAX];
  while(1)
    {
      fscanf(f,"%[^\n]\n",s);
      if(strcmp(s,"[STATIONS]") == 0) break;
    }

 
  
  int malloc_x = 10;
  data = (station *)malloc(malloc_x * sizeof(station));
  if(data == NULL)
    {printf("Malloc failed\n");return 1;}
  int order = 0;
  
  while(1)
    {
      fscanf(f,"%[^\n]\n",s);
       if(strcmp(s,"[LINES]") == 0) break;
       if (strcmp(s, "\n") == 0) continue;

       int i;
       for (i = 0; s[i] != '\0' && s[i] != '='; i++);
       if (s[i] == '\0') continue;
       
       if(order == 9)
	 {
	   malloc_x += 10;
	   data = (station *)realloc(data, sizeof(station) * malloc_x);
	 }
       sscanf(s,"S%*d=%[^\n]\n",data[order++].name);
    }

  while(!feof(f))
    {
      fscanf(f,"%[^\n]\n",s);
      int i;
      for (i = 0; s[i] != '\0' && s[i] != '='; i++);
      if (s[i] == '\0') continue;

      char s2[MAX];
      sscanf(s, "%*[^=]=%[^\n]", s2);
      char *p = strtok(s2, " ");
      int v1 = p[1] - '0';
      p = strtok(NULL," ");
      while(p != NULL)
	{
	  int v2 = p[1] - '0';
	  addEdge(g,v1,v2);
	  v1 = v2;
	  p = strtok(NULL," ");
	}
    }

  int i;
  printf("%s\n", "LIST OF METRO STATIONS");
  for (i = 0; i < order; ++i)
    {
      printf("%3d. %s\n", i + 1, data[i].name);
    }
  printf("\n\n");

  
  
  printf("%s", "Find shortest path between 2 metro stations :\n"
            "Select Number of start station \n\t> ");
     int start, stop;
     scanf(" %d", &start);
     printf("%s", "Select Number of end station \n\t> ");
     scanf(" %d", &stop);

     printf("%s\n", "shortest path :");
     BFS(g, start, stop, print_metro);
     printf("\n\n");
     printf("%d\n",UShortestPath(g,start,stop));

}
