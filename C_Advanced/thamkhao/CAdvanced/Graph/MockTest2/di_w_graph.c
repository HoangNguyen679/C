#include <stdlib.h>
#include <stdio.h>
#include "../lib/libfdr/jrb.h"
#include "../lib/libfdr/dllist.h"
#include "../lib/libfdr/jval.h"
#include "di_w_graph.h"

Graph create()
{
	Graph G;
	G.edges = make_jrb();
	G.vertices = make_jrb();
	G.MAX_VERTICES = 0;
	return G;
}

void addVertex(Graph *ptr_G, char *abbr, char *fullname) {
	JRB node;

	node = jrb_find_str(ptr_G->vertices, abbr);

	if(node == NULL) {
		jrb_insert_str(ptr_G->vertices, abbr, new_jval_s(fullname));
		ptr_G->MAX_VERTICES++;
	} else return;
}

char* getVertex(Graph G, char *abbr) {
	JRB node;

	node = jrb_find_str(G.vertices, abbr);

	if(node != NULL) {
		return jval_s(node->val);
	} else {
		return NULL;
	}
}

int hasEdge(Graph G, int v1, int v2) {
	JRB node, tree;

	// Find v1 in G
	node = jrb_find_int(G.vertices, v1);
	if(node == NULL) return 0;

	// Find v2 in G
	node = jrb_find_int(G.vertices, v2);
	if(node == NULL) return 0;

	node = jrb_find_int(G.edges, v1);
	if(node == NULL) return 0;
	else {
		// Adjacent tree of v1
		tree = (JRB)jval_v(node->val);
		// Find v2 in adjacent tree of v1
		node = jrb_find_int(tree, v2);

		if(node == NULL) return 0; // Not found
		else return 1; // Found
	}
}

int addEdge(Graph G, int v1, int v2, double w) {
	JRB node, tree;

	// Find v1 in G
	node = jrb_find_int(G.vertices, v1);
	if(node == NULL) return 0;

	// Find v2 in G
	node = jrb_find_int(G.vertices, v2);
	if(node == NULL) return 0;

	if(hasEdge(G, v1, v2)) return 1;

	node = jrb_find_int(G.edges, v1);
	if(node == NULL) {
		tree = make_jrb();
		jrb_insert_int(G.edges, v1, new_jval_v(tree));
		jrb_insert_int(tree, v2, new_jval_d(w));
	} else {
		tree = (JRB)jval_v(node->val);
		jrb_insert_int(tree, v2, new_jval_d(w));
	}
}

double getWeight(Graph G, int v1, int v2) {
	JRB node, tree;

	// Find v1 in G
	node = jrb_find_int(G.vertices, v1);
	if(node == NULL) return INFINITE_VALUE;

	// Find v2 in G
	node = jrb_find_int(G.vertices, v2);
	if(node == NULL) return INFINITE_VALUE;

	if(!hasEdge(G, v1, v2)) return INFINITE_VALUE;

	node = jrb_find_int(G.edges, v1);
	tree = (JRB)jval_v(node->val);

	node = jrb_find_int(tree, v2);
	return jval_d(node->val);
}

int outdegree(Graph G, int v, int *output) {
	JRB node, tree, tmp;
	int count = 0;

	node = jrb_find_int(G.vertices, v);
	if(node == NULL) return 0;

	node = jrb_find_int(G.edges, v);
	if(node == NULL) return 0;
	else {
		tree = (JRB)jval_v(node->val);
		jrb_traverse(tmp, tree) {
			output[count++] = jval_i(tmp->key);
		}
	}

	return count;
}

int indegree(Graph G, int v, int *output) {
	JRB node, tree, tmp;
	int key, count = 0;

	node = jrb_find_int(G.vertices, v);
	if(node == NULL) return 0; 

	jrb_traverse(tmp, G.edges) {
		key = jval_i(tmp->key);
		if(hasEdge(G, key, v)) {
			output[count++] = key;
		}
	}

	return count;
}

void drop(Graph *ptr_G) {
	JRB tmp;

	jrb_traverse(tmp, ptr_G->edges) {
		jrb_free_tree(jval_v(tmp->val));
	}

	jrb_free_tree(ptr_G->edges);
	jrb_free_tree(ptr_G->vertices);
}

void BFT(Graph G, int start, int stop, void (*visit)(int)) {
	Dllist Q, node;
	int i, k, n, u, v;

	n = getHighestID(G) + 1;

	/**
	 * Array storing visited status
     * Index of array = key of node
     * 0 - not visited
     * 1 - visited 
     */
     int *visited = (int*)malloc(sizeof(int) * n);
     for(i = 0; i < n; i++)
     	visited[i] = 0;

     int *out = (int*)malloc(sizeof(int) * n);

     Q = new_dllist();

     dll_append(Q, new_jval_i(start));

     while(!dll_empty(Q)) {
     	node = dll_first(Q);
     	u = jval_i(node->val);
     	dll_delete_node(node);

     	if(visited[u] == 0) {
     		visit(u);
     		visited[u] = 1;

     		if(u == stop) return;

     		k = outdegree(G, u, out);

     		for(i = 0; i < k; i++) {
     			v = out[i];

     			if(visited[v] == 0)
     				dll_append(Q, new_jval_i(v));
     		}
     	}
     }

     free(visited);
     free(out);
 }

 void DFT(Graph G, int start, int stop, void (*visit)(int)) {
 	Dllist S, node;
 	int i, k, n, u, v;

 	n = getHighestID(G) + 1;

	/**
	 * Array storing visited status
     * Index of array = key of node
     * 0 - not visited
     * 1 - visited 
     */
     int *visited = (int*)malloc(sizeof(int) * n);
     for(i = 0; i < n; i++)
     	visited[i] = 0;

     int *out = (int*)malloc(sizeof(int) * n);

     S = new_dllist();

     dll_append(S, new_jval_i(start));

     while(!dll_empty(S)) {
     	node = dll_last(S);
     	u = jval_i(node->val);
     	dll_delete_node(node);

     	if(visited[u] == 0) {
     		visit(u);
     		visited[u] = 1;

     		if(u == stop) return;

     		k = outdegree(G, u, out);

     		for(i = 0; i < k; i++) {
     			v = out[i];

     			if(visited[v] == 0)
     				dll_append(S, new_jval_i(v));
     		}
     	}
     }

     free(visited);
     free(out);
 }

 int isDAG(Graph G) {
 	Dllist S, node;
 	JRB vertex;
 	int i, k, n, u, v, start;

 	n = getHighestID(G) + 1;

 	int *visited = (int*)malloc(sizeof(int) * n);
 	for(i = 0; i < n; i++)
 		visited[i] = 0;

 	int *out = (int*)malloc(sizeof(int) * n);

 	jrb_traverse(vertex, G.vertices) {
 		// Starting vertex
 		start = jval_i(vertex->key);
 		// Create stack S
 		S = new_dllist();
 		// Push 'start' into stack S
 		dll_append(S, new_jval_i(start));

 		while(!dll_empty(S)) {
 			node = dll_last(S);
 			u = jval_i(node->val);
 			dll_delete_node(node);

 			if(visited[u] == 0) {
 				visited[u] = 1;

 				k = outdegree(G, u, out);

 				for(i = 0; i < k; i++) {
 					v = out[i];

 					if(v == start) return 0; // has cycle
 					if(visited[v] == 0)
 						dll_append(S, new_jval_i(v));
 				}
 			}
 		}
 	}

 	free(visited);
 	free(out);

 	return 1; // no cycle, is DAG
 }

 void showVertices(Graph G) {
 	JRB tmp;

 	jrb_traverse(tmp, G.vertices) {
 		printf("%s - \"%s\"\n", jval_s(tmp->key), jval_s(tmp->val));
 	}
 }

 void showEdges(Graph G) {
 	JRB tree, tmp, node;
 	int i, key;

 	jrb_traverse(node, G.edges) {
 		printf("%d:", jval_i(node->key));
 		tree = (JRB)jval_v(node->val);

 		jrb_traverse(tmp, tree) {
 			printf("%4d", jval_i(tmp->key));
 		}
 		printf("\n");
 	} 
 }

 void TSort(Graph G, void (*visit)(int)) {
 	Dllist Q, node;
 	JRB tmp;
 	int i, n, u, v, k, w;

 	n = getHighestID(G) + 1;

 	int *outdegree_node = (int*)malloc(sizeof(int) * n);
 	int *indegree_node = (int*)malloc(sizeof(int) * n);
 	int *indegree_ar = (int*)malloc(sizeof(int) * n);

 	Q = new_dllist();

 	jrb_traverse(tmp, G.vertices) {
 		v = jval_i(tmp->key);
 		indegree_ar[v] = indegree(G, v, indegree_node);
 		if(indegree_ar[v] == 0)
 			dll_append(Q, new_jval_i(v));
 	}

 	while(!dll_empty(Q)) {
 		node = dll_first(Q);
 		u = jval_i(node->val);
 		dll_delete_node(node);

 		visit(u);


 		k = outdegree(G, u, outdegree_node);

 		if(k != 0) {
 			for(i = 0; i < k; i++) {
 				w = outdegree_node[i];
 				indegree_ar[w]--;

 				if(indegree_ar[w] == 0)
 					dll_append(Q, new_jval_i(w));
 			}
 		}
 	}

 	free(indegree_node);
 	free(indegree_ar);
 	free(outdegree_node);
 }

 int getHighestID(Graph G) {
 	JRB node;
 	int max = -1000;
 	int v;

 	jrb_traverse(node, G.vertices) {
 		v = jval_i(node->key);
 		if(v >= max)
 			max = v;
 	}

 	return max;
 }

 double shortestPath(Graph graph, int s, int t, int* path, double* length) {
  if (graph.edges == NULL || graph.vertices == NULL)
    return INFINITE_VALUE;

  if (path == NULL || length == NULL)
    return INFINITE_VALUE;

  int i, max_id = getHighestID(graph);
  double *dist = malloc(sizeof(double) * (max_id + 1));  // free ?
  int *prev = malloc(sizeof(int) * (max_id + 1));
  if (!dist || !prev) {
    fprintf(stderr, "%s%s:%d\n", "Allocated Failed in ", __FILE__, __LINE__);
    exit(1);
  }

  Dllist queue = new_dllist();   // free ?

  for (i = 0; i <= max_id ; ++i) {
    if (i != s) {
      dist[i] = INFINITE_VALUE;
      prev[i] = UNDEFINED;
    }
    dll_append(queue, new_jval_i(i));
  }

  dist[s] = 0;

  while (!dll_empty(queue)) {
    // extract min
    int u;
    {
      Dllist tmp, min_node = dll_first(queue);
      int min = jval_i(dll_first(queue)->val);
      dll_traverse(tmp, queue) {
        int tmp_node_i = jval_i(tmp->val);
        if (dist[min] > dist[tmp_node_i]) {
          min = tmp_node_i;
          min_node = tmp;
        }
      }
      u = min;
      dll_delete_node(min_node);
    }

    //
    int *out_degree_u_list = malloc(sizeof(int) * (max_id + 1));  // free ?
    if (!out_degree_u_list) {
      fprintf(stderr, "%s%s:%d\n", "Allocated Failed in ", __FILE__, __LINE__);
      exit(1);
    }
    int out_degree_u = outdegree(graph, u, out_degree_u_list);
    if (out_degree_u == 0)
      continue;

    int i;
    for (i = 0; i < out_degree_u; i++) {
      int v = out_degree_u_list[i];
      double alt = dist[u] + getWeight(graph, u, v);
      if (alt < dist[v]) {
        dist[v] = alt;
        prev[v] = u;
        dll_append(queue, new_jval_i(v));
      }

    }
    // free(out_degree_u_list);

  }

  for (i = 0; i <= max_id + 1; i++) {
    length[i] = dist[i];
  }

  if (prev[t] != -1) {
    int j = 1;
    path[0] = t;
    while (1) {
      path[j] = prev[path[j - 1]];
      if (path[j] == s)
        break;
      j++;
    }
    path[++j] = -1;
  }
  
  free_dllist(queue);
  free(dist);
  free(prev);

  return dist[t];
}