#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

// DEF for array
#define ARRSIZE 	10
#define RANGE 		10
#define INITIAL_SIZE 		10000
#define INCREMENTAL_SIZE 	5
#define DATA_FILENAME "bushn.txt"

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

#include "Source/graph.h"
#include "Source/util.h"
//---------------------------------------------------------
void ReadData(Graph g, const char* fileName)
{
	IS is;
	is = new_inputstruct(fileName);
	if (is == NULL) 
	{
		perror("ERROR");
		exit(1);
	}

	JRB node;
	
	while(get_line(is) >= 0) 
	{
		//printf("%s\n", is->text1);
		printf("%s\n", is->fields[0]);

	}
}
//---------------------------------------------------------
int main(int argc, char const *argv[])
{
	Graph g;
	g = CreateGraph();

	JRB node;

	ReadData(g, DATA_FILENAME);









	// int state = 1;
	// while (state != 0)
	// {
	// 	switch (GetMenu())
	// 	{
	// 		case 1: break;
	// 		case 2: break;
	// 		case 3: break;
	// 		case 4: break;
	// 		case 5: break;
	// 		case 6: break;
	// 		case 7: break;
	// 		case 0:	state = 0; break;
	// 		default: printf("Invalid Option\n"); continue;
	// 	}
	// }

	// Free and Exit'
	printf("%s\n", "Goodbye!");
	DropGraph(g);
	return 0;
}



	// DocMatran(g, DATA_FILENAME);

	// NEWLINE
	// printf("-Tong so nut = %d\n", TongSoNut(g));
	// printf("-Tong so cung = %d\n", TongSoCung(g));

	// printf("-Cac diem lien thong: "); 
	// TimDiemLienThong(g, 10);

	// printf("\n-Lien thong lon nhat:"); 
	// LienThongLonNhat(g);

	// NutDao(g);


	//DuongDiNganNhat(g, 00, 44);

	//printf("\n***********\n");
	//int sWay = 0;
	//SoCachDi(g, 00, 03, &sWay);
	//printf("**%d**\n", sWay);


	//ReadData(g, DATA_FILENAME);

	// // Create Vertices
	// AddVertice(g, 1, "V1");
	// AddVertice(g, 2, "V2");
	// AddEdge(g, 1, 1, 1, true);
	// AddVertice(g, 3, "V3");
	// AddVertice(g, 4, "V4");
	// AddEdge(g, 1, 2, 1, true);
	// AddEdge(g, 1, 3, 14, false);
	// AddEdge(g, 2, 4, 15, false);
	// AddEdge(g, 3, 4, 24, false);


// //	TRAVERSE_VERTICE	
// 	NEWLINE
// 	jrb_traverse(node, g.vertices)
// 	{
// 		printf("%s*", jval_s(node->val));
// 	}
// 	NEWLINE


// TRAVERSE_EDGES
// 	jrb_traverse(node, g.edges)
// 	{
// 		printf("\nVertice: %d", jval_i(node->key));
// 		JRB tree = (JRB)jval_v(node->val);
// 		printf("\nAdjacent: ");
// 		JRB as;
// 		jrb_traverse(as, tree)
// 			printf("%d*", jval_i(as->key));
// 	}


// GET_OUTDEGREE
// 	NEWLINE
// 	int vertexToGetOutdegree = 1;
// 	int outdegreeofVerticeArray[100];
// 	int numnberofAdjacentVertice_ = Outdegree(g, vertexToGetOutdegree, outdegreeofVerticeArray);
// 	for (i = 0; i < numnberofAdjacentVertice_; ++i)
// 	{
// 		printf("%d*", outdegreeofVerticeArray[i]);
// 	}


//	GET_INDEGREE
// 	NEWLINE
// 	int vertexToGetIndegree = 5;
// 	int indegreeofVerticeArray[100];
// 	for (i = 0; i < Indegree(g, vertexToGetIndegree, indegreeofVerticeArray); ++i)
// 	{
// 		printf("%d-", indegreeofVerticeArray[i]);
// 	}


//	BFS
// 	NEWLINE
// 	int bfsStart = 1;
// 	int bfsStop = -1; // no stop
// 	BFS(g, bfsStart, bfsStop, Visit);


//	DFS
// 	NEWLINE
// 	int dfsStart = 1;
// 	int dfsStop = -1; // no stop
// 	DFS(g, dfsStart, dfsStop, Visit);

	
//	DAG
// 	NEWLINE
// 	printf("\nDAG?: %d\n", isDAG(g));


//	TOPOSORT	
// 	if (!isDAG(g))
// 		TopologicalSort(g);
// 	else
// 		printf("%s\n", "");


//	SHORTEST_PATH
// 	int path[100];
// 	int sizeofPath = 0;
// 	int totalLength = 0;
// 	ShortestPath(g, 1, 9, path, &sizeofPath, &totalLength);
// 	printf("Length = %d\n", totalLength);
// 	printf("Path: ");
// 	int i = 0;
// 	for (i = 0; i <= sizeofPath; ++i)
// 		printf("%d-", path[i]);




// void ReadData(Graph G, char *fileName)
// {
// 	IS is;
// 	is = new_inputstruct(fileName);
// 	if (is == NULL) 
// 	{
// 		perror("ERROR");
// 		exit(1);
//   	}

//   	int v_num = 0;
//   	int mark = 0;
//  	JRB node;
	
// 	while(get_line(is) >= 0) 
// 	{
// 		if (strcmp(is->fields[0], "CLASS") == 0)
// 		{
// 			// AddVertices
// 			if (jrb_empty(G.vertices))
// 			{
// 				AddVertice(G, v_num++, is->fields[1]);
// 			}
// 			else
// 			{
// 				int t = 0;
// 				jrb_traverse(node, G.vertices)
// 				{	
// 					if (strcmp(jval_s(node->val), is->fields[1]) == 0)
// 					{
// 						t = 1;
// 					}
// 				}

// 				if(t == 0)
// 				{
// 					AddVertice(G, v_num++, is->fields[1]);
// 				}
// 			}	
// 			mark = v_num - 1;
// 			//printf("%d-", v_num);
// 		}

// 		if (strcmp(is->fields[0], "PREREQ") == 0)
// 		{			
// 			int foundEqual = -1;			
// 			// AddVertices
// 			int t = 0;
// 			jrb_traverse(node, G.vertices)
// 			{
// 				if (strcmp(jval_s(node->val), is->fields[1]) == 0)
// 				{
// 					t = 1;
// 					foundEqual = jval_i(node->key);
// 				}
// 			}

// 			if(t == 0)
// 			{
// 				AddVertice(G, v_num++, is->fields[1]);
// 			}		
// 			//printf("%d-", v_num);
			
// 			if (foundEqual != -1)
// 			{
// 				AddEdge(G, foundEqual, mark, 0.0, false);
// 				printf("%d->%d\n", foundEqual, mark);
// 			}
// 			else
// 			{
// 				AddEdge(G, v_num - 1, mark, 0.0, false);
// 				printf("%d->%d\n", v_num-1, mark);
// 			}
// 		}
// 	}

// 	jettison_inputstruct(is);
// 	return;
// }