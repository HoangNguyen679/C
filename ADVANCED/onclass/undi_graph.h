#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jrb.h>
#include <dllist.h>
#define BIGNUM 999999999

typedef JRB Graph;

//tao do thi......................................................

Graph creatGraph()
{
  return make_jrb();
}

//kiem tra v1 co la canh ke cua v2 kh..............................

int adjacent(Graph g, int v1,int v2)
{
  if (g == NULL) return 0;

  JRB node = jrb_find_int(g,v1);
  if(node != NULL)
    {
      JRB tree = (JRB)jval_v(node->val);
      JRB result = jrb_find_int(tree,v2);
      if(result != NULL) return 1;
      return 0;
    }

  return 0;
}

//tao canh giua v1 va v2..........................................

void addEdge(Graph g, int v1,int v2)
{
  if(adjacent(g,v1,v2)) return;

  JRB node1 = jrb_find_int(g,v1);
  if(node1 != NULL)
    {
      JRB tree1 = (JRB)jval_v(node1->val);
      jrb_insert_int(tree1,v2,new_jval_i(1));
    }
  else
    {
      JRB tree = make_jrb();
      jrb_insert_int(g,v1,new_jval_v(tree));
      jrb_insert_int(tree,v2,new_jval_i(1));
    }

  JRB node2 = jrb_find_int(g,v2);
  if(node2 != NULL)
    {
      JRB tree2 = (JRB)jval_v(node2->val);
      jrb_insert_int(tree2,v1,new_jval_i(1));
    }
  else
    {
      JRB tree = make_jrb();
      jrb_insert_int(g,v2,new_jval_v(tree));
      jrb_insert_int(tree,v1,new_jval_i(1));
    }
}

//so dinh ke voi dinh v............................................

int getAdjacentVertices(Graph g, int v, int *output)
{
  if(g == NULL) return 0;

  int counter = 0;
  JRB node = jrb_find_int(g,v);
  if(node == NULL) return 0;
  JRB tree = (JRB)jval_v(node->val);
  JRB tmp;
  jrb_traverse(tmp,tree)
    output[counter++] = jval_i(tmp->key);
  
  return counter;
}

//xoa do thi.......................................................

void dropGraph(Graph *g)
{
  JRB graph = (JRB) *g;
  JRB tmp;
  jrb_traverse(tmp,graph)
    jrb_free_tree(*g);
  *g = NULL;
}

//BFS .............................................................

void BFS(Graph g,int start,int stop,void(*func)(int))
{
  JRB tmp;
  int v = 0,i;

  jrb_traverse(tmp,g) v++;
  int *visited = (int *)malloc(v * sizeof(int));
  if(visited == NULL) {printf("Malloc failed!\n");return;}
  for(i = 0; i < v; i++) visited[i] = 0;

  JRB check1 = jrb_find_int(g,start);
  JRB check2 = jrb_find_int(g,stop);
  if(check1 == NULL )
    { free(visited);return;}
  if(stop != -1 && check2 == NULL)
    { free(visited);return;}
  
  Dllist queue = new_dllist();
  dll_append(queue,new_jval_i(start));

  while(!dll_empty(queue))
    {
      Dllist node = dll_first(queue);
      int u = jval_i(node->val);
      dll_delete_node(node);
      if(!visited[u])
	{
	  func(u);
	  visited[u] = 1;
	}
      if(u == stop) goto end;
      
      JRB u_node = jrb_find_int(g,u);
      if(u_node == NULL) continue;
      JRB v_connect_to_u = (JRB)jval_v(u_node->val);
      jrb_traverse(tmp,v_connect_to_u)
	if(!visited[tmp->key.i])
	  dll_append(queue,new_jval_i(tmp->key.i)); 
    }
 end:
  free(visited);
  free_dllist(queue);
}

//duong di ngan nhat dung BFS.....................................

