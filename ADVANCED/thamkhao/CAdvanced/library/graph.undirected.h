/*Le Vinh Thien - 8C*/
// Date Create: 30/5/2015
// Copyright @ 2015 by Le Vinh Thien - HUST
#include "lib/jrb.h"
#include "lib/dllist.h"
#define MAX 1000
/**/
typedef JRB Graph;
/*NGUYEN HAM*/
// tao moi mot do thi
Graph createGraph();
// them ket noi giua dinh v1 va v2 voi trong so value
void addEdge(Graph g, int v1, int v2, double value);
// lay trong so canh
double adjacent(Graph g, int v1, int v2);
// lay dinh ke
int getAdjacentVertices(Graph g, int v, int *output);
// xoa cay
void freeGraph(Graph g);
// in cay
void  printGraph(Graph g);
// duyet
void printVertex(int v);
// theo chieu rong
void BFS(Graph g, int start, int stop, void (*func)(int));
// theo chieu sau
void DFS(Graph g, int start, int stop, void (*func)(int));
// dem tong so dinh trong 1 lien thong
int totalConnected(Graph g, int start, int stop);
// di qua it dinh nhat
int UFS(Graph g, int s, int t, int* path, int*length);
// kiem tra co chu trinh
int DFSAII(Graph g);
// dijkstra tra ve INFINITI_VALUE neu khong ton tai duong di
double shortestPath(Graph g, int v1, int v2, int *path, int *a);
// dem so thanh phan lien thong
int countConnected(Graph g);
// dem so canh
int numEdges(Graph g);
/*GRAPH*/
// tao moi
Graph createGraph()
{
  return make_jrb();
}
// xem co lien ket giau 2 dinh
double adjacent(Graph g, int v1, int v2)
{
  JRB node, tree;
  node = jrb_find_int(g, v1);
  if (node == NULL)
    return 0;
  tree = jval_v(node->val);
  if (jrb_find_int(tree, v2) == NULL)
    return 0;
  node = jrb_find_int(tree, v2);
  return jval_d(node->val);
}
// them lien ket
void addEdge(Graph g, int v1, int v2, double value)
{
  if(v1 == v2) return;
  if(adjacent(g, v1, v2) != 0) return;
  JRB tree, node;
  node = jrb_find_int(g, v1);
  if(node == NULL)
	{
      tree = make_jrb();
      jrb_insert_int(g, v1, new_jval_v(tree));
      jrb_insert_int(tree,v2,new_jval_d(value));
	}
  else
	{
      tree = (JRB)jval_v(node->val);
      jrb_insert_int(tree,v2,new_jval_d(value));
	}
  node = jrb_find_int(g, v2);
  if(node == NULL)
	{
      tree = make_jrb();
      jrb_insert_int(g, v2, new_jval_v(tree));
      jrb_insert_int(tree,v1,new_jval_d(value));
	}
  else
	{
      tree = (JRB)jval_v(node->val);
      jrb_insert_int(tree,v1,new_jval_d(value));
	}

}
// lay cac dinh ke
int getAdjacentVertices(Graph g, int v, int *output)
{
  JRB node = jrb_find_int(g,v), tree, tmp;
  if (node == NULL) return -1;
  int i = 0;
  tree = (JRB)jval_v(node->val);
  jrb_traverse(tmp, tree) {
    output[i] = jval_i(tmp->key);
    i++;
  }
  return i;
}
// xoa graph
void freeGraph(Graph g)
{
  JRB node;
  jrb_traverse(node, g)
	{
      jrb_free_tree(jval_v(node->val));
	}
  jrb_free_tree(g);
}
// in
void  printGraph(Graph g)
{
  JRB tree, node, tmp;
  int k,i;
  jrb_traverse(node,g)
	{

      k =  jval_i(node->key);
      tmp = (JRB)jval_v(node->val);
      printf("%d : ", k);
      jrb_traverse(tree, tmp)
		{
          i = jval_i(tree->key);
          printf("%d     ",i);
		}
      printf("\n");
	}
}
/////////
void printVertex(int v)
{
  printf("%4d", v);
}

