#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jrb.h>

#define SIZE_MAX 100

typedef JRB Graph;


Graph creatGraph()
{
  return make_jrb();
}

int isAdjacent(Graph g, int v1, int v2)
{
  if(g == NULL) return 0;
  JRB node = jrb_find_int(g, v1);
  if (node != NULL) // vertex v1 is already in graph
    {
      JRB tree_v1 = (JRB)jval_v(node->val);
      JRB result = jrb_find_int(tree_v1,v2);
      if(result != NULL) return 1;
      else return 0;
    }
  return 0; 
}


void setEdge(Graph g, int v1, int v2)
{
  if(isAdjacent(g,v1,v2)) return;
  JRB node1 = jrb_find_int(g, v1);
  if(node1 != NULL)
    {
      JRB tree_v1 = (JRB)jval_v(node1->val);
      jrb_insert_int(tree_v1, v2, new_jval_i(1));
    }
  else
    {
      JRB tree = make_jrb();
      jrb_insert_int(g, v1, new_jval_v(tree));
      jrb_insert_int(tree, v2, new_jval_i(1));
    }

  JRB node2 = jrb_find_int(g, v2);
  if(node2 != NULL)
    {
      JRB tree_v2 = (JRB)jval_v(node2->val);
      jrb_insert_int(tree_v2, v1, new_jval_i(1));
    }
  else
    {
      JRB tree = make_jrb();
      jrb_insert_int(g, v2, new_jval_v(tree));
      jrb_insert_int(tree, v1, new_jval_i(1));
    }
}


int getAdjacentVertices(Graph g, int v, int* output)
{
  if (g == NULL) return 0;
  int counter = 0;
  JRB node = jrb_find_int(g, v);
  JRB tree_v = (JRB)jval_v(node->val);

  JRB tmp;
  jrb_traverse(tmp,tree_v)
    output[counter++] = jval_i(tmp->key);

  return counter;
}


void dropGraph(Graph *g)
{
  
  JRB graph = (JRB) *g;
  JRB node;
  jrb_traverse(node, graph)
    jrb_free_tree(jval_v(node->val));
  jrb_free_tree(*g);
  *g = NULL;

}

int main(int argc, char *argv[])
{
  argc = argc;
  NULL == argv[argc];

  int n,i;
  int output[SIZE_MAX];

  Graph g = creatGraph(SIZE_MAX);

  setEdge(g,0,1);
  setEdge(g,0,2);
  setEdge(g,1,2);
  setEdge(g,1,3);

  n = getAdjacentVertices(g, 1, output);
  if(!n) printf("No adjacent vertices of node 1!\n");
  else {
    printf("Adjacent of node 1 is:\n");
    for(i = 0; i < n; i++)
      printf("%5d\t",output[i]);
    printf("\n");
  }
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



