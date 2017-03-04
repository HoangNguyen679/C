#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directed_graph.h"

// creat ...............................................................

Graph createGraph()
{
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  if (G.vertices == NULL || G.edges == NULL)
    printf("%s\n", "Could not create graph! ERROR: make_jrb failed!");
  return g;
}

// add vertex...........................................................

void addVertex(Graph g, int id, char *value)
{
  if(g.edges == NULL || g.vertices == NULL)
    return;
  JRB node = jrb_find_int(g.vertices,id);
  if(node == NULL)
    jrb_insert_int(g.vertices, id, new_jval_s(value));
  else
    strcpy(jval_s(node->val),value);
}

// get vertex............................................................

char *getVertex(Graph graph, int id)
{
  if(g.edges == NULL || g.vertices == NULL)
    return NULL;
  JRB node = jrb_find_int(g.vertices,id);
  if(node != NULL)
    return jval_s(node->val);
  return NULL;
}

// addEdge...............................................................

void addEdge(Graph g, int v1, int v2)
{
  if hasEdge(g,v1,v2) return;
  
  JRB node = jrb_find_int(g.edges,v1);
  JRB tree = make_jrb();

  if(node == NULL)
    jrb_insert_int(g.edges,v1, new_jval_v(tree));
  else
    tree = (JRB)jval_v(node->val);
  jrb_insert_int(tree, v2, new_jval_i(1));
  
}

// hasEdge...............................................................

int hasEdge(Graph g, int v1, int v2)
{
  if(g.edges == NULL || g.vertices == NULL)
    return;

  JRB node = jrb_find_int(g.edges,v1);
  if(node == NULL) return 0;

  JRB tree;
  tree = jrb_v(node->val);
  JRB f = jrb_find_int(tree, v2);
  if(f != NULL) return 1;
  return 0;
}

// Indegree..............................................................

int inDegree(Graph g, int v, int *output)
{
  if(g.edges == NULL || g.vertices == NULL)
    return 0;

  JRB node = jrb_find_int(g.vertices, v);
  if (node == NULL) return 0;

  int total = 0;

  jrb_traverse(node, g.vertices)
    if(hasEdge(g,jval_i(node->key),v))
      output[total++] = jval_i(node->key);

  return total;
}

// Outdegree.............................................................

int outDegree(Graph g, int v, int *output)
{
   if(g.edges == NULL || g.vertices == NULL)
    return 0;
   JRB node = jrb_find_int(g.vertices, v);
   if (node == NULL) return 0;

   int total = 0;
   JRB tree = (JRB)jval_v(node->val);
   jrb_traverse(node, tree)
     output[total++] = jval_i(node->key);
   
  return total;
}

// Drop.................................................................

void dropGraph(Graph *g)
{
  JRB node;
  jrb_traverse(node, g->edges)
    jrb_free_tree(jval_v(node->val));
  jrb_free_tree(g->vertices);
  jrb_free_tree(g->edges);

}

// BFS..................................................................

void BFS(Graph g, int start, int stop, void (*visited_func)(Graph, int))
{
  if(g.edges == NULL || g.vertices == NULL)
    return;

  JRB tmp;
  int max_id = get_graph_max_id(g);

  int *visited = (int *)malloc((max_id + 1) * sizeof(int));
  if (visited == NULL)
    {
      fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
      exit(1);
    }

  JRB node;
  jrb_traverse(node, g.vertices) 
    visited[jval_i(node->key)] = 0;
  
  Dllist queue = new_dllist();

  node = jrb_find_int(g.vertices, start);
  if(node == NULL) goto end;

  dll_append(queue, new_jval_i(start));

  while(!dll_empty(queue))
    {
      Dllist node = dll_first(queue);
      int u = jval_i(node->val);
      dll_delete_node(node);

      if(!visited[u])
	{
	  visited_func(g,u);
	  visited[u] = 1;
	}

      if(u == stop) goto end;

      JRB u_node = jrb_find_int(g.edges, u);
      if(u_node == NULL)
	continue;

      JRB vertex_connect_to_u_tree = (JRB)jval_v(u_node-val);

      jrb_traverse(tmp, vertex_connect_to_u_tree)
	if(!visited[tmp->key.i])
	  dll_append(queue, new_jval_i(tmp->key.i));
    }
 end:
  free(visited);
  free_dllist(queue);
}

// DFS ...................................................................

void DFS(Graph g, int start, int stop, void (*visited_func)(Graph, int))
{
  if(g.edges == NULL || g.vertices == NULL)
    return;

  JRB tmp;
  int max_id = get_graph_max_id(g);

  int *visited = (int *)malloc((max_id + 1) * sizeof(int));
  if (visited == NULL)
    {
      fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
      exit(1);
    }

  JRB node;
  jrb_traverse(node, g.vertices) 
    visited[jval_i(node->key)] = 0;
  
  Dllist stack = new_dllist();

  node = jrb_find_int(g.vertices, start);
  if(node == NULL) goto end;

  dll_append(stack, new_jval_i(start));

  while(!dll_empty(stack))
    {
      Dllist node = dll_last(stack);
      int u = jval_i(node->val);
      dll_delete_node(node);

      if(!visited[u])
	{
	  visited_func(g,u);
	  visited[u] = 1;
	}

      if(u == stop) goto end;

      JRB u_node = jrb_find_int(g.edges, u);
      if(u_node == NULL)
	continue;

      JRB vertex_connect_to_u_tree = (JRB)jval_v(u_node-val);

      jrb_traverse(tmp, vertex_connect_to_u_tree)
	if(!visited[tmp->key.i])
	  dll_append(stack, new_jval_i(tmp->key.i));
    }
 end:
  free(visited);
  free_dllist(stack);
}

// get max id ..........................................................

int get_graph_max_id(Graph g)
{
   if(g.edges == NULL || g.vertices == NULL)
    return 0;

   int max_id = 0;
   JRB tmp;
   jrb_traverse(tmp, g.vertices)
     {
       int key = jval_i(tmp->key);
       if(key > max_id)
	 max_id = key;
     }
   return max_id;
}

// get min id ..........................................................

int get_graph_min_id(Graph g)
{
   if(g.edges == NULL || g.vertices == NULL)
    return 0;

   int min_id = 10000000;
   JRB tmp;
   jrb_traverse(tmp, g.vertices)
     {
       int key = jval_i(tmp->key);
       if(key < min_id)
	 min_id = key;
     }
   return min_id;
}

// vetex has cycle ......................................................

int is_cyclic_util(Graph g, int start)
{
  if(g.edges == NULL || g.vertices == NULL)
    return 0;

  JRB tmp;
  int max_id = get_graph_max_id(g);

  int *visited = (int *)malloc((max_id + 1) * sizeof(int));
  if(visited == NULL)
    {
      fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
      exit(1);
    }

  JRB node;
  jrb_traverse(node, g.vertices)
    visited[jval_i(node_.key)] = 0;

  Dllist stack = new_dllist();

  node = jrb_find_int(g.vertices, start);
  if(node == NULL) goto end;

  dll_append(stack, new_jval_i(start));

  while(!dll_empty(stack))
    {
      Dllist node = dll_last(stack);
      int u = jval_i(node->val);
      dll_delete_node(node);

      if(!visited[u])
	visited[u] = 1;

      if(u == start)
	{
	  free(visited);
	  free_dllist(stack);
	  return 1;
	}

      JRB u_node = jrb_find_int(g.vertices, u);
      if(u_node == NULL) continue;

      JRB vertex_connect_to_u_tree = (JRB)(jval_v(u_node->val));
      jrb_traverse(tmp, vertex_connect_to_u_tree)
	if(!visited[tmp->key.i])
	  dll_append(stack, new_jval_i(tmp->key));
    }
 end:
  free(visited);
  free_dllist(stack);
  return 0;
}

// graph has cycle .......................................................

int isCyclic(Graph g)
{
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  JRB tmp;
  jrb_traverse(tmp, g.vertices)
    if(is_cyclic_util(g, jval_i(tmp->key)))
      return 1;
  return 0;
}

// topological sorting....................................................

void TSort(Graph g, void (*visited_func)(Graph, int))
{
  if (g.edges == NULL || g.vertices == NULL)
    return;

  
}
