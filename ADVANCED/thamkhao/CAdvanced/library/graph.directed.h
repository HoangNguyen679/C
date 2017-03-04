/*Le Vinh Thien - 8C*/
// Date Create: 30/5/2015
// Copyright @ 2015 by Le Vinh Thien - HUST
#include "./lib/jrb.h"
#include "./lib/dllist.h"
#define MAX 1000
// data
typedef struct
{
  JRB edge;
  JRB vertices;
  int MAX_VERTICES;
} Graph;
///////////NGUYEN HAM////////////
// khoi tao
Graph createGraph();
// them dinh
void addVertex(Graph *g, int id, char *name);
// lay dinh
char *getVertex(Graph g, int id);
// lay trong so cua canh tu u->v
double hasEdge(Graph g, int u, int v);
// them canh tu u->v
void addEdge(Graph g, int u, int v, double value);
// cac dinh vao tu u;
int outdegree(Graph g, int u, int a[]);
// ra tu dinh u
int indegree(Graph g, int u, int a[]);
// in dinh
void  printVertex(Graph g);
// in canh
void  printEdge(Graph g);
// kiem tra chu trinh
int DAG(Graph graph);
/// cac kieu duyet do thi
/////////
void pVertex(int v);
// theo chieu rong
void BFS(Graph g, int start, int stop, void (*func)(int));
// theo chieu sau
void DFS(Graph g, int start, int stop, void (*func)(int));
// dem tong so dinh trong 1 ket noi bang DFS
int totalConnected(Graph g, int start, int stop);
// qua it dinh nhat
int UFS(Graph g, int s, int t, int* path, int*length);
// dem so tahnh phan lien thong
int countConnected(Graph g);
// dijkstra NOTICE!!!: phai dung UFS kiem tra xem co ton tai duong di trc.
double shortestPath(Graph g, int v1, int v2, int *path, int *a);
//////////////////////
// khoi tao
Graph createGraph()
{
  Graph g;
  g.edge = make_jrb();
  g.vertices = make_jrb();
  g.MAX_VERTICES = 0;
  return g;
}
// them dinh
void addVertex(Graph *g, int id, char *name)
{
  JRB find = jrb_find_int(g->vertices, id);
  if(find != NULL) return;
  else
    {
      jrb_insert_int(g->vertices, id, new_jval_s(name));
      g->MAX_VERTICES++;;
    }
}
// lay dinh;
char *getVertex(Graph g, int id)
{
  JRB find = jrb_find_int(g.vertices, id);
  if (find ==NULL) return "Not Found!\n";
  else return jval_s(find->val);
}
// kiem tra canh u->v
double hasEdge(Graph g, int u, int v)
{
  JRB node, tree;
  node = jrb_find_int(g.edge, u);
  if (node == NULL)
    return 0;
  tree = jval_v(node->val);
  if (jrb_find_int(tree, v) == NULL)
    return 0;
  node = jrb_find_int(tree, v);
  return jval_d(node->val);
}
// them canh
void addEdge(Graph g, int u, int v, double value)
{
  JRB find = jrb_find_int(g.vertices, u);
  if(find == NULL)
    {
      printf("Vertex %d not found!\n ", u);
      return;
    }
  find = jrb_find_int(g.vertices, v);
  if(find == NULL)
    {
      printf("Vertex %d not found!\n ", v);
      return;
    }
  if(hasEdge(g, u, v) != 0) return;
  JRB tree, node;
  node = jrb_find_int(g.edge, u);
  if(node == NULL)
	{
      tree = make_jrb();
      jrb_insert_int(g.edge, u, new_jval_v(tree));
      jrb_insert_int(tree, v, new_jval_d(value));
	}
  else
	{
      tree = (JRB)jval_v(node->val);
      jrb_insert_int(tree, v, new_jval_d(value));
	}
}
// cac dinh vao tu u;
int outdegree(Graph g, int u, int a[])
{
  JRB find = jrb_find_int(g.vertices, u), tmp;
  int d = 0;
  if(find == NULL) return 0;
  find = jrb_find_int(g.edge, u);
  if(find == NULL) return 0;
  find = (JRB)jval_v(find->val);
  jrb_traverse(tmp, find)
    {
      a[d++] = jval_i(tmp->key);
    }
  return d;
}
// ra tu dinh u
int indegree(Graph g, int u, int a[])
{
  JRB tmp,node,tree;
  int k, v, d=0;
  jrb_traverse(tree, g.edge)
    {
      v = jval_i(tree->key);
      if(hasEdge(g, v, u))
        {
          a[d++] = v;
        }
    }
  return d;
}
// in
void  printVertex(Graph g)
{
  JRB tree, node, tmp;
  int k,i;
  jrb_traverse(node,g.vertices)
	{

      k =  jval_i(node->key);
      printf("%d: %s\n",k,jval_s(node->val));
	}
}
void  printEdge(Graph g)
{
  JRB tree, node, tmp;
  int k,i;
  jrb_traverse(node,g.edge)
	{

      k =  jval_i(node->key);
      printf("%d: ",k);
      tmp = (JRB)jval_v(node->val);
      jrb_traverse(tree, tmp)
		{
          i = jval_i(tree->key);
          printf("%d     ",  i);
		}
      printf("\n");
	}
}
// kiem tra chu trinh
int DAG(Graph graph)
{
   int visited[MAX];
   int n, output[MAX], i, u, v, start;
   Dllist node, stack;
   JRB vertex;
   jrb_traverse(vertex, graph.vertices)
   {
       memset(visited, 0, sizeof(visited));
       start = jval_i(vertex->key);
       stack = new_dllist();
       dll_append(stack, new_jval_i(start));
       while ( !dll_empty(stack) )
       {
          node = dll_last(stack);
          u = jval_i(node->val);
          dll_delete_node(node);
          if (!visited[u])
          {
              visited[u] = 1;
              n = outdegree(graph, u, output);
              for (i=0; i<n; i++)
              {
                  v = output[i];
                  if ( v == start ) // la chu trinh
                     return 1;
                  if (!visited[v])
                     dll_append(stack, new_jval_i(v));
              }
          }
       }
   }
   return 0; // khong co chu trinh
}

