#include"w_graph.h"
graph createGraph() {
  graph g;
  g.edge=make_jrb();
  g.vertex=make_jrb();
  return g;
}
void addVertex(graph g, int v, char *name) {
  vertex_info info=(vertex_info)malloc(sizeof(vertex_info));
  info->name=(char *)malloc(100);
  strcpy(info->name, (const char*)name);
  info->len=(double *)malloc(sizeof(double));
  *(info->len)=INFINITIVE;
  jrb_insert_int(g.vertex, v, new_jval_v(info));
}
char *getVertex(graph g, int v) {
  JRB node=jrb_find_int(g.vertex, v);
  if (node==NULL)
    return NULL;
  else {
    vertex_info info=(vertex_info)jval_v(node->val);
    return info->name;
  }
}
double getVertexLen(graph g, int v) {
  JRB node=jrb_find_int(g.vertex, v);
  if (node==NULL)
    return INFINITIVE;
  else {
    vertex_info info=(vertex_info)jval_v(node->val);
    return *(info->len);
  }
}
void addVertexLen(graph g, int v, double len) {
  JRB node=jrb_find_int(g.vertex, v);
  if (node==NULL)
    printf("Vertex %d has not been added yet!\n", v);
  else {
    vertex_info info=(vertex_info)jval_v(node->val);
    *(info->len)=len;
  }
}
void addEdge(graph g, int v1, int v2, double len) {
  JRB node, tree;
  if ((node=jrb_find_int(g.edge, v1))==NULL) {
    tree=make_jrb();
    jrb_insert_int(g.edge, v1, new_jval_v(tree));
    jrb_insert_int(tree, v2, new_jval_d(len)); 
  }
  else {
    tree=(JRB)jval_v(node->val);
    if (jrb_find_int(tree, v2)==NULL)
      jrb_insert_int(tree, v2, new_jval_d(len)); 
  }
  if ((node=jrb_find_int(g.edge, v2))==NULL) {
    tree=make_jrb();
    jrb_insert_int(g.edge, v2, new_jval_v(tree));
    jrb_insert_int(tree, v1, new_jval_d(len)); 
  }
  else {
    tree=(JRB)jval_v(node->val);
    if (jrb_find_int(tree, v1)==NULL)
      jrb_insert_int(tree, v1, new_jval_d(len)); 
  }
}
void addVector(graph g, int v1, int v2, double len) {
  JRB node, tree;
  if ((node=jrb_find_int(g.edge, v1))==NULL) {
    tree=make_jrb();
    jrb_insert_int(g.edge, v1, new_jval_v(tree));
    jrb_insert_int(tree, v2, new_jval_d(len)); 
  }
  else {
    tree=(JRB)jval_v(node->val);
    if (jrb_find_int(tree, v2)==NULL)
      jrb_insert_int(tree, v2, new_jval_d(len)); 
  }
}
int adjacent(graph g, int v1, int v2) {
  return (isVector(g, v1, v2) || isVector(g, v2, v1));
} 
int isVector(graph g, int v1, int v2) {
  JRB node, tree;
  if ((node=jrb_find_int(g.edge, v1))!=NULL) { 
    tree=(JRB)jval_v(node->val);
    if (jrb_find_int(tree, v2)==NULL)
      return 0;
    else 
      return 1;
  }
  else 
    return 0;
}
int outDegree(graph g, int v, int *output) {
  JRB node, tree;
  int i=0;
  if ((node=jrb_find_int(g.edge, v))==NULL) 
    return 0;
  else {
    tree=(JRB)jval_v(node->val);
    jrb_traverse(node, tree) {
      output[i++]=jval_i(node->key);
    }
  }
  return i;
}
int inDegree(graph g, int v, int *output) {
  JRB node, tree;
  int i=0;
  jrb_traverse(node, g.edge) {
    tree=(JRB)jval_v(node->val);
    if (jrb_find_int(tree, v)!=NULL)
      output[i++]=jval_i(node->key);
  }
  return i;
}
int getAdjacentVertices(graph g, int v, int *output) {
  int outDgree[MAX_SIZE], inDgree[MAX_SIZE];
  int n_out, n_in, i, j, k, flag;
  n_out=outDegree(g, v, outDgree);
  n_in=inDegree(g, v, inDgree);
  for (i=0; i<n_out; i++)
    output[i]=outDgree[i];
  k=n_out-1;
  for (i=0; i<n_in; i++) {
    flag=0;
    for (j=0; j<n_out; j++)
      if (inDgree[i]==outDgree[j])
	flag=1;
    if (flag==0) {
      k++;
      output[k]=inDgree[i];
    }
  }
  return k+1;
}
void dropGraph(graph g) {
  JRB node;
  jrb_traverse(node, g.edge) {
    jrb_free_tree(jval_v(node->val));
  }
}
void BFS(graph g, int v1, int v2, void(*func)(int)) {
  Dllist queue=new_dllist();
  Dllist node;
  int visited[MAX_SIZE];
  int output[MAX_SIZE];
  int i, n, x;
  for (i=0; i<=MAX_SIZE; i++)
    visited[i]=0;
  dll_append(queue, new_jval_i(v1));
  while (!dll_empty(queue)) {
    node=dll_first(queue);
    x=jval_i(node->val);
    if (visited[x]==0)
      func(x);
    visited[x]=1;
    if (x==v2)
      break;
    n=outDegree(g, x, output);
    for (i=0; i<n; i++) 
      if (visited[output[i]]==0)
	dll_append(queue, new_jval_i(output[i]));
    dll_delete_node(node);
  }
}
void DFS(graph g, int v1, int v2, void(*func)(int)) {
  Dllist queue=new_dllist();
  Dllist node;
  int visited[MAX_SIZE];
  int output[MAX_SIZE];
  int i, n, x;
  for (i=0; i<=MAX_SIZE; i++)
    visited[i]=0;
  dll_append(queue, new_jval_i(v1));
  while (!dll_empty(queue)) {
    node=dll_last(queue);
    x=jval_i(node->val);
    if (visited[x]==0)
      func(x);
    visited[x]=1;
    if (x==v2)
      break;
    n=outDegree(g, x, output);
    for (i=0; i<n; i++) 
      if (visited[output[i]]==0)
	dll_append(queue, new_jval_i(output[i]));
    dll_delete_node(node);
  }
}
void graph_traverse(graph g, int v1, int v2, void(*func)(int)) {
  Dllist queue=new_dllist();
  Dllist node;
  int visited[MAX_SIZE];
  int output[MAX_SIZE];
  int i, n, x;
  for (i=0; i<=MAX_SIZE; i++)
    visited[i]=0;
  dll_append(queue, new_jval_i(v1));
  while (!dll_empty(queue)) {
    node=dll_first(queue);  
    x=jval_i(node->val);
    if (visited[x]==0)
      func(x);
    visited[x]=1;
    if (x==v2)  
      break;
    n=getAdjacentVertices(g, x, output);
    for (i=0; i<n; i++) 
      if (visited[output[i]]==0)
	dll_append(queue, new_jval_i(output[i]));
    dll_delete_node(node);
  }
}
int DAG(graph g) {
  Dllist queue=new_dllist();
  Dllist node;
  int visited[MAX_SIZE];
  int output[MAX_SIZE];
  int i, n, x;
  for (i=0; i<=MAX_SIZE; i++)
    visited[i]=0;
  dll_append(queue, g.edge->flink->key);
  while (!dll_empty(queue)) {
    node=dll_last(queue);
    x=jval_i(node->val);
    visited[x]=1;
    n=outDegree(g, x, output);
    for (i=0; i<n; i++) 
      if (visited[output[i]]==0)
	dll_append(queue, new_jval_i(output[i]));
      else return 0;
    dll_delete_node(node);
  }
  return 1;
}
void topologicalsort(graph g, int *output, int *n) {
  if (DAG(g)) {
    int inDgree;
    int visited[MAX_SIZE];
    int x[MAX_SIZE];
    int i=0, k=0, j, d;
    int list[MAX_SIZE];
    void func1(int x) {
      list[i]=x;
      visited[x]=0;
      i++;
    }
    graph_traverse(g, jval_i(g.edge->flink->key), -1, func1);
    *n=i;
    while (k!=*n) {
      for (i=0; i<*n; i++) {
	inDgree=inDegree(g, list[i], x);
	d=inDgree;
	for (j=0; j<d; j++) {
	  if (visited[x[j]]==1)
	    inDgree=inDgree-1;  
	}		     
	if (inDgree==0 && visited[list[i]]==0) {
	  output[k]=list[i];
	  k++;
	  visited[list[i]]=1;
	}
      } 
    }
  }
  else 
    printf("This is not DAG, cannot sort!\n");
}
double vectorLenght(graph g, int v1, int v2) {
  if (!isVector(g, v1, v2))
    return (double)INFINITIVE;
  else {
    JRB node=jrb_find_int(g.edge, v1);
    JRB tree=(JRB)jval_v(node->val);
    return jval_d(jrb_find_int(tree, v2)->val);
  }
}
double edgeLenght(graph g, int v1, int v2) {
  double v1_v2=vectorLenght(g, v1, v2);
  double v2_v1=vectorLenght(g, v2, v1);
  if (v1_v2<v2_v1)
    return v1_v2;
  else 
    return v2_v1;
}
void relax(graph g, int v, int *before, double *len) {
  int output[MAX_SIZE];
  int n, i, x;
  n=outDegree(g, v, output);
  for (i=0; i<n; i++)
    if ((x=len[v]+vectorLenght(g, v, output[i]))<len[output[i]]) {
      len[output[i]]=x;
      before[output[i]]=v;
    }
}
double single_pair(graph g, int v1, int v2, int *output, int *n) {
  int solved[MAX_SIZE];
  int before[MAX_SIZE];
  double len[MAX_SIZE];
  int closest;
  void func1(int x) {
    solved[x]=0;
    before[x]=v1;
    len[x]=INFINITIVE;
  }
  graph_traverse(g, jval_i(g.edge->flink->key), -1, func1);
  len[v1]=0;
  len[MAX_SIZE]=INFINITIVE;
  solved[v1]=1;
  relax(g, v1, before, len);
  while (closest!=MAX_SIZE) {
    closest=MAX_SIZE;
    void func(int x) {
      if (solved[x]==0 && len[closest]>=len[x])
	closest=x;
    }
    BFS(g, v1, -1, func);
    if (closest==-1)
      break;
    relax(g, closest, before, len);
    solved[closest]=1;
  }
  int i=v2;
  int arr[MAX_SIZE];
  *n=0;
  output[*n]=v2;
  *n=*n+1;
  while (i!=v1) {
    i=before[i];
    output[*n]=i;
    *n=*n+1;
  }
  for (i=0; i<*n; i++) 
    arr[*n-i-1]=output[i];
  for (i=0; i<*n; i++)
    output[i]=arr[i];
  return len[v2];
}
int getVertexKey(graph g, char *name) {
  JRB node;
  vertex_info info;
  jrb_traverse(node, g.vertex) {
    info=(vertex_info)jval_v(node->val);
    if (strcmp(info->name, name)==0)
      return jval_i(node->key);
  }
  return -1;
}
int newKey(graph g, char *name){
  int key;
  if ((key=getVertexKey(g, name))!=-1)
    return key;
  key=0;
  while (getVertex(g, key)!=NULL)
    key++;
  return key;
}
