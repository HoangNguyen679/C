#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_jrb.h"


Graph creatGraph()
{
  return make_jrb();
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



