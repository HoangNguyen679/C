#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int menu();
void sodinh_socanh();
void print_node(Graph g, int i);

Graph g;

int main()
{
  g = createGraph();
  while(1)
    {
      switch(menu())
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7: return 0;
	default: printf("\nLua chon sai!\n");
	}
    }
}

int menu()
{
  printf("\n\n----------MENU----------\n\n");
  printf("1. \n");
  printf("2. \n");
  printf("3. \n");
  printf("4. \n");
  printf("5. \n");
  printf("6. \n");
  printf("7. \n");
  printf("\nNhap lua chon: ");
  int k; scanf("%d",&k);
  return k;
}

void sodinh_socanh()
{
  int v = 0,e = 0;
  JRB tmp,node,tree;
  jrb_traverse(tmp,g.vertices)
    v++;
  jrb_traverse(tmp,g.edges)
    {
      tree = (JRB)jval_v(tmp->val);
      jrb_traverse(node,tree)
	e++;
    }
  
  printf("\nSo dinh la : %d\n",v); 
  printf("\nSo canh la : %d\n",e);
}

void print_node(Graph g, int i)
{
  printf("\t\t%s", getVertex(g, i));
}
