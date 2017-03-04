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

#include "graph.h"
#include "util.h"
//---------------------------------------------------------
void ReadData(Graph g, const char* fileName);
int TongSoNut(Graph G);
int TongSoCung(Graph G);
int KiemTraMonHoc(Graph g, const id);
int CacMonCanHocTruoc(Graph g, const id, Dllist monhoctruoc);
void CongViec3(Graph g);
void CongViec5(Graph g);



int cacmontruoc(Graph g, const id, Dllist monhoctruoc, int* so)
{
	int i = 0;
	int outdegreeArray[100];
	int numnberofOutdegree_ = Indegree(g, id, outdegreeArray);
	for (i = 0; i < numnberofOutdegree_; ++i)
	{
		int truoc = outdegreeArray[i];

		if (!dll_find(monhoctruoc, truoc))
		{
			(*so)++;
			printf("%d ", truoc);
			dll_append(monhoctruoc, new_jval_i(truoc));
		}
	}

	for (i = 0; i < numnberofOutdegree_; ++i)
	{
		int temp = *so;
		int truoc = outdegreeArray[i];
		cacmontruoc(g, truoc, monhoctruoc, &temp);
	}
}
//---------------------------------------------------------
int main(int argc, char const *argv[])
{
	Graph g;
	g = CreateGraph();

	JRB node;

	char strTenTep[100] = DATA_FILENAME;

	// 1.
	printf("Nhap ten tep: "); scanf("%s", strTenTep);
	ReadData(g, strTenTep);
	printf("Tong so nut: %d\n", TongSoNut(g));
	printf("Tong so cung: %d\n", TongSoCung(g));
	// 2.
	int isChuTrinh = IsDAG(g);
	if (isChuTrinh == 1)
	{
		printf("CO CHU TRINH\n");
		return 0;
	}
	else
		printf("HOP LE\n");

	// 3.
	CongViec3(g);

	// 4.
	while (1)
	{
		printf("\nTiep tuc thuc hien cong viec 3 (y/n) ");
		char choice[10] = "";
		scanf("%s", choice);
		if (strcmp("y", choice) == 0 || strcmp("Y", choice) == 0)
		{
			CongViec3(g);
		}
		else break;
	}

	// 5.
	printf("\n\nDanh sach cac mon hoc: ");
	NEWLINE
	int i = 0;
	int output[100];
	for (i=0; i<TongSoNut(g); i++)
	{
		jrb_traverse(node,g.vertices)
		{
			int truoc = Indegree(g,jval_i(node->key),output);
			if (truoc == i ) 
				printf("%d",jval_i(node->key) );
		}
		NEWLINE
	}
	// Dllist monhoctruoc = new_dllist();
	// int so = 0;
	// cacmontruoc(g, 5, monhoctruoc, &so);
	// printf("**%d**", so);


	// 6.
	printf("Thu tu sap xep cac mon hoc:\n");
	TopologicalSort(g);


	// Free and Exit'
	printf("\n%s\n", "Goodbye!");
	DropGraph(g);
	return 0;
}

int TongSoNut(Graph G)
{
	int sV = 0;
	JRB node;
	jrb_traverse(node, G.vertices)
		sV++;
	return sV;
}
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
	return sE;
}
int KiemTraMonHoc(Graph G, const id)
{
	JRB node = make_jrb();
	node = jrb_find_int(G.vertices, id);

	if (NULL != node)
	{
		return 1;
	}

	//printf("Ten nguoi khong ton tai\n");
	return 0;
}
int CacMonCanHocTruoc(Graph g, const id, Dllist monhoctruoc)
{
	int i = 0;
	int outdegreeArray[100];
	int numnberofOutdegree_ = Indegree(g, id, outdegreeArray);

	for (i = 0; i < numnberofOutdegree_; ++i)
	{
		int truoc = outdegreeArray[i];

		if (!dll_find(monhoctruoc, truoc))
		{
			dll_append(monhoctruoc, new_jval_i(truoc));
		}
	}

	for (i = 0; i < numnberofOutdegree_; ++i)
	{
		int truoc = outdegreeArray[i];
		CacMonCanHocTruoc(g, truoc, monhoctruoc);
	}
}
int CacMonHocSau(Graph g, const id, Dllist monhocsau)
{
	int i = 0;
	int outdegreeArray[100];
	int numnberofOutdegree_ = Outdegree(g, id, outdegreeArray);
	//printf("===%d\n", numnberofOutdegree_);
	for (i = 0; i < numnberofOutdegree_; ++i)
	{
		int sau = outdegreeArray[i];

		if (!dll_find(monhocsau, sau))
		{
			printf("%d*", sau);
			dll_append(monhocsau, new_jval_i(sau));
		}
		
	}

	NEWLINE
	for (i = 0; i < numnberofOutdegree_; ++i)
	{
		int sau = outdegreeArray[i];
		CacMonHocSau(g, sau, monhocsau);
	}
}
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
	
	get_line(is);
	int somonhoc = atoi(is->fields[0]); 

	int i = 0;
	for (i = 0; i < somonhoc; ++i)
	{
		get_line(is);
		// char *ten = (char*)malloc(sizeof(char)*20);
		// strcpy(ten, is->fields[1]);

		// int id = atoi(is->fields[0]);
		int monhoc = atoi(is->fields[0]);
		AddVertice(g, monhoc, "");


		int j = 0;
		for (j = 1; j < is->NF; j++)
		{
			int monhoctruoc = atoi(is->fields[j]);
			//printf("%d*\n", monhoctruoc);
			AddVertice(g, monhoctruoc, "");
			AddEdge(g, monhoctruoc, monhoc, 1, false);
		}
		

		//printf("%d%s\n", id, ten);
		// AddVertice(g, id, ten);
	}
}
void CongViec3(Graph g)
{
	Dllist dllMonHocTruoc;
	int iMonHoc = -1;
	printf("Nhap mon hoc: "); scanf("%d", &iMonHoc);
	int isExist = KiemTraMonHoc(g, iMonHoc);
	if (isExist == 0)
		printf("KHONG TON TAI\n");
	else
	{
		printf("Cac mon can hoc truoc la: ");
		dllMonHocTruoc = new_dllist();
		CacMonCanHocTruoc(g, iMonHoc, dllMonHocTruoc);

		Dllist ptr;
		dll_traverse(ptr, dllMonHocTruoc)
			printf("%d ", jval_i(ptr->val));
		dll_delete_node(dllMonHocTruoc);
	}
}
void CongViec5(Graph G)
{
	Dllist tpQueue = new_dllist();
	JRB indegree = make_jrb();
	JRB node;

	jrb_traverse(node, G.vertices)
	{
		int iv = Indegree(G, jval_i(node->key), NULL);
		jrb_insert_int(indegree, jval_i(node->key), new_jval_i(iv));
		if (iv == 0)
			dll_append(tpQueue, node->key);
	}
	
	while (!dll_empty(tpQueue))
	{
		//Visit(G, jval_i(dll_first(tpQueue)->val));
		printf("%d ", jval_i(dll_first(tpQueue)->val));

		int arc[ARRSIZE]; 
		int sizeofArc = Outdegree(G, jval_i(dll_first(tpQueue)->val), arc);
		dll_delete_node(dll_first(tpQueue));
		NEWLINE
		
		int i;
		for(i = 0; i < sizeofArc; i++)
		{
			JRB tmp;
			tmp = jrb_find_int(indegree, arc[i]);

			if (tmp != NULL)
			{
				tmp->val = new_jval_i(jval_i(tmp->val)-1);
				if (jval_i(tmp->val) <= 0)
					dll_append(tpQueue, tmp->key);
			}	
		}
	}

	jrb_free_tree(indegree);
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