/////////
void pVertex(int v)
{
  printf("%4d", v);
}
// theo chieu rong
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
          n = outdegree(g, u, out);
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
          n = outdegree(g, u, out);
          for( i=0;i < n ; i++ )
            {
              v = out[i];
              if(!edge[v]) dll_append(queue, new_jval_i(v));
            }
        }
    }
}
// tong so dinh trong 1 ket noi
// dem tong so dinh trong 1 ket noi bang DFS
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
          n = outdegree(g, u, out);
          for( i=0;i < n ; i++ )
            {
              v = out[i];
              if(!edge[v]) dll_append(queue, new_jval_i(v));
            }
        }
    }
  return tong;
}
//bin/cp
#define INFINITIVE_VALUE 1000000
// qua it dinh nhat
int UFS(Graph g, int s, int t, int* path, int*length)
{
  int distance[MAX], min, w,total;
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

      n = outdegree(g, u, output);
      for (i=0; i<n; i++)
        {
          v = output[i];
          w = hasEdge(g, u, v);
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
  jrb_traverse(tmp,g.vertices){
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
                n = outdegree(g, v, out);
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
// dijkstra
double shortestPath(Graph g, int v1, int v2, int *path, int *a)
{
  if(v1 == v2){
    *a = 0;
    return 0;
  }
  int visited[100], pre[100];
  double d[100], de, min;
  int vmin, v, u;
  JRB node, node2, tree;
  jrb_traverse(node, g.vertices){
    v = jval_i(node->key);
    visited[v] = 0;
    d[v] = INFINITIVE_VALUE;
  }
  // bắt đầu từ v1;
  d[v1] = 0;

  while (!visited[v2]){//lap toi khi v2 duoc tham
    min = INFINITIVE_VALUE;
    jrb_traverse(node, g.vertices){
      v = jval_i(node->key);
      if (!visited[v] && d[v]<min){
        min = d[v];
        vmin = v;
      }
    }
    v = vmin;
    visited[v] = 1;// v da duoc tham
    node = jrb_find_int(g.edge, v);
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
// thu tu topo
int topo(Graph g, int output[])
{
  //in[] là mảng chứa số cạnh trỏ vào 1 node tại 1 điểm
  int in[MAX], out[MAX], a[MAX];
  JRB node1, tree;
  int v, n, i, w, dem=0;
  Dllist node , queue;
  queue = new_dllist();
  // duyệt lấy mảng in[]
  jrb_traverse(node1, g.vertices){
    v = jval_i(node1->key);
    in[v] = indegree(g, v, a);
    if (in[v] == 0)
      dll_append(queue, new_jval_i(v));
  }
  while( !dll_empty(queue) ){
    node = dll_first(queue);
    v = jval_i(node->val);
    dll_delete_node(node);
    output[dem++]=v;
    n = outdegree(g, v, out);
    for (i=0; i<n; i++){
      w = out[i];
      in[w]--;   //giảm in[w] vì đã duyệt xong v
      if (in[w] == 0)	  dll_append(queue, new_jval_i(w));
    }
  }
  return dem;
}
