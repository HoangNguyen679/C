#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <jrb.h>
#include <dllist.h>
#define INFINITY 1000000
#define UNDEFINED -1
#define MAX 1000

typedef struct graph
{
    JRB vertices;
    JRB edges;
} Graph;

Graph createGraph();
int addVertex(Graph g, int v, char *value);
char *getVertex(Graph g, int v);
int getID(Graph g, char *s);
int deleteVertex(Graph g, int v);
void addEdge(Graph g, int v1, int v2, double weight);
int deleteEdge(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int getEdgeValue(Graph, int, int);
void setEdgeValue(Graph g,int v1,int v2,double weight);
int inDegree(Graph g, int v, int *output);
int outDegree(Graph g, int v, int *output);
int allIndegree(Graph g, int v, int *output);
int allOutdegree(Graph g, int v, int *output);
void dropGraph(Graph g);
void BFS(Graph g, int start, int stop, void (*func)(Graph, int));
void DFS(Graph g, int start, int stop, void (*func)(Graph, int));
int get_graph_max_id(Graph g);
int get_graph_min_id(Graph g);
int is_cyclic_util(Graph g, int start);
int is_cyclic(Graph g);
void TSort(Graph g, void (*func)(Graph, int));
int shortest_path(Graph, int s, int t, int* path, int* length);
int DAG(Graph g);
  
// tao do thi..................................................................

Graph createGraph()
{
    Graph g;
    g.vertices = make_jrb();
    g.edges = make_jrb();
    return g;
}

// them dinh ..................................................................

int addVertex(Graph g, int v, char *value)
{
    if(g.edges == NULL || g.vertices == NULL)
      return -1;
    JRB check = jrb_find_int(g.vertices,v);
    if(check == NULL)
      {
	jrb_insert_int(g.vertices,v,new_jval_s(strdup(value)));
	return 1;
      }
    return 0;
}

// lay ten dinh................................................................

char *getVertex(Graph g, int v)
{
    if(g.edges == NULL || g.vertices == NULL)
      return NULL;
    JRB check = jrb_find_int(g.vertices,v);
    if(check != NULL)
      return jval_s(check->val);
    return NULL;
}

//xoa dinh.....................................................................

int deleteVertex(Graph g, int v)
{
  JRB node,node2,tree,tmp;   
  node = jrb_find_int(g.vertices,v);
  jrb_delete_node(node);
  
  node = jrb_find_int(g.edges,v);
  if (node == NULL) 
    return 0;
  jrb_traverse(tmp, g.edges)
    {
      tree = jrb_find_int((JRB)tmp->val.v, v);
      if (tree != NULL) 
	jrb_delete_node(tree);
    }
  node2 = (JRB)node->val.v;
  jrb_free_tree(node2);
  jrb_delete_node(node);
  return 1;
}

// them canh...................................................................

void addEdge(Graph g, int v1, int v2, double weight)
{
    if(adjacent(g, v1, v2)) return;

    JRB node1 = jrb_find_int(g.edges, v1);
    JRB tree;
    if(node1 == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(g.edges,v1,new_jval_v(tree));
    }
    else 
      tree = (JRB)jval_v(node1->val);
    jrb_insert_int(tree,v2,new_jval_d(weight));
}

//xoa canh.....................................................................

int deleteEdge(Graph g, int v1, int v2)
{
  JRB node1,tree,result;
  node1 = jrb_find_int(g.edges, v1);
  if (node1 == NULL)
    return 0;
  tree = (JRB)jval_v(node1->val);
  result = jrb_find_int(tree, v2);
  if(result == NULL)
    return 0; 
  jrb_delete_node(node1);
  return 1;
}

// ktra canh ke ...............................................................

int adjacent(Graph g, int v1, int v2)
{
    if(g.edges == NULL || g.vertices == NULL)
      return 0;
    JRB check1 = jrb_find_int(g.edges,v1);
    if(check1 == NULL)
      return 0;
    JRB tree = (JRB)jval_v(check1->val);
    JRB result = jrb_find_int(tree, v2);
    if(result != NULL)
      return 1;
    return 0;
}

//lay id cua dinh...............................................................

int getID(Graph g, char *s)
{
    JRB tmp;
    jrb_traverse(tmp,g.vertices)
      if (strcmp(s,tmp->val.s) == 0) 
	return tmp->key.i;
    // printf("Khong co %s trong do thi\n", s);
    return -1;
}

//lay gia tri cua canh.........................................................

int getEdgeValue(Graph g, int v1, int v2)
{
    if(!adjacent(g,v1,v2))
        return INFINITY;
    JRB node1,tree,result;
    node1 = jrb_find_int(g.edges, v1);
    tree = (JRB) jval_v(node1->val);
    result = jrb_find_int(tree, v2);
    return jval_d(result->val);
}

//tao gia tri cua canh..........................................................

void setEdgeValue(Graph g,int v1,int v2,double weight)
{
  if(!adjacent(g,v1,v2))
    return;
  JRB node,tree,result;
  node = jrb_find_int(g.edges,v1);
  tree = (JRB)jval_v(node->val);
  result = jrb_find_int(tree,v2);
  jrb_delete_node(result);
  jrb_insert_int(tree,v2,new_jval_d(weight));
}

//ban bac vao..................................................................

int inDegree(Graph g, int v, int *output)
{
    if (g.edges == NULL || g.vertices == NULL)
        return 0;
    JRB node = jrb_find_int(g.vertices, v);
    if (node == NULL)
      return 0;
    int total = 0;
    JRB tmp;
    jrb_traverse(tmp, g.vertices)
      if(adjacent(g, jval_i(tmp->key), v))
	output[total++] = jval_i(tmp->key);
    return total;
}

//tat ca ban bac vao ..........................................................

int allIndegree(Graph g, int v, int *output)
{
  int x,i,j,p = 0,y,u,total = 0;
  int tmp[MAX],visited[MAX] = {};
  Dllist queue = new_dllist();
  x = inDegree(g,v,tmp);
  for(i = 0; i < x; i++)
    {
      dll_append(queue, new_jval_i(tmp[i]));
      visited[tmp[i]] = 1;
      total++;
    }
  while (!dll_empty(queue))
    {
      Dllist node = dll_first(queue);
      u = node->val.i;
      dll_delete_node(node);
      output[p++] = u;

      y = inDegree(g,u,tmp);
      for(j = 0; j < y; j++)
	if(visited[tmp[j]] == 0)
	  {
	    dll_append(queue,new_jval_i(tmp[j]));
	    visited[tmp[j]] = 1;
	    total++;
	  }
    }
  free_dllist(queue);
  return total;
}

//ban bac ra...................................................................

int outDegree(Graph g, int v, int *output)
{
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  JRB node = jrb_find_int(g.edges, v);
  if (node == NULL)
    return 0;
  int total = 0;
  JRB tree = (JRB) jval_v(node->val);
  JRB tmp;
  jrb_traverse(tmp,tree)
    output[total++] = jval_i(tmp->key);
  return total;
}

// tat ca ban bac ra............................................................

int allOutdegree(Graph g, int v, int *output)
{
  int x,i,j,p = 0,y,u,total = 0;
  int tmp[MAX],visited[MAX] = {};
  Dllist queue = new_dllist();
  x = outDegree(g,v,tmp);
  for(i = 0; i < x; i++)
    {
      dll_append(queue, new_jval_i(tmp[i]));
      visited[tmp[i]] = 1;
      total++;
    }
  while (!dll_empty(queue))
    {
      Dllist node = dll_first(queue);
      u = node->val.i;
      dll_delete_node(node);
      output[p++] = u;

      y = outDegree(g,u,tmp);
      for(j = 0; j < y; j++)
	if(visited[tmp[j]] == 0)
	  {
	    dll_append(queue,new_jval_i(tmp[j]));
	    visited[tmp[j]] = 1;
	    total++;
	  }
    }
  free_dllist(queue);
  return total;
}

// xoa do thi..................................................................

void dropGraph(Graph g)
{
    JRB node;
    jrb_traverse(node, g.edges)
        jrb_free_tree(jval_v(node->val));
    jrb_free_tree(g.vertices);
    jrb_free_tree(g.edges);
}

//BFS..........................................................................

void BFS(Graph g, int start, int stop, void (*func)(Graph, int))
{
    if (g.edges == NULL || g.vertices == NULL)
        return;
    int u,visited[MAX] = {};
    JRB tmp,check1,check2;
    check1 = jrb_find_int(g.vertices,start);
    check2 = jrb_find_int(g.vertices,stop);
    if ((check1 == NULL) || (check2 == NULL && stop != -1))   
      return;
    
    Dllist queue,node;
    queue = new_dllist();
    dll_append(queue,new_jval_i(start));
    while (!dll_empty(queue)) 
      {
	node = dll_first(queue);
	u = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[u]) 
	  {
            func(g, u);
            visited[u] = 1;
	  }
        if (u == stop)
	  {
	    free_dllist(queue);
            return;
	  }	
	JRB u_node,v_connect_to_u;
	u_node = jrb_find_int(g.edges,u);
        if (u_node == NULL)
	  continue;
	v_connect_to_u = (JRB)jval_v(u_node->val);
        jrb_traverse(tmp,v_connect_to_u) 
	  if (!visited[tmp->key.i])
	    dll_append(queue,new_jval_i(tmp->key.i));
      }
   free_dllist(queue);
}