int UShortestPath(Graph g,int v1,int v2,void(*func)(int,int,int*))
{
  JRB tmp;
  int v = 0,i;
  
  jrb_traverse(tmp,g) v++;
  int *visited = (int *)malloc(v * sizeof(int));
  int *d = (int *)malloc(v * sizeof(int));
  int *way = (int *)malloc(v * sizeof(int));
  if(visited == NULL|| d == NULL || way == NULL)
    {printf("Malloc failed!\n");return -2;}
  for(i = 0; i < v; i++)
    {
     visited[i] = 0;
     d[i] = BIGNUM;
     way[i] = -1;
    }

  JRB check1 = jrb_find_int(g,v1);
  JRB check2 = jrb_find_int(g,v2);
  if(check1 == NULL || check2 == NULL)
    {
      free(visited);
      return -1;
    }
  
  Dllist queue = new_dllist();
  dll_append(queue,new_jval_i(v1));
  d[v1] = 0;

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
	    way[tmp->key.i] = u;
	    if(tmp->key.i == v2)
	      {
		printf("\n\nDuong di ngan nhat la: ");
		func(v2,v1,way);
		free(visited);
		free_dllist(queue);
		return d[v2];
	      }
	    dll_append(queue,new_jval_i(tmp->key.i));
	  }
    }
}

// DFS ..........................................................

void DFS(Graph g, int start, int stop, void(*func)(int))
{
  JRB tmp;
  int v = 0,i;

  jrb_traverse(tmp,g) v++;
  int *visited = (int*)malloc(v * sizeof(int));
  if(visited == NULL) {printf("Failed malloc\n");return;}
  for(i = 0; i < v; i++) visited[i] = 0;

  JRB check1 = jrb_find_int(g,start);
  JRB check2 = jrb_find_int(g,stop);
  if(check1 == NULL )
    { free(visited);return;}
  if(stop != -1 && check2 == NULL)
    { free(visited);return;}
  
  Dllist stack = new_dllist();
  dll_append(stack, new_jval_i(start));

  while(!dll_empty(stack))
    {
      Dllist node = dll_last(stack);
      int u = jval_i(node->val);
      dll_delete_node(node);

      if(!visited[u])
	{
	  func(u);
	  visited[u] = 1;
	}
      if(u == stop) goto end;

      JRB u_node = jrb_find_int(g, u);
      if(u_node == NULL) continue;

      JRB v_connect_to_u = (JRB)jval_v(u_node->val);
      jrb_rtraverse(tmp, v_connect_to_u)
	if(!visited[tmp->key.i])
	  dll_append(stack, new_jval_i(tmp->key.i));
    }
 end:
  free(visited);
  free_dllist(stack);
}

//ktra 1 dinh co chu trinh........................................

int isCycleVertex(Graph g,int start)
{
  JRB tmp;
  int v = 0,i;
  jrb_traverse(tmp,g) v++;
  int *visited = (int *)malloc(v * sizeof(int));
  if(visited == NULL)
    {printf("Failed malloc\n");return -1;}
  
  for(i = 0; i < v; i++) visited[i] = 0;
  Dllist stack = new_dllist();

  JRB node = jrb_find_int(g, start);
  if(node == NULL) goto end;

   dll_append(stack, new_jval_i(start));

  while(!dll_empty(stack))
    {
      Dllist node = dll_last(stack);
      int u = jval_i(node->val);
      dll_delete_node(node);

      if(!visited[u])
	{ visited[u] = 1;}
          
      if(u == start)
	{
	  free(visited);
	  free_dllist(stack);
	  return 1;
	}

      JRB u_node = jrb_find_int(g, u);
      if(u_node == NULL) continue;

      JRB v_connect_to_u = (JRB)jval_v(u_node->val);
      jrb_rtraverse(tmp, v_connect_to_u)
	  if(!visited[tmp->key.i])
	  {
	    dll_append(stack, new_jval_i(tmp->key.i));
	  }		
    }
 end:
  free(visited);
  free_dllist(stack);
  return 0;
}

// ktra chu trinh................................................

int isCycle(Graph g)
{
  JRB tmp;
  jrb_traverse(tmp,g) 
    if(isCycleVertex(g,jval_i(tmp->key)))
      return 1;
  return 0;
}

