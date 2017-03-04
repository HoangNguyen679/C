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

#define NEWLINE 	printf("%s", "\n");

enum bool {false, true};
typedef int bool;

#include "jrb.h"
#include "dllist.h"
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

typedef JRB Graph;
//---------------------------------------------------------
Graph CreateGraph(void);
//int CheckValidVertex(Graph G, int v);
void AddEdge(Graph G, int v1, int v2, float weight, bool indirected);
int IsAdjacent(Graph G, int v1, int v2);
int GetAdjacentVerticle(Graph G, int v, int *output);
void ShowAdjacentVerticle(Graph G, int v);
void DropGraph(Graph G);
//---------------------------------------------------------
// Travesral functions
int Visit(Graph G, int v);
void BFS(Graph G, int start, int stop, int(*Visit)(Graph, int));
void DFS(Graph G, int start, int stop, int(*Visit)(Graph, int));

//---------------------------------------------------------
int main(int argc, char const *argv[])
{
	Graph myGraph;
	myGraph = CreateGraph();

	AddEdge(myGraph, 0 ,1, 1, true);
	AddEdge(myGraph, 0 ,2, 1, true);
	AddEdge(myGraph, 0 ,3, 1, true);
	AddEdge(myGraph, 2, 4, 1, true);
	AddEdge(myGraph, 4 ,5, 1, true);

	//ShowAdjacentVerticle(myGraph, 1);
	BFS(myGraph, 0, 4, Visit);
	NEWLINE
	DFS(myGraph, 0, 4, Visit);


	DropGraph(myGraph);
	return 0;
}
//---------------------------------------------------------
Graph CreateGraph(void)
{
	Graph G = make_jrb();
	if (G == NULL)
	{
		printf("%s\n", "Could not create graph!");
	}
	return G;
}
//---------------------------------------------------------
void AddEdge(Graph G, int v1, int v2, float weight, bool indirected)
{
	JRB tree = make_jrb();

	JRB node = make_jrb();
	node = jrb_find_int(G, v1);
	
	if (node == NULL)
	{
		jrb_insert_int(G, v1, new_jval_v(tree));
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
	node = jrb_find_int(G, v);

	if (node == NULL)
	{
		printf("%s\n", "Vertex does not exist!");
		return 0;
	}

	JRB tree = (JRB)jval_v(node->val);
	int total = 0;
	jrb_traverse(node, tree)
		output[total++] = jval_i(node->key);

	return total;
}
//---------------------------------------------------------
void DropGraph(Graph G)
{	
	JRB node;
	jrb_traverse(node, G)
		jrb_free_tree( jval_v(node->val) );
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
	printf("%d ", v);
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
	Dllist l = new_dllist();
	Dllist visited = new_dllist();

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