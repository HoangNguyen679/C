#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_jrb.h"


Graph creatGraph()
{
  return make_jrb();
}


void addEdge(Graph g, int v1, int v2)
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
  if (g == NULL) return 0;
  
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
  if(g == NULL) return 0;
  
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

// BFS ....................................................................

void BFS(Graph g, int start,int stop, void(*func)(int))
{
  int v = 0;
  JRB tmp;
  jrb_traverse(tmp,g) v++;
  int *visited = (int *)malloc(v * sizeof(int));
  if(visited == NULL)
    {
      printf("Failed malloc\n");return ;
    }
  int i;
  for(i = 0; i < v; i++) visited[i] = 0;
  
  Dllist queue = new_dllist();

  JRB node = jrb_find_int(g,start);
  if(node == NULL)
    goto end;

  dll_append(queue,new_jval_i(start));
  func(start);
  visited[start] = 1;

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
	    func(tmp->key.i);
	    visited[tmp->key.i] = 1;
	    if(tmp->key.i == stop)
	       goto end;
	    dll_append(queue,new_jval_i(tmp->key.i));  
	  }

    }
 end:
  free(visited);
  free_dllist(queue);
}

// DFS ...................................................................

void DFS(Graph g, int start, int stop, void(*visited_func)(int))
{
  JRB tmp;
  int v = 0;
  jrb_traverse(tmp,g) v++;
  
  int *visited = (int*)malloc(v * sizeof(int));
  if(visited == NULL)
    {
      fprintf(stderr, "Allocated failed in %s:%d \n",
	      __FILE__, __LINE__);
      exit(1);
    }
  
  int i;
  for(i = 0; i < v; i++) visited[i] = 0;

  Dllist stack = new_dllist();

  // add start to stack
  JRB node = jrb_find_int(g, start);
  if(node == NULL)
    goto end;

  dll_append(stack, new_jval_i(start));
  //

  while(!dll_empty(stack))
    {
      Dllist node = dll_last(stack);
      int u = jval_i(node->val);
      dll_delete_node(node);

      if(!visited[u])
	{
	  visited_func(u);
	  visited[u] = 1;
	}
          
      if(u == stop) 
	goto end;

      JRB u_node = jrb_find_int(g, u);
      if(u_node == NULL)
	continue;

      JRB vertex_connect_to_u_tree = (JRB)(jval_v(u_node->val));
      jrb_rtraverse(tmp, vertex_connect_to_u_tree)
	{
	  if(!visited[tmp->key.i])
	    dll_append(stack, new_jval_i(tmp->key.i));
	}
    }
 end:
  free(visited);
  free_dllist(stack);
}
