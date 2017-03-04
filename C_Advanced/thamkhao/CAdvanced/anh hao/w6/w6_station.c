#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#define ARRSIZE 	10
#define RANGE 		10
#define EPSILON 	1E-7
#define MAX_BUFF 	512

#define INITIAL_SIZE 		10
#define INCREMENTAL_SIZE 	5
#define BUFF_SIZE			80

#define NULLVERTICE	-99999

#define NEWLINE 	printf("%s", "\n");

#define TXTDATAFILE	"w6_station.txt"

enum bool {false, true};
typedef int bool;

#include "fields.h"
#include "jrb.h"

typedef JRB Graph;

Graph CreateGraph(void);
//int CheckValidVertex(Graph G, int v);
void AddEdge(Graph G, int v1, int v2, float weight, bool indirected);
int IsAdjacent(Graph G, int v1, int v2);
int GetAdjacentVerticle(Graph G, int v, int *output);
void ShowAdjacentVerticle(Graph G, int v);
void DropGraph(Graph G);

Graph ReadDataFile()
{
	IS isStation;
	isStation = new_inputstruct(TXTDATAFILE);
	if (isStation == NULL) 
	{
		perror(TXTDATAFILE);
		exit(1);
	}

	Graph G = make_jrb();
	int i;
	while(get_line(isStation) >= 0) 
	{
		// if (strcmp(isStation->text1, "[LINES]\n") == 0)
		// {
		// 	while(get_line(isStation) == 3) 
		// 	{
		// 		jrb_insert_int(G, atoi(isStation->fields[0]), new_jval_s(isStation->fields[i+2]));
		// 	}
		// }


		if (strcmp(isStation->text1, "[LINES]\n") == 0)
		{
			while(get_line(isStation) >= 3) 
			{
				for(i = 1; i < isStation->NF-1; i++)
				AddEdge(G, atoi(isStation->fields[i]), atoi(isStation->fields[i+1]), 0, true);
			}
		}

		// printf("%s\n", isStation->text1);
		// for (i = 0; i < isStation->NF; i++) 
		// {
		// 	printf("%d: %s\n", isStation->line, isStation->fields[i]);
		// }
	}

	jettison_inputstruct(isStation);
	return G;
}

int main(int argc, char const *argv[])
{
	/* This is sample main function
	Graph myGraph;
	myGraph = CreateGraph();

	AddEdge(myGraph, 0 ,1, 1, true);
	AddEdge(myGraph, 1 ,2, 1, true);
	AddEdge(myGraph, 1 ,3, 1, true);
	AddEdge(myGraph, 1 ,3, 1, false);

	// AddEdge(myGraph, 2 ,5);
	// AddEdge(myGraph, 2 ,6);
	// AddEdge(myGraph, 2 ,9);
	// AddEdge(myGraph, 4 ,9);

	ShowAdjacentVerticle(myGraph, 1);
	DropGraph(myGraph);
	*/
	int v;
	scanf("%d", &v);
	Graph myGraph = ReadDataFile();
	ShowAdjacentVerticle(myGraph, v);

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
		if (v2 != NULLVERTICE)
		{
			jrb_insert_int(tree, v2, new_jval_f(weight));
		}
	}
	else
	{
		tree = (JRB)jval_v(node->val);
		if (v2 != NULLVERTICE && jrb_find_int(tree, v2) == NULL)
		{
			jrb_insert_int(tree, v2, new_jval_f(weight));
		}
	}

	if (v2 != NULLVERTICE && indirected)
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

void ShowAdjacentVerticle(Graph G, int v)
{
	int output[ARRSIZE];
	int n = GetAdjacentVerticle(G, v, output);

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