void BFS(Graph g, int start, int stop, void (*func)(int))
{
  Dllist queue = new_dllist(), node;
  int edge[MAX] = {}, i,u,v, out[MAX], n;
  dll_append(queue, new_jval_i(start));
  while(!dll_empty(queue))
    {
      node = dll_first(queue);
      u = jval_i(node->val);
      dll_delete_node(node);
      if(!edge[u])
        {
          func(u);
          edge[u] = 1;
          if(u == stop) return;
          n = getAdjacentVertices(g, u, out);
          for( i=0;i < n ; i++ )
            {
              v = out[i];
              if(!edge[v]) dll_append(queue, new_jval_i(v));
            }
           }
    }
}
// theo chieu sau
void DFS(Graph g, int start, int stop, void (*func)(int))
{
  Dllist queue = new_dllist(), node;
  int edge[MAX] = {}, i,u,v, out[MAX], n;
  dll_append(queue, new_jval_i(start));
  while(!dll_empty(queue))
    {
      node = dll_last(queue);
      u = jval_i(node->val);
      dll_delete_node(node);
      if(!edge[u])
        {
          func(u);
          edge[u] = 1;
          if(u == stop) return;
          n = getAdjacentVertices(g, u, out);
          for( i=0;i < n ; i++ )
            {
              v = out[i];
              if(!edge[v]) dll_append(queue, new_jval_i(v));
            }
        }
    }
}
// dem tong so dinh trong 1 ket noi
int totalConnected(Graph g, int start, int stop)
{
  Dllist queue = new_dllist(), node;
  int edge[MAX] = {}, i,u,v, out[MAX], n, tong = 0;
  dll_append(queue, new_jval_i(start));
  while(!dll_empty(queue))
    {
      node = dll_last(queue);
      u = jval_i(node->val);
      dll_delete_node(node);
      if(!edge[u])
        {
          tong++;
          edge[u] = 1;
          if(u == stop) return tong;
          n = getAdjacentVertices(g, u, out);
          for( i=0;i < n ; i++ )
            {
              v = out[i];
              if(!edge[v]) dll_append(queue, new_jval_i(v));
            }
        }
    }
  return tong;
}
// kiem tra chu trinh
void dfs(int v,int * nccv,int * ncce,int visited[],Graph g){
  int output[MAX];
  int i,u,n;
  visited[v]=1;
  (*nccv)++;
  n=getAdjacentVertices(g,v,output);
  for(i=0;i<n;i++){
    (*ncce)++;
    u=output[i];
    if(!visited[u])
      dfs(u,nccv,ncce,visited,g);
  }
}
int DFSAII(Graph g){
  int ncce=0,u;
  int nccv=0;
  int visited[1000]={0};
  int i,numberOfV=0;
  JRB node;
  jrb_traverse(node,g){
    numberOfV++;
  }
  jrb_traverse(node,g){
    u=node->key.i;
    if(!visited[u])
      {
        ncce=0;nccv=0;
        dfs(u,&nccv,&ncce,visited,g);
        if(ncce/2>=nccv){
          return 1;// co chu trinh
        }
      }
  }
  return 0;// khong co chu trinh
}
// dijkstra
#define INFINITIVE_VALUE 1000000
double shortestPath(Graph g, int v1, int v2, int *path, int *a)
{
  if(v1 == v2){
    *a = 0;
    return 0;
  }
  int visited[MAX], pre[MAX];
  double d[MAX], de, min;
  int vmin, v, u;
  JRB node, node2, tree;
  jrb_traverse(node, g){
    v = jval_i(node->key);
    visited[v] = 0;
    d[v] = INFINITIVE_VALUE;
  }
  // bắt đầu từ v1;
  d[v1] = 0;

  while (!visited[v2]){//lap toi khi v2 duoc tham
    min = INFINITIVE_VALUE;
    jrb_traverse(node, g){
      v = jval_i(node->key);
      if (!visited[v] && d[v]<min){
        min = d[v];
        vmin = v;
      }
    }
    v = vmin;
    visited[v] = 1;// v da duoc tham
    node = jrb_find_int(g, v);
    if( node != NULL ){
      tree = (JRB) jval_v(node->val);
      jrb_traverse(node2, tree){
        u = jval_i(node2->key);
        de = jval_d(node2->val);
        if (d[v]+de < d[u]){
          d[u] = d[v]+de;
          pre[u] = v;}
      }
    }
  }

  // find path
  *a=0;
  v = v2;
  path[*a] = v;
  do{
    v=pre[v];
    path[++(*a)] = v;
  }while( v != v1);
  return d[v2];
}
// qua it dinh nhat
int UFS(Graph g, int s, int t, int* path, int*length)
{
  int distance[MAX], min, w, total;
  int previous[MAX], tmp[MAX];
  int n, output[MAX], i, u, v, start;
  Dllist ptr, queue, node;

  for (i=0; i<1000; i++)
    distance[i] = INFINITIVE_VALUE;
  distance[s] = 0;
  previous[s] = s;

  queue = new_dllist();
  dll_append(queue, new_jval_i(s));

  while ( !dll_empty(queue) )
    {
      // get u from the priority queue
      min = INFINITIVE_VALUE;
      dll_traverse(ptr, queue)
        {
          u = jval_i(ptr->val);
          if (min > distance[u])
            {
              min = distance[u];
              node = ptr;
            }
        }
      dll_delete_node(node);

      if (u == t) break; // stop at t

      n = getAdjacentVertices(g, u, output);
      for (i=0; i<n; i++)
        {
          v = output[i];
          w = adjacent(g, u, v);
          if ( distance[v] > distance[u] + w )
            {
              distance[v] = distance[u] + w;
              previous[v] = u;
            }
          dll_append(queue, new_jval_i(v));
        }
    }
  total = distance[t];
  if (total != INFINITIVE_VALUE)
    {
      tmp[0] = t;
      n = 1;
      while (t != s)
        {
          t = previous[t];
          tmp[n++] = t;
        }
      for (i=n-1; i>=0; i--)
        path[n-i-1] = tmp[i];
      *length = n;
    }
  return total;
}
// dem so tahnh phan lien thong
int countConnected(Graph g)
{
  Dllist queue = new_dllist(), node;
  int visited[MAX], out[MAX];
  int i, u, v, n, total = 0;
  for(i=0 ;i<MAX ;i++ ) visited[i] = 0;
  JRB  tmp;
  jrb_traverse(tmp,g){
    u = tmp->key.i;
    if(!visited[u])
      {
        total++;
        dll_append(queue, new_jval_i(u));
        while(!dll_empty(queue))
          {
            node = dll_last(queue);
            v = jval_i(node->val);
            dll_delete_node(node);
            if(!visited[v])
              {
                visited[v] = 1;
                n = getAdjacentVertices(g, v, out);
                for( i=0;i < n ; i++ )
                  {
                    v = out[i];
                    if(!visited[v]) dll_append(queue, new_jval_i(v));
                  }
              }
          }
      }
  }
  return total;
}
// dem so canh
int numEdges(Graph g)
{
  JRB node, tree, tmp;
  int total;
  jrb_traverse(tree, g)
    {
      node = (JRB) jval_v(tree->val);
      jrb_traverse(tmp, node) total++;
    }
  return total/2;
}