//DFS..........................................................................

void DFS(Graph g, int start, int stop, void (*func)(Graph, int))
{
    if (g.edges == NULL || g.vertices == NULL)
      return;
    int u,visited[MAX] = {};
    JRB tmp,check1,check2;
    check1 = jrb_find_int(g.vertices,start);
    check2 = jrb_find_int(g.vertices,stop);
    if ((check1 == NULL) || (check2 == NULL && stop != -1))   
      return;

    Dllist node,stack;
    stack = new_dllist();
    dll_append(stack,new_jval_i(start));
    while (!dll_empty(stack)) 
      {
        node = dll_last(stack);
	u = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[u]) 
	  {
            func(g, u);
            visited[u] = 1;
	  }
        if (u == stop)
	  {
            free_dllist(stack);
            return;
	  }
	JRB u_node,v_connect_to_u;
	u_node = jrb_find_int(g.edges, u);
        if (u_node == NULL)
	  continue;
	v_connect_to_u = (JRB)jval_v(u_node->val);
        jrb_traverse(tmp, v_connect_to_u) 
	  if (!visited[tmp->key.i])
	    dll_append(stack, new_jval_i(tmp->key.i));
      }
    free_dllist(stack);
}

//lay gia tri dinh id lon nhat.................................................

int get_graph_max_id(Graph g)
{
    if (g.edges == NULL || g.vertices == NULL)
        return 0;
    int key,max_id = 0;
    JRB tmp;
    jrb_traverse(tmp, g.vertices) 
    {
      key = jval_i(tmp->key);
      if (key > max_id)
        max_id = key;
    }
    return max_id;
}

//lay gia tri dinh id nho nhat.................................................

int get_graph_min_id(Graph g)
{
    if (g.edges == NULL || g.vertices == NULL)
        return 0;
    int key,min_id = 1000000;
    JRB tmp;
    jrb_traverse(tmp, g.vertices) 
    {
      key = jval_i(tmp->key);
      if (key < min_id)
        min_id = key;
    }
    return min_id;
}

// ktra chu trinh tu mot dinh .................................................

int is_cyclic_util(Graph g, int start)
{
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  int u,visited[MAX] = {};
  JRB tmp,check;
  check = jrb_find_int(g.vertices,start);
  if (check == NULL)   
    return 0;
  
  Dllist node,stack;
  stack = new_dllist();
  dll_append(stack,new_jval_i(start));
  while (!dll_empty(stack))
    {
      node = dll_last(stack);
      u = jval_i(node->val);
      dll_delete_node(node);
      
      if (!visited[u]) 
      visited[u] = 1;   
      JRB u_node,v_connect_to_u;
      u_node = jrb_find_int(g.edges,u);
      if (u_node == NULL)
	continue;
      v_connect_to_u = (JRB)(jval_v(u_node->val));
      jrb_rtraverse(tmp, v_connect_to_u)
	{
	  if (tmp->key.i == start)
	    {
	      free_dllist(stack);
	      return 1;
	    }
	  if (!visited[tmp->key.i])
	    dll_append(stack, new_jval_i(tmp->key.i));
	}
    }
  free_dllist(stack);
  return 0;
}

//ktra chu trinh do thi........................................................

int is_cyclic(Graph g)
{
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  JRB tmp;
  jrb_traverse(tmp, g.vertices) 
    if (is_cyclic_util(g, tmp->key.i))
      return 1;    
  return 0;
}

//do thi co huong kh co chu trinh ...............................................

int DAG(Graph g)
{
  int visited[MAX] = {};
  int i,n,output[100],u,v,start;
  Dllist stack,node;
  JRB tmp;
  jrb_traverse(tmp,g.vertices)
    {
      start = tmp->key.i;
      stack = new_dllist();
      dll_append(stack,new_jval_i(start));
      while(!dll_empty(stack))
	{
	  node = dll_last(stack);
	  u = jval_i(node->val);
	  dll_delete_node(node);
	  if(!visited[u])
	    {
	      visited[u]=1;
	      n=outDegree(g,u,output);
	      for(i=0;i<n;i++)
		{
		  v=output[i];
		  if(v==start) return 0;
		  if(!visited[v])
		    dll_append(stack,new_jval_i(v));
		}
	    }
	}
    }
  return 1;
}

// sap xe topo.................................................................

