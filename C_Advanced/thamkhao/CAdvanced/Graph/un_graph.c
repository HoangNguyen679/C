#include <stdlib.h>
#include <stdio.h>
#include "lib/libfdr/jrb.h"
#include "lib/libfdr/dllist.h"
#include "lib/libfdr/jval.h"
#include "un_graph.h"

#define INFINITE_VALUE 10000000

Graph create() {
  Graph G = make_jrb();
  return G;
}

void addEdge(Graph G, int v1, int v2) {
  if (v1 == v2) return;
  if (isAdjacent(G, v1, v2)) return;

  JRB node, tree;

  // Add v2 to adjacent tree of v1
  node = jrb_find_int(G, v1);
  if(node == NULL) {
    tree = create();
    jrb_insert_int(G, v1, new_jval_v(tree));
    jrb_insert_int(tree, v2, new_jval_i(1));
  } else {
    tree = (JRB)jval_v(node->val);
    jrb_insert_int(tree, v2, new_jval_i(1));
  }

  // Add v1 to adjacent tree of v2
  node = jrb_find_int(G, v2);
  if(node == NULL) {
    tree = create();
    jrb_insert_int(G, v2, new_jval_v(tree));
    jrb_insert_int(tree, v1, new_jval_i(1));
  } else {
    tree = (JRB)jval_v(node->val);
    jrb_insert_int(tree, v1, new_jval_i(1));
  }
}

int isAdjacent(Graph G, int v1, int v2) {
  JRB node, tree;
  // Find v1 in G
  node = jrb_find_int(G, v1);
  if (node == NULL) // if v1 not in G
  {
    return 0;
  } else { 
    // Get adjacent tree of v1
    tree = jval_v(node->val);
    // Find v2 in adjacent tree of v1
    node = jrb_find_int(tree, v2);
    if (node == NULL) // if v2 not in adjacent tree of v1
    {
      return 0;
    } else {
      return 1;
    }
  }
}

int getAdjacentNodes(Graph G, int v, int *output) {
  int count = 0;
  JRB node, tree, tmp;

  node = jrb_find_int(G, v);
  if(node == NULL) return 0;

  tree = (JRB)jval_v(node->val);

  jrb_traverse(tmp, tree)
    output[count++] = jval_i(tmp->key);

  return count;
}

void drop(Graph *ptr_G) {
  JRB G = (JRB)*ptr_G;
  JRB tmp;
  jrb_traverse(tmp, G)
    jrb_free_tree(jval_v(tmp->val));
  jrb_free_tree(G);
  *ptr_G = NULL;
}

int getNumNode(Graph G){
  int count = 0;
  JRB tmp;

  jrb_traverse(tmp, G)
      count++;

  return count;
}

int getNumEdge(Graph G)
{
  int count = 0;
  JRB node, tree, tmp;

  jrb_traverse(tree, G)
    {
      node = (JRB) jval_v(tree->val);
      jrb_traverse(tmp, node) count++;
    }

  return count/2;
}

void BFT(Graph G, int start, int stop, void (*visit)(Dllist)) {  
  Dllist Q, node;
  int i, n, u, v;

  int numNode = getNumNode(G);
  
  /**
   * Array storing visited status
   * Index of array = key of node
   * 0 - not visited
   * 1 - visited 
   */
  int *visited = (int*)malloc(sizeof(int)*numNode);

  for(i = 0; i < numNode; i++) {
    visited[i] = 0;
  }

  /**
   * Array storing adjacent nodes of vertex
   * Value of array = key of node
   */
  int *adj = (int*)malloc(sizeof(int)*numNode);

  Q = new_dllist(); // create queue Q
  dll_append(Q, new_jval_i(start)); // enqueue starting node

  while(!dll_empty(Q)) {
    node = dll_first(Q); // dequeue Q
    u = jval_i(node->val);

    dll_delete_node(node);
    
    if( visited[u] == 0 ) { // if not visited
      visit(node);
      visited[u] = 1;

      if(u == stop) return;

      n = getAdjacentNodes(G, u, adj);

      for(i = 0; i < n; i++) {
        v = adj[i];
        if(visited[v] == 0) {
          dll_append(Q, new_jval_i(v));
        }
      }
    }
  }

  free(visited);
  free(adj);
  free_dllist(Q);
}

void DFT(Graph G, int start, int stop, void (*visit)(Dllist)) {
  Dllist S, node;
  int i, n, u, v;
  
  int numNode = getNumNode(G);
  
  /**
   * Array storing visited status
   * Index of array = key of node
   * 0 - not visited
   * 1 - visited 
   */
  int *visited = (int*)malloc(sizeof(int)*numNode);
  for(i = 0; i < numNode; i++) {
      visited[i] = 0;
  }

  /**
   * Array storing adjacent nodes of vertex
   * Value of array = key of node
   */
  int *adj = (int*)malloc(sizeof(int)*numNode);

  S = new_dllist(); // create stack S
  dll_append(S, new_jval_i(start)); // push starting node into S

  while(!dll_empty(S)) {
    node = dll_last(S); // pop S
    u = jval_i(node->val);

    if(visited[u] == 0) {
      visit(node);
      visited[u] = 1;

      if (u == stop) return;

      n = getAdjacentNodes(G, u, adj);
      for(i = 0; i < n; i++) {
        v = adj[i];
        if(visited[v] == 0) {
          dll_append(S, new_jval_i(v));
        }
      }
    }
  }

  free(visited);
  free(adj);
}

void showGraph(Graph G) {
  JRB tree, tmp, tmp_;
  int key, key_;

  jrb_traverse(tmp, G) {
    key = jval_i(tmp->key);
    printf("%d:", key);

    tree = (JRB)jval_v(tmp->val);
    jrb_traverse(tmp_, tree) {
      key_ = jval_i(tmp_->key);
      printf("%3d", key_);
    }

    printf("\n");
  }
}

//---------------------------------------------------------------------

void addEdge2(Graph G, int v1, int v2, double w) {
  if (v1 == v2) return;
  if (isAdjacent(G, v1, v2)) return;

  JRB node, tree;

  // Add v2 to adjacent tree of v1
  node = jrb_find_int(G, v1);
  if(node == NULL) {
    tree = create();
    jrb_insert_int(G, v1, new_jval_v(tree));
    jrb_insert_int(tree, v2, new_jval_d(w));
  } else {
    tree = (JRB)jval_v(node->val);
    jrb_insert_int(tree, v2, new_jval_d(w));
  }

  // Add v1 to adjacent tree of v2
  node = jrb_find_int(G, v2);
  if(node == NULL) {
    tree = create();
    jrb_insert_int(G, v2, new_jval_v(tree));
    jrb_insert_int(tree, v1, new_jval_d(w));
  } else {
    tree = (JRB)jval_v(node->val);
    jrb_insert_int(tree, v1, new_jval_d(w));
  }
}

double getWeight(Graph G, int v1, int v2) {
  JRB node, tree;

  // Find v1 in G
  node = jrb_find_int(G, v1);
  if(node == NULL) return INFINITE_VALUE;

  // Find v2 in G
  node = jrb_find_int(G, v2);
  if(node == NULL) return INFINITE_VALUE;

  if(!isAdjacent(G, v1, v2)) return INFINITE_VALUE;

  node = jrb_find_int(G, v1);
  tree = (JRB)jval_v(node->val);

  node = jrb_find_int(tree, v2);
  return jval_d(node->val);
}