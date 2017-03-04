#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

// DEF for array
#define ARRSIZE 	10
#define RANGE 		10
#define EPSILON 	1E-7
#define MAX_BUFF 	512

//
#define INITIAL_SIZE 		10000
#define INCREMENTAL_SIZE 	5
#define BUFF_SIZE			80

// DEF for Dijkstra
#define INFINITY_	100000
#define MAXVERTICE	1000
//
#define DATA_FILENAME "data.txt"
//
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
			return 1;
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
void 	AddEdge(Graph G, int v1, int v2, int weight, bool indirected); //indirected==true: do thi vo huong
int 	IsAdjacent(Graph G, int v1, int v2);
int 	GetAdjacentVerticle(Graph G, int v, int *output);
void 	ShowAdjacentVerticle(Graph G, int v);
int 	Indegree(Graph graph, int v, int* output);
int 	Outdegree(Graph graph, int v, int* output);
int 	GetEdgeValue(Graph graph, int u, int v);
void 	DropGraph(Graph G);
//---------------------------------------------------------
// Travesral functions
int 	Visit(Graph G, int v);
void 	BFS(Graph G, int start, int stop, int(*Visit)(Graph, int));
void 	DFS(Graph G, int start, int stop, int(*Visit)(Graph, int));
int 	isDAG(Graph G);
void 	TopologicalSort(Graph G);
void 	ReadData(Graph G, char *fileName);
void	ShortestPath(Graph G, int start, int end, int* path, int* sizeofPath, int *totalLength);
//---------------------------------------------------------

// Các hàm của bài thi cuối kì
int GetMenu(void);
void DocMatran(Graph G, char *fileName)
{
	IS is;
	is = new_inputstruct(fileName);
	if (is == NULL) 
	{
		perror("ERROR");
		exit(1);
  	}

  	int iRow = 0;
  	int iCol = 0;
	// Read file and Add Vertice
	while(get_line(is) >= 0) 
	{
		int i = 0;
		for (i = 0; i < is->NF; i++) 
		{
    		int column = i;  
    		int row = is->line - 1;
    		
    		if (atoi(is->fields[i]) == 0)
    		{
    			AddVertice(G, row*10+column, " ");
    			//printf("%d\n", row*10+column);
    		}
    	}
    	iRow++;
    	iCol = is->NF;
	}

	// Add Edge
	JRB node;
	jrb_traverse(node, G.vertices)
	{
		int row1 = jval_i(node->key)/10;
		int column1 = jval_i(node->key)%10;
		
		JRB temp;
		jrb_traverse(temp, G.vertices)
		{
			int row2 = jval_i(temp->key)/10;
			int column2 = jval_i(temp->key)%10;
			
			// down
			if (row1==row2-1 && column1==column2)
			{
				AddEdge(G, jval_i(node->key), jval_i(temp->key), 1, false);
			}
			// up
			else if (row1==row2+1 && column1==column2)
			{
				AddEdge(G, jval_i(node->key), jval_i(temp->key), 1, false);
			}
			// left
			else if (column1==column2+1 && row1==row2)
			{
				AddEdge(G, jval_i(node->key), jval_i(temp->key), 1, false);
			}
			// right
			else if (column1==column2-1 && row1==row2)
			{
				AddEdge(G, jval_i(node->key), jval_i(temp->key), 1, false);
			}
		}
	}

	int r = 0, c = 0;
	for (r = 0; r < iRow; ++r)
	{
		for (c = 0; c < iCol; ++c)
		{
			node = jrb_find_int(G.vertices, r*10+c);
			if (NULL != node) printf("0 ");
			else printf("1 ");
		}
		NEWLINE
	}

	
	jettison_inputstruct(is);
	return;
}
//---------------------------------------------------------
int TongSoNut(Graph G)
{
	int sV = 0;
	JRB node;
	jrb_traverse(node, G.vertices)
		sV++;
	return sV;
}
//---------------------------------------------------------
int TongSoCung(Graph G)
{
	int sE = 0;
	JRB node;
	jrb_traverse(node, G.edges)
	{
		JRB tree = (JRB)jval_v(node->val);
		JRB as;
		jrb_traverse(as, tree)
			sE++;
	}
	return sE/2;
}
//---------------------------------------------------------
void TimDiemLienThong(Graph G, int v)
{
	int vertexToGetOutdegree = v;
	int outdegreeofVerticeArray[100];

	int i;
	int numnberofAdjacentVertice_ = Outdegree(G, vertexToGetOutdegree, outdegreeofVerticeArray);
	for (i = 0; i < numnberofAdjacentVertice_; ++i)
	{
		printf("%d ", outdegreeofVerticeArray[i]);
	}
}
//---------------------------------------------------------
void LienThongLonNhat(Graph G)
{
 	JRB node;
 	int max_ = 0;
 	jrb_traverse(node, G.vertices)
 	{
		int vertexToGetOutdegree = jval_i(node->key);

		int outdegreeofVerticeArray[100];
		int numnberofAdjacentVertice_ = Outdegree(G, vertexToGetOutdegree, outdegreeofVerticeArray);
		
		if (max_ < numnberofAdjacentVertice_)
		{
			max_ = numnberofAdjacentVertice_;
		}
	}
	printf("\nSo lien thong lon nhat = %d, cac dinh do la: ", max_);

	// in ra dinh co so lien thong = max_
	jrb_traverse(node, G.vertices)
 	{
		int vertexToGetOutdegree = jval_i(node->key);

		int outdegreeofVerticeArray[100];
		
		int numnberofAdjacentVertice_ = Outdegree(G, vertexToGetOutdegree, outdegreeofVerticeArray);
		
		if (max_ == numnberofAdjacentVertice_)
		{
			printf("%d ", vertexToGetOutdegree);
		}
	}
}
//---------------------------------------------------------
void NutDao(Graph G)
{
	printf("\nCac nut dao la: ");
	JRB node;
 	jrb_traverse(node, G.vertices)
 	{
 		JRB temp = jrb_find_int(G.edges, jval_i(node->key));
	 	if (temp == NULL)
	 	{
	 		printf("%d ", jval_i(node->key));
	 	}
 	}
}
//---------------------------------------------------------
void DuongDiNganNhat(Graph G, int start, int stop)
{
	int path[100];
	int sizeofPath = 0;
	int totalLength = 0;
	ShortestPath(G, start, stop, path, &sizeofPath, &totalLength);
	printf("Length = %d\n", totalLength);
	printf("Path: ");
	int i = 0;
	for (i = 0; i <= sizeofPath; ++i)
		printf("%d-", path[i]);
}
//---------------------------------------------------------
void SoCachDi(Graph G, int start, int stop, int *sWay)
{
	NEWLINE
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
			printf("%d ", u);
			//Visit(G, u);

			// Set stop = -1 if you want to traverse all vertices
			if (stop == u)
			{
				(*sWay)++;
				return;
			}
			
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
						//SoCachDi(G, output[i], stop, sWay);
					}
				}
			}
		}
	}

	free_dllist(visited);
}
//---------------------------------------------------------
int main(int argc, char const *argv[])
{
	JRB node;

// 	printf("1");
	// Init Graph
	Graph g;
	g = CreateGraph();

	DocMatran(g, DATA_FILENAME);

	printf("Tong so nut = %d\n", TongSoNut(g));
	printf("Tong so cung = %d\n", TongSoCung(g));

	TimDiemLienThong(g, 10);

	LienThongLonNhat(g);

	NutDao(g);

	DuongDiNganNhat(g, 00, 44);


	NEWLINE
	printf("%d\n", IsAdjacent(g, 32, 42));
	//printf("\n***********\n");
	//int sWay = 0;
	//SoCachDi(g, 00, 03, &sWay);
	//printf("**%d**\n", sWay);



// 	//ReadData(g, DATA_FILENAME);

// 	// Create Vertices\
	// AddVertice(g, 1, "V1");
 // 	AddVertice(g, 2, "V2");
// 	AddVertice(g, 3, "V3");
// 	AddVertice(g, 4, "V4");
// 	AddVertice(g, 5, "V5");
// 	AddVertice(g, 6, "V6");
// 	AddVertice(g, 7, "V7");
//	AddVertice(g, 8, "V8");
//	AddEdge(g, 1, 2, 1, true);
// 	AddEdge(g, 1, 2, 9, false);
// 	AddEdge(g, 1, 6, 14, false);
// 	AddEdge(g, 1, 7, 15, false);
// 	AddEdge(g, 2, 3, 24, false);
// 	AddEdge(g, 3, 8, 19, false);	
// 	AddEdge(g, 3, 5, 2, false);	
// 	AddEdge(g, 4, 3, 6, false);
// 	AddEdge(g, 4, 8, 6, false);
// 	AddEdge(g, 5, 4, 11, false);
// 	AddEdge(g, 5, 8, 16, false);
// 	AddEdge(g, 6, 7, 5, false);
// 	AddEdge(g, 6, 3, 18, false);
// 	AddEdge(g, 6, 5, 30, false);
// 	AddEdge(g, 7, 5, 20, false);
// 	AddEdge(g, 7, 8, 44, false);


// 	printf("aaaa");
// #pragma region SHORTEST_PATH
// 	int path[100];
// 	int sizeofPath = 0;
// 	int totalLength = 0;
// 	ShortestPath(g, 1, 9, path, &sizeofPath, &totalLength);
// 	printf("Length = %d\n", totalLength);
// 	printf("Path: ");
// 	int i = 0;
// 	for (i = 0; i <= sizeofPath; ++i)
// 		printf("%d-", path[i]);
// #pragma endregion SHORTEST_PATH

// #pragma region TRAVERSE_VERTICE	
// 	NEWLINE

// 	jrb_traverse(node, g.vertices)
// 	{
// 		printf("%s*", jval_s(node->val));
// 	}
// 	NEWLINE
// #pragma endregion TRAVERSE_VERTICE	

// #pragma region TRAVERSE_EDGES
// 	jrb_traverse(node, g.edges)
// 	{
// 		printf("\nVertice: %d", jval_i(node->key));
// 		JRB tree = (JRB)jval_v(node->val);
// 		printf("\nAdjacent: ");
// 		JRB as;
// 		jrb_traverse(as, tree)
// 			printf("%d*", jval_i(as->key));
// 	}
// #pragma endregion TRAVERSE_EDGES

// #pragma region GET_OUTDEGREE
// 	NEWLINE
// 	int vertexToGetOutdegree = 1;
// 	int outdegreeofVerticeArray[100];
// 	int numnberofAdjacentVertice_ = Outdegree(g, vertexToGetOutdegree, outdegreeofVerticeArray);
// 	for (i = 0; i < numnberofAdjacentVertice_; ++i)
// 	{
// 		printf("%d*", outdegreeofVerticeArray[i]);
// 	}
// #pragma endregion GET_OUTDEGREE	

// #pragma region GET_INDEGREE
// 	NEWLINE
// 	int vertexToGetIndegree = 5;
// 	int indegreeofVerticeArray[100];
// 	for (i = 0; i < Indegree(g, vertexToGetIndegree, indegreeofVerticeArray); ++i)
// 	{
// 		printf("%d-", indegreeofVerticeArray[i]);
// 	}
// #pragma endregion GET_INDEGREE

// #pragma region BFS
// 	NEWLINE
// 	int bfsStart = 1;
// 	int bfsStop = -1; // no stop
// 	BFS(g, bfsStart, bfsStop, Visit);
// #pragma endregion BFS	
	
// #pragma region DFS
// 	NEWLINE
// 	int dfsStart = 1;
// 	int dfsStop = -1; // no stop
// 	DFS(g, dfsStart, dfsStop, Visit);
// #pragma endregion DFS
	
// #pragma region DAG
// 	NEWLINE
// 	printf("\nDAG?: %d\n", isDAG(g));
// #pragma endregion DAG

// #pragma region TOPOSORT	
// 	if (!isDAG(g))
// 		TopologicalSort(g);
// 	else
// 		printf("%s\n", "");
// #pragma endregion TOPOSORT

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
		jrb_insert_int(G.vertices, id, new_jval_s(strdup(name))); // insert new
	}
	else
	{
		strcpy(jval_s(node->val), name); // update
	}
}
//---------------------------------------------------------
void AddEdge(Graph G, int v1, int v2, int weight, bool indirected)
{
	JRB tree = make_jrb();
	JRB node = make_jrb();
	node = jrb_find_int(G.edges, v1);
	
	if (node == NULL)
	{
		jrb_insert_int(G.edges, v1, new_jval_v(tree));
		jrb_insert_int(tree, v2, new_jval_i(weight));
	}
	else
	{
		tree = (JRB)jval_v(node->val);
		if (jrb_find_int(tree, v2) == NULL)
		{
			jrb_insert_int(tree, v2, new_jval_i(weight));
		}
	}

	if (indirected)
	{
		AddEdge(G, v2, v1, weight, false);
	}
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
int GetEdgeValue(Graph G, int u, int v)
{
	JRB node = jrb_find_int(G.edges, u);
	if (NULL == node)
		return INFINITY_;
	
	JRB adjacentTree = make_jrb();
	adjacentTree = (JRB)jval_v(node->val);
	node = jrb_find_int(adjacentTree, v);
	if (NULL == node)
		return INFINITY_;
	else
		return jval_i(node->val);
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
void ShortestPath(Graph G, int start, int end, int* path, int* sizeofPath, int *totalLength)
{
	// This funcion base on Dijkstra Algorithm
	int distance[MAXVERTICE], previous[MAXVERTICE];
	int min;
	// Initial
	int i;
	int u;
	for (i = 0; i < MAXVERTICE; ++i)
		distance[i] = INFINITY_;

	// Set first start to priority queue
	previous[start] = start;
	distance[start] = 0;
	Dllist pQueue = new_dllist();
	Dllist visited = new_dllist();
	dll_append(pQueue, new_jval_i(start));

	Dllist dequeue;

	while (!dll_empty(pQueue))
	{
		// Extract min
		min = INFINITY_;
		Dllist ptr;
		dll_traverse(ptr, pQueue)
		{
			u = jval_i(ptr->val);
			if (min > distance[u])
			{
				min = distance[u];
				dequeue = ptr;
			}
		}
		u = jval_i(dequeue->val);
		dll_delete_node(dequeue);

		if (u == end)
			break;

		// Relax
		int output[100];
		int numnberofAdjacentVertice = Outdegree(G, u, output);
		for (i = 0; i < numnberofAdjacentVertice; ++i)
		{
			int v = output[i];
			int w = GetEdgeValue(G, u, v);

			if (distance[v] > distance[u] + w)
			{
				distance[v] = distance[u] + w;
				previous[v] = u;
			}
			
			// Modify key
			int foundInQueue = 0;
			dll_traverse(ptr, visited)
			{
				int t = jval_i(ptr->val);
				if (v == t)
					foundInQueue = 1;
			}
			if (foundInQueue != 1)
			{
				dll_append(pQueue, new_jval_i(v));
				dll_append(visited, new_jval_i(v));
			}
		}
	}

	*sizeofPath = 0;
	*totalLength = distance[end];

	if (distance[end] != INFINITY_)
	{
		while (end != start)
		{
			path[(*sizeofPath)++] = end;
			end = previous[end];
		}
		path[(*sizeofPath)] = start;
	}	
}
//-------------------------------------------------------------------
int IsAdjacent(Graph G, int v1, int v2)
{
	JRB node = jrb_find_int(G.edges, v1);
	if (node == NULL) 
		return 0;
	else
	{
		JRB adjacentTree = make_jrb();
		adjacentTree = (JRB)jval_v(node->val);
		JRB temp = jrb_find_int(adjacentTree, v2);
		if (temp != NULL)
			return 1;
	}
	return 0;
}

//-------------------------------------------------------------------
int GetMenu(void)
{
	int menuOption = 0;
	do 
	{
		printf("\n\n---SORT MENU---\n");
		printf("1. Doc va in ma tran\n");
		printf("2. Thong tin ma tran\n");
		printf("3. Tim diem lien thong\n");
		printf("4. Danh sach cac nut co lien thong lon nhat\n");
		printf("5. Danh sach nut dao\n");
		printf("6. Duong di ngan nhat\n");
		printf("7. Tong so cach di giua 2 diem\n");
		printf("0. Exit\n");
		printf("Your Choice: ");
		scanf("%d", &menuOption);
	} while(menuOption < 0 || menuOption > 7);
	return menuOption;
}