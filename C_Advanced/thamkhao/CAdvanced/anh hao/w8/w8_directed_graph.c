#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ARRSIZE 	10
#define RANGE 		10
#define EPSILON 	1E-7
#define MAX_BUFF 	512

#define INITIAL_SIZE 		10
#define INCREMENTAL_SIZE 	5
#define BUFF_SIZE			80

#define DATA_FILENAME "data.txt"

#define NEWLINE 	printf("%s", "\n");

enum bool {false, true};
typedef int bool;

#include "jrb.h"
#include "dllist.h"
#include "fields.h"
// Extend Dll function
int dll_find(Dllist l, int key)
{
	Dllist temp;
	dll_traverse(temp, l)
	{
		if (key == jval_i(temp->val))
		{
			return 1;
		}
	}
	return 0;
}

typedef struct 
{
	JRB vertices;
	JRB edges;
} Graph;
//---------------------------------------------------------
Graph 	CreateGraph(void);
void 	AddVertice(Graph G, int id, char *name);
void 	AddEdge(Graph G, int v1, int v2, float weight, bool indirected);
int 	IsAdjacent(Graph G, int v1, int v2);
int 	GetAdjacentVerticle(Graph G, int v, int *output);
void 	ShowAdjacentVerticle(Graph G, int v);
int 	Indegree(Graph graph, int v, int* output);
int 	Outdegree(Graph graph, int v, int* output);
void 	DropGraph(Graph G);
//---------------------------------------------------------
// Travesral functions
int 	Visit(Graph G, int v);
void 	BFS(Graph G, int start, int stop, int(*Visit)(Graph, int));
void 	DFS(Graph G, int start, int stop, int(*Visit)(Graph, int));
int 	isDAG(Graph G);
void 	TopologicalSort(Graph G);
void 	ReadData(Graph G, char *fileName);
//---------------------------------------------------------
int main(int argc, char const *argv[])
{
	// Init Graph
	Graph g;
	g = CreateGraph();

	ReadData(g, DATA_FILENAME);

/*
	// Create Vertices
	AddVertice(myGraph, 0, "V0");
	AddVertice(myGraph, 1, "V1");
	AddVertice(myGraph, 2, "V2");
	AddVertice(myGraph, 3, "V3");
	AddVertice(myGraph, 4, "V4");
	AddVertice(myGraph, 5, "V5");
	AddVertice(myGraph, 6, "V6");
	AddVertice(myGraph, 7, "V7");
	AddVertice(myGraph, 8, "V8");
	AddVertice(myGraph, 9, "V9");

	//Create Edges
	AddEdge(myGraph, 0, 1, 0.0, false);
	AddEdge(myGraph, 0, 4, 0.0, false);
	AddEdge(myGraph, 0, 6, 0.0, false);

	AddEdge(myGraph, 1, 2, 0.0, false);

	AddEdge(myGraph, 2, 5, 0.0, false);
	AddEdge(myGraph, 2, 7, 0.0, false);

	AddEdge(myGraph, 3, 4, 0.0, false);
	AddEdge(myGraph, 3, 8, 0.0, false);

	AddEdge(myGraph, 4, 5, 0.0, false);

	AddEdge(myGraph, 5, 0, 0.0, true);

	AddEdge(myGraph, 6, 2, 0.0, false);
	AddEdge(myGraph, 6, 3, 0.0, false);

	AddEdge(myGraph, 7, 8, 0.0, false);

	AddEdge(myGraph, 9, 6, 0.0, false);
	*/

	/*
	AddVertice(g, 0, "CS102"); AddVertice(g, 1, "CS140");
	AddVertice(g, 2, "CS160"); AddVertice(g, 3, "CS302");
	AddVertice(g, 4, "CS311"); AddVertice(g, 5, "MATH300");

	AddEdge(g, 0, 1, 0.0, false); AddEdge(g, 0, 2, 0.0, false);
	AddEdge(g, 1, 3, 0.0, false); AddEdge(g, 5, 4, 0.0, false); AddEdge(g, 3, 4, 0.0, false);
	*/


	//printf("0");
	// jrb_traverse(node, g.vertices)
	// {
	// 	printf("%s*", jval_s(node->val));
	// }
	NEWLINE

	// jrb_traverse(node, g.edges)
	// {
	// 	JRB as;
	// 	JRB tree = (JRB)jval_v(node->val);
	// 	jrb_traverse(as, tree)
	// 		printf("%d*", jval_i(as->key));
	// }
	//BFS(g, 1, -1, Visit);
	// NEWLINE
	//DFS(g, 0, -1, Visit);

	NEWLINE
	printf("\nDAG?: %d\n", isDAG(g));

	// int out[10];
	// int i;
	// for (i = 0; i < Indegree(myGraph, 1, out); ++i)
	// {
	// 	printf("%d-", out[i]);
	// }
	
	TopologicalSort(g);


	// Free and Exit
	DropGraph(g);
	return 0;
}
//---------------------------------------------------------
Graph CreateGraph(void)
{
	Graph G;
	G.vertices = make_jrb();
	G.edges = make_jrb();
	if (G.vertices == NULL || G.edges == NULL)
	{
		printf("%s\n", "Could not create graph! ERROR: make_jrb failed!");
	}
	return G;
}
//---------------------------------------------------------
void DropGraph(Graph G)
{	
	JRB node;
	
	jrb_free_tree(G.vertices);

	jrb_traverse(node, G.edges)
		jrb_free_tree( jval_v(node->val) );
}
//---------------------------------------------------------
void AddVertice(Graph G, int id, char *name)
{
	JRB node = make_jrb();
	node = jrb_find_int(G.vertices, id);

	if (node == NULL)
	{
		jrb_insert_int(G.vertices, id, new_jval_s(strdup(name)));
	}
	else
	{
		strcpy(jval_s(node->val), name);
	}
}
//---------------------------------------------------------
void AddEdge(Graph G, int v1, int v2, float weight, bool indirected)
{
	JRB tree = make_jrb();

	JRB node = make_jrb();
	node = jrb_find_int(G.edges, v1);
	
	if (node == NULL)
	{
		jrb_insert_int(G.edges, v1, new_jval_v(tree));
		jrb_insert_int(tree, v2, new_jval_f(weight));
	}
	else
	{
		tree = (JRB)jval_v(node->val);
		if (jrb_find_int(tree, v2) == NULL)
		{
			jrb_insert_int(tree, v2, new_jval_f(weight));
		}
	}

	if (indirected)
	{
		AddEdge(G, v2, v1, weight, false);
	}

	return;
}
//---------------------------------------------------------
int GetAdjacentVerticle(Graph G, int v, int *output)
{
	JRB node;
	node = jrb_find_int(G.edges, v);

	if (node == NULL)
	{
		//printf("%s\n", "Vertex does not exist!");
		return 0;
	}

	JRB tree = (JRB)jval_v(node->val);
	int total = 0;
	jrb_traverse(node, tree)
		output[total++] = jval_i(node->key);

	return total;
}
//---------------------------------------------------------
void ShowAdjacentVerticle(Graph G, int v)
{
	int output[ARRSIZE];
	int n = GetAdjacentVerticle(G, 1, output);

	if (n == 0) 
		printf("No adjacent vertices\n");
	else 
	{
		printf("%s %d: \n", "Vertice", v);
		printf("Number of adjacent: %d\n", n);
		printf("Adjacent vertices:");
		int i;
		for (i=0; i< n; i++) 
			printf("%5d", output[i]);
	}
	printf("%s\n", "");
}
//---------------------------------------------------------
int Visit(Graph G, int v)
{
	JRB node;
	node = jrb_find_int(G.vertices, v);
	printf("%s ", jval_s(node->val));
	return 0;
}
//---------------------------------------------------------
void BFS(Graph G, int start, int stop, int(*Visit)(Graph, int))
{
	Dllist l = new_dllist();
	Dllist visited = new_dllist();

	dll_append(l, new_jval_i(start));

	while (!dll_empty(l))
	{
		int u = jval_i(dll_first(l)->val);
		dll_delete_node(dll_first(l));

		if (!dll_find(visited, u))
		{
			// printf("%d ", u);
			Visit(G, u);
			if (stop == u)
				return;

			dll_append(visited, new_jval_i(u));
			
			int output[ARRSIZE];
			int n = GetAdjacentVerticle(G, u, output);
			if (n != 0)
			{
				int i;
				for (i = 0; i < n; i++) 
				{
					if (!dll_find(visited, output[i]))
					{
						dll_append(l, new_jval_i(output[i]));
					}
				}
			}
		}
	}

	free_dllist(visited);
}
//---------------------------------------------------------
void DFS(Graph G, int start, int stop, int(*Visit)(Graph, int))
{
	// Stack
	Dllist l = new_dllist();
	// List of vertices which are visited
	Dllist visited = new_dllist();

	// Check if start vertex is exists
	JRB find = jrb_find_int(G.vertices, start);
	if (find == NULL)
	{
		printf("Start vertex is not vaild! Vertex does not exists!\n");
		return;
	}

	// First element of stack
	dll_append(l, new_jval_i(start));

	while (!dll_empty(l))
	{
		int u = jval_i(dll_last(l)->val);
		dll_delete_node(dll_last(l));

		if (!dll_find(visited, u))
		{
			//visit
			//printf("%d ", u);
			Visit(G, u);

			// Set stop = -1 if you want to traverse all vertices
			if (stop == u)
				return;

			dll_append(visited, new_jval_i(u));
			
			int output[ARRSIZE];
			int n = GetAdjacentVerticle(G, u, output);
			if (n != 0)
			{
				int i;
				for (i = n-1; i >= 0; i--) 
				{
					if (!dll_find(visited, output[i]))
					{
						dll_append(l, new_jval_i(output[i]));
					}
				}
			}
		}
	}

	free_dllist(visited);
}
//---------------------------------------------------------
int isDAG(Graph G)
{
	Dllist arbitraryVertice = new_dllist();

	JRB node;
	jrb_traverse(node, G.vertices)
	{
		printf("%d*", jval_i(node->key));
		dll_append(arbitraryVertice, (node->key));
	}

	NEWLINE
	while (!dll_empty(arbitraryVertice))
	{
		Dllist l = new_dllist();
		int source = jval_i(dll_first(arbitraryVertice)->val);
		dll_append(l, new_jval_i(source));
		dll_delete_node(dll_first(arbitraryVertice));
		
		Dllist visited = new_dllist();
		while (!dll_empty(l))
		{
			int u = jval_i(dll_last(l)->val);
			dll_delete_node(dll_last(l));

			if (!dll_find(visited, u))
			{
				dll_append(visited, new_jval_i(u));
				
				int output[ARRSIZE];
				int n = GetAdjacentVerticle(G, u, output);
				if (n != 0)
				{
					int i;
					for (i = n-1; i >= 0; i--) 
					{
						if (!dll_find(visited, output[i]))
						{
							dll_append(l, new_jval_i(output[i]));
						}
						else if (output[i] == source)
						{
							free_dllist(visited);
							free_dllist(l);
							free_dllist(arbitraryVertice);
							return 1;
						}
					}
				}
			}
		}
	}

	free_dllist(arbitraryVertice);
	return 0;
}
//---------------------------------------------------------
int Indegree(Graph G, int v, int* output)
{
	JRB findv;
	findv = jrb_find_int(G.vertices, v);
	int total = 0;

	if (findv == NULL)
	{
		//printf("%s\n", "Vertex does not exist!");
		return 0;
	}

	JRB p;// = make_jrb();
	JRB node;// = make_jrb();

	jrb_traverse(node, G.edges)
	{
		JRB tree = (JRB)jval_v(node->val);
		jrb_traverse(p, tree)
		{
			if (jval_i(p->key) == v)
			{
				if (output == NULL) total++;
				else output[total++] = jval_i(node->key);
			}
		}
	}

	return total;
}
//---------------------------------------------------------
int Outdegree(Graph G, int v, int* output)
{
	JRB node;
	node = jrb_find_int(G.edges, v);

	if (node == NULL)
	{
		//printf("%s\n", "Vertex does not exist!");
		return 0;
	}

	JRB tree = (JRB)jval_v(node->val);
	int total = 0;
	jrb_traverse(node, tree)
		output[total++] = jval_i(node->key);

	return total;
}
//---------------------------------------------------------
void TopologicalSort(Graph G)
{
	// if (isDAG(G))
	// {
	// 	printf("Can not make topological sort\n"); 
	// 	return; 
	// }

	Dllist tpQueue = new_dllist();

	JRB indegree = make_jrb();
	if (indegree == NULL)
	{
		printf("Make JRB false for indegree!");
		return;
	}

	JRB node;
	jrb_traverse(node, G.vertices)
	{
		int iv = Indegree(G, jval_i(node->key), NULL);
		jrb_insert_int(indegree, jval_i(node->key), new_jval_i(iv));
		if (iv == 0)
		{
			dll_append(tpQueue, node->key);
		}
	}
	
	while (!dll_empty(tpQueue))
	{
		Visit(G, jval_i(dll_first(tpQueue)->val));

		int arc[ARRSIZE]; 
		int sizeofArc = Outdegree(G, jval_i(dll_first(tpQueue)->val), arc);

		dll_delete_node(dll_first(tpQueue));
		
		int i;
		for(i = 0; i < sizeofArc; i++)
		{
			JRB tmp;
			tmp = jrb_find_int(indegree, arc[i]);

			if (tmp != NULL)
			{

				tmp->val = new_jval_i(jval_i(tmp->val)-1);

				if (jval_i(tmp->val) <= 0)
				{
					dll_append(tpQueue, tmp->key);
				}
			}	
		}
	}

	jrb_free_tree(indegree);
}
//---------------------------------------------------------
void ReadData(Graph G, char *fileName)
{
	IS is;
	is = new_inputstruct(fileName);
	if (is == NULL) 
	{
		perror("ERROR");
		exit(1);
  	}

  	int v_num = 0;
  	int mark = 0;
 	JRB node;
	
	while(get_line(is) >= 0) 
	{
		if (strcmp(is->fields[0], "CLASS") == 0)
		{
#pragma region ADDVERTICE
			// AddVertices
			if (jrb_empty(G.vertices))
			{
				AddVertice(G, v_num++, is->fields[1]);
			}
			else
			{
				int t = 0;
				jrb_traverse(node, G.vertices)
				{	
					if (strcmp(jval_s(node->val), is->fields[1]) == 0)
					{
						t = 1;
					}
				}

				if(t == 0)
				{
					AddVertice(G, v_num++, is->fields[1]);
				}
			}	
#pragma endregion
			mark = v_num - 1;
			//printf("%d-", v_num);
		}

		if (strcmp(is->fields[0], "PREREQ") == 0)
		{			
			int foundEqual = -1;
#pragma region ADDVERTICE				
			// AddVertices
			int t = 0;
			jrb_traverse(node, G.vertices)
			{
				if (strcmp(jval_s(node->val), is->fields[1]) == 0)
				{
					t = 1;
					foundEqual = jval_i(node->key);
				}
			}

			if(t == 0)
			{
				AddVertice(G, v_num++, is->fields[1]);
			}	
#pragma endregion	
			//printf("%d-", v_num);
			
			if (foundEqual != -1)
			{
				AddEdge(G, foundEqual, mark, 0.0, false);
				printf("%d->%d\n", foundEqual, mark);
			}
			else
			{
				AddEdge(G, v_num - 1, mark, 0.0, false);
				printf("%d->%d\n", v_num-1, mark);
			}
		}
	}

	jettison_inputstruct(is);
	return;
}
//---------------------------------------------------------