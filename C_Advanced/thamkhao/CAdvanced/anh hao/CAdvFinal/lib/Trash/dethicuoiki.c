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
#define INITIAL_SIZE 		10000
#define INCREMENTAL_SIZE 	5
#define DATA_FILENAME "data.txt"

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

// Các hàm của bài thi cuối kì
void DocMatran(Graph G, char *fileName);
int TongSoNut(Graph G);
int TongSoCung(Graph G);
void TimDiemLienThong(Graph G, int v);
void LienThongLonNhat(Graph G);
void NutDao(Graph G);
void DuongDiNganNhat(Graph G, int start, int stop);
void SoCachDi(Graph G, int start, int stop, int *sWay);

//---------------------------------------------------------
int main(int argc, char const *argv[])
{
	JRB node;

	// Init Graph
	Graph g;
	g = CreateGraph();

	int v, v1, sWay = 0;
	int state = 1;
	while (state != 0)
	{
		switch (GetMenu())
		{
			case 1: DocMatran(g, DATA_FILENAME); break;
			case 2: 
			{
				NEWLINE
				printf("-Tong so nut = %d\n", TongSoNut(g));
				printf("-Tong so cung = %d\n", TongSoCung(g));
				break;
			}
			case 3: 
			{
				printf("Nhap dinh can tim lien thong: ");
				scanf("%d", &v);
				printf("\nCac diem lien thong voi %d la: ", v); 
				TimDiemLienThong(g, v);
				break;
			}
			case 4:
			{
				printf("\nLien thong lon nhat:"); 
				LienThongLonNhat(g);
				break;
			}
			case 5:
			{
				NutDao(g);
				break;
			}
			case 6:
			{
				printf("Nhap dinh bat dau: ");
				scanf("%d", &v);
				printf("Nhap dinh ket thuc: ");
				scanf("%d", &v1);
				DuongDiNganNhat(g, v, v1);
				break;
			}
			case 7:
			{
				printf("Nhap dinh bat dau: ");
				scanf("%d", &v);
				printf("Nhap dinh ket thuc: ");
				scanf("%d", &v1);
				SoCachDi(g, 00, 03, &sWay);
				printf("So cach di giua %d va %d la: %d", v, v1, sWay);
			}
			case 0:
			{
				state = 0;
				break;
			}

			default: printf("Invalid Option\n"); continue;
		}
	}

	// Free and Exit
	printf("%s\n", "Goodbye!");
	DropGraph(g);
	return 0;
}

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
		// Do somethings with this adjacent vertex here
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
	NEWLINE
	printf("-Duong di ngan nhat: \n");
	int sizeofPath = 0;
	int totalLength = 0;
	int path[100];
	ShortestPath(G, start, stop, path, &sizeofPath, &totalLength);
	printf("	+Length = %d\n", totalLength);
	printf("	+Number of vertices pass: %d\n", sizeofPath);
	printf("	+Path: ");
	int i = 0;
	for (i = sizeofPath-1; i > 0; i--)
		printf("%d-", path[i]);
	printf("%d", path[0]);
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
			int n = Outdegree(G, u, output);
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

