#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <jrb.h>
#include <dllist.h>

#define BIGNUM 999999999

typedef struct
{
  JRB edges;
  JRB vertices;
}Graph;

// tao do thi...........................................................

Graph creatGraph()
{
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  return g;
}

//them dinh.............................................................

void addVertex(Graph g,int id, char *value)
{
  if(g.vertices == NULL || g.edges == NULL)
    return;
  JRB node = jrb_find_int(g.vertices,id);
  if(node == NULL)
    {
      jrb_insert_int(g.vertices,id,new_jval_s(value));
    }
}

//lay gia tri cua dinh...................................................

char *getVetex(Graph g, int id)
{
  if(g.vertices == NULL || g.edges == NULL)
    return;
  JRB node = jrb_find_int(g.vertices,id);
  if(node != NULL)
    {
      return jval_s(node->val);
    }
  return NULL;
}

int getID(Graph g, char *s)
{
  JRB cur;
  jrb_traverse(cur, gra->vertices)
    {
      if (strcmp(s, cur->val.s) == 0)
	return cur->key.i;
    }
  printf("Khong co %s trong do thi\n", s);
  return -1;
}

//ktra canh ke............................................................

int adjacent(Graph g, int v1, int v2)
{
  if(g.vertices == NULL || g.edges == NULL)
    return;
  JRB node = jrb_find_int(g.edges, v1);
  if(node == NULL) return 0;

  JRB tree = (JRB)jval_v(node->val);
  JRB result = jrb_find_int(tree,v2);

  if(result != NULL) return 1;
  return 0;
}

//tao them canh...........................................................

void addEdge(Graph g,int v1,int v2)
{
  if(adjacent(g,v1,v2)) return;

  JRB node1 = jrb_find_int(g.edges, v1);
  JRB tree1;
  if(node1 == NULL)
    {
      tree = make_jrb();
      jrb_insert_int(g.edges,v1,new_jval_v(tree));
    }
  else
    tree = (JRB)jval_v(node->val);

  jrb_insert_int(tree,v2,new_jval_i(1));
}

//ban bac vao...............................................................

int indegree(Graph g, int v, int* output)
{
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
 
  JRB check = jrb_find_int(g.vertices,v);
  if(check == NULL) return 0;
  JRB tmp; int counter = 0;
  jrb_traverse(tmp,g.vertices)
    if(adjacent(g,jval_i(tmp->key),v))
      output[counter++] = jval_i(node->v);

  return counter;
}

//ban bac ra...............................................................

int outdegree(Graph graph, int v, int* output)
{
   if (g.edges == NULL || g.vertices == NULL)
    return 0;

   JRB check = jrb_find_int(g.vertices,v);
   if(check == NULL) return 0;
   JRB tmp,tree; int counter = 0;
   tree = (JRB)jval_v(check->val);
   jrb_traverse(tmp,tree)
     output[counter++] = jval_i(check->key);

   return counter;
}


int getComponents(Graph g);

//xoa do thi...............................................................

void dropGraph(Graph g)
{
  JRB node;
  jrb_traverse(node,g->edges)
    jrb_free_tree(jval_v(node->val));
  jrb_free_tree(g->vertices);
  jrb_free_tree(g->edges);
}


//tim dinh lon nhat........................................................

int getMaxId(Graph g)
{
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  int max_id = 0;
  JRB tmp;
  jrb_traverse(tmp,g.vertices)
    {
      int key = jval_i(tmp->key);
      if(key > max_id)
	max_id = key;
    }
  return max_id;
}

//tim dinh nho nhat........................................................

int getMinId(Graph g)
{
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  int min_id = BIGNUM;
  JRB tmp;
  jrb_traverse(tmp,g.vertices)
    {
      int key = jval_i(tmp->key);
      if(key < max_id)
	max_id = key;
    }
  return min_id;
}


// BFS ....................................................................

void BFS(Graph g,int start,int stop,void(*func)(Graph, int))
{
  if (g.edges == NULL || g.vertices == NULL)
    return;
  JRB tmp;
  int max_id = getMaxId(g);

  int *visited = (int *)malloc((max_id + 1) * sizeof(int));
  if(visited == NULL)
    {
      printf("Malloc failed!\n");
      return;
    }

  jrb_traverse(tmp,g.vertices)
    visited[jval_i(tmp->key)] = 0;

  JRB check = jrb_find_int(g.vertices,start);
  if(check == NULL)
    {
      free(visited);
      return;
    }

  Dllist queue = new_dllist();

  dll_append(queue,new_jval_i(start));

  while(!dll_empty(queue))
    {
      Dllist node = dll_first(queue);
      int u = jval_i(node->val);
      dll_delete_node(node);

      if(!visited[u])
	{
	  func(g,u);
	  visited[u] = 1;
	}

      if(u == stop)
	{
	  free(visited);
	  free_dllist(queue);
	  return;
	}

      JRB u_node = jrb_find_int(g.edges, u);
      if (u_node == NULL) continue;
      
      JRB v_connect_to_u = (JRB)jval(u_node->val);
      jrb_traverse(tmp, v_connect_to_u) 
	if (!visited[tmp->key.i])
	  dll_append(queue, new_jval_i(tmp->key.i));
      
    }
  free(visited);
  free_dllist(queue);
  
}
  
// DFS ....................................................................

void DFS(Graph g, int start, int stop, void (*func)(graph, int))
{
  if (g.edges == NULL || g.vertices == NULL)
    return;
  
  JRB tmp;
  int max_id = get_graph_max_id(g);

  int *visited = (int*)malloc((max_id + 1) * sizeof(int));
  if (visited == NULL)
    {
      printf("Malloc failed!\n");
      return;
    }
  
  jrb_traverse(tmp, g.vertices)
    visited[jval_i(tmp->key)] = 0;
    

  JRB check = jrb_find_int(g.vertices,start);
  if(check == NULL)
    {
      free(visited);
      return;
    }

  Dllist stack = new_dllist();
  
  dll_append(stack, new_jval_i(start));

  while (!dll_empty(stack))
    {
      Dllist node = dll_last(stack);
      int u = jval_i(node->val);
      dll_delete_node(node);

      if (!visited[u])
	{
	  func(g, u);
	  visited[u] = 1;
	}

    if (u == stop)
      {
	free(visited);
	free_dllist(queue);
	return;
      }

    JRB u_node = jrb_find_int(g.edges, u);
    if (u_node == NULL) continue;

    JRB v_connect_to_u = (JRB)(jval_v(u_node->val));

    jrb_rtraverse(tmp, v_connect_to_u)
      if (!visited[tmp->key.i])
        dll_append(stack, new_jval_i(tmp->key.i));
    
  }

  free(visited);
  free_dllist(stack);
}

int is_cyclic_from(graph g, int start)
{
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  JRB tmp;
  int max_id = get_graph_max_id(g);

  int *visited = (int*)malloc((max_id + 1) * sizeof(int));
  if (visited == NULL)
    {
      printf("Malloc failed!\n");
      return;
    }

  jrb_traverse(tmp, g.vertices) 
    visited[jval_i(tmp->key)] = 0;

  JRB check = jrb_find_int(g.vertices,start);
  if(check == NULL)
    {
      free(visited);
      return;
    }
  
  Dllist stack = new_dllist();

  dll_append(stack, new_jval_i(start));

  while (!dll_empty(stack))
    {
      Dllist node = dll_last(stack);
      int u = jval_i(node->val);
      dll_delete_node(node);

      if (!visited[u])
	{
	  visited[u] = 1;
	}

      if (u == start)
	{
	  free(visited);
	  free_dllist(stack);
	  return 1;
	}

      JRB u_node = jrb_find_int(g.vertices, u);
      if (u_node == NULL)
	continue;

    JRB v_connect_to_u = (JRB)(jval_v(u_node->val));


    jrb_rtraverse(tmp, v_connect_to_u) 
      if (!visited[tmp->key.i])
        dll_append(stack, new_jval_i(tmp->key.i));
    
  }
  
  free(visited);
  free_dllist(stack);
  return 0;
}

int is_cyclic(graph g)
{
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  JRB tmp;
  jrb_traverse(tmp, g.vertices)
    {
      if (is_cyclic_util(g, jval_i(tmp->key)))
	return 1;
    }
  return 0;
}