void TSort(Graph g, void (*func)(Graph, int))
{  
  if (g.edges == NULL || g.vertices == NULL)
    return;
  
  Dllist node,queue;
  JRB tmp;
  int u,v,w,i ;
  int tmp_out[MAX] = {};  
  int in_deg[MAX] = {};
  
  queue = new_dllist();
  jrb_traverse(tmp,g.vertices)
    if ((in_deg[tmp->key.i] = inDegree(g,tmp->key.i,tmp_out)) == 0) 
      dll_append(queue,new_jval_i(tmp->key.i));
  
  while (!dll_empty(queue))
    {
      node = dll_first(queue);
      u = jval_i(node->val);
      dll_delete_node(node);
      
      func(g,u);
      	
      int out_degree_u;
      int out_degree_node_u[MAX] = {};
      if ((out_degree_u = outDegree(g,u,out_degree_node_u)) != 0)
	for (i = 0; i < out_degree_u; ++i)
	  {
	    w = out_degree_node_u[i];
	    in_deg[w]--;
	    if (in_deg[w] == 0) 
	      dll_append(queue,new_jval_i(w));
	  }
    }
  free_dllist(queue);
}

//duong di ngan nhat...........................................................

int shortest_path(Graph g, int s, int t, int* path, int* length)
{
    if (g.edges == NULL || g.vertices == NULL || path == NULL || length == NULL)
        return INFINITY;
   
    int d[MAX];
    int u,i;
    int parent[MAX];
    Dllist queue ;
    JRB rnode;
    queue = new_dllist();
    for (i = 0; i <= MAX ; ++i) 
      {
	d[i] = INFINITY;
	parent[i] = UNDEFINED;
      }
    jrb_traverse(rnode,g.edges)
      {
	u = rnode->key.i;
	dll_append(queue,new_jval_i(u));
      }
    
    d[s] = 0;
    while (!dll_empty(queue))
      {
        {
	  Dllist tmp, min_node = dll_first(queue);
	  int min = jval_i(dll_first(queue)->val);
	  dll_traverse(tmp, queue) 
	    {
	      int tmp_node_i = tmp->val.i;
	      if (d[min] > d[tmp_node_i]) 
		{
		  min = tmp_node_i;
		  min_node = tmp;
		}
	    }
	  u = min;
	  dll_delete_node(min_node);
        }

        int output[MAX] = {};
        int out_degree_u;
	out_degree_u = outDegree(g,u,output);
	if (out_degree_u == 0)
	  continue;
	
	for (i = 0; i < out_degree_u; i++) 
	  {
            int v = output[i];
            int alt = d[u] + getEdgeValue(g,u,v);
            if (alt < d[v]) 
	      {
                d[v] = alt;
                parent[v] = u;
		  dll_append(queue,new_jval_i(v));
	      }
	  }
      }

    for (i = 0; i < MAX + 1; i++) 
      length[i] = d[i];
    /*
    if (parent[t] != -1) 
      {
	int j = 1;
        path[0] = t;
        while (1) 
	  {
            path[j] = parent[path[j - 1]];
            if (path[j] == s)
	      break;
            j++;
	  }
        path[++j] = -1;
      }
    */
     Dllist list=new_dllist(),dnode;
    u=t;
    int total = 0,v;
    while(u!=-1)
      {
	dll_append(list,new_jval_i(u));
	v=parent[u];
	u=v;
      }
    dll_rtraverse(dnode,list)
      path[total++]=jval_i(dnode->val);
    free_dllist(queue);
    return d[t];
}


/*
double shortest_path(Graph g,int s,int t,int *path,double *length)
{
  Dllist queue,dnode,minp;
  JRB rnode;
  int u,v,i,n,temp;
  double d[100];
  int output[100],parent[100];
  for(i=0;i<100;i++) d[i]=INFINITY;
  memset(parent,-1,sizeof(parent));
  queue=new_dllist();
  jrb_traverse(rnode,g.edges)
    {
      u=jval_i(rnode->key);
      dll_append(queue,new_jval_i(u));
    }
  d[s]=0;
  while(!dll_empty(queue))
    {
      minp=dll_first(queue);
      dll_traverse(dnode,queue)
	if(d[jval_i(dnode->val)]<d[jval_i(minp->val)]) 
	  minp=dnode;
      u=jval_i(minp->val);
      dll_delete_node(minp);
      n=outDegree(g,u,output);
      for(i=0;i<n;i++)
	{
	  v=output[i];
	  temp=d[u]+getEdgeValue(g,u,v);
	  if(temp<d[v])
	    {
	      d[v]=temp;
	      parent[v]=u;
	    }
	}
    }
  if(d[t]==INFINITY) return INFINITY; 
  Dllist list=new_dllist();
  u=t;
  int total=0;
  while(u!=-1)
    {
      dll_append(list,new_jval_i(u));
      v=parent[u];
      u=v;
    }
  dll_rtraverse(dnode,list)
    path[total++]=jval_i(dnode->val);
  *length=total;
  return d[t];
}
*/
