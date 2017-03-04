#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../di_graph.h"

#define MAX 80

void visit(int v){ printf("%3d", v);}

void getDataFrom(FILE *file, Graph *ptr_G, int *N, int *M);
void list(Graph G, int start, int stop, int k, void (*visit)(int));

int main(int argc, char const *argv[])
{
	if(argc == 1) {
		printf("Error! Please specify the task!\n");
		exit(1);
	}

	char task[MAX], file_name[MAX];
	strcpy(task, argv[1]);

	FILE *file;
	Graph G = create();
	int N, M;

	// Print notice
	if (strcmp(task, "about") == 0) { // about
		
		printf("Bai thi lap trinh C nang cao HK2-2014-2015\n");
		return 0;

	} 

	// Read file and print out N, M
	else if (strcmp(task, "size") == 0) { // size <file_name>

		if(argc != 3) {
			printf("Error! Incorrect command!\n");
			exit(1);
		}

		strcpy(file_name, argv[2]);
		file = fopen(file_name, "r");

		if(file == NULL) {
			printf("Error! Cannot open file %s!\n", file_name);
			exit(1);
		}

		getDataFrom(file, &G, &N, &M);

		printf("%d %d\n", N, M);
	} 

	// Print out outdegree web of 'id'
	else if (strcmp(task, "out") == 0) { // out <file_name> <id>

		if(argc != 4) {
			printf("Error! Incorrect command!\n");
			exit(1);
		}

		strcpy(file_name, argv[2]);
		file = fopen(file_name, "r");

		if(file == NULL) {
			printf("Error! Cannot open file %s!\n", file_name);
			exit(1);
		}

		int id;
		if(!(id = atoi(argv[3]))) {
			printf("Error! Undefined 'id'!\n");
			exit(1);
		}

		getDataFrom(file, &G, &N, &M);

		int n = G.MAX_VERTICES;
		int *out = (int*)malloc(sizeof(int) * n);
		int i, k;

		k = outdegree(G, id, out);

		for(i = 0; i < k; i++)
			printf("%s\n", getVertex(G, out[i]));
	} 

	// Print out web with maximum indegree
	else if (strcmp(task, "maxin") == 0) { // maxin <file_name> 

		if(argc != 3) {
			printf("Error! Incorrect command!\n");
			exit(1);
		}

		strcpy(file_name, argv[2]);
		file = fopen(file_name, "r");

		if(file == NULL) {
			printf("Error! Cannot open file %s!\n", file_name);
			exit(1);
		}

		getDataFrom(file, &G, &N, &M);

		JRB node;
		int max = -1000;
		int n = getHighestID(G) + 1;
		int *out = (int*)malloc(sizeof(int) * n);
		int *in = (int*)malloc(sizeof(int) * n);
		int i, u, v;

		for(i = 0; i < MAX; i++)
			in[i] = max;

		jrb_traverse(node, G.vertices) {
			u = jval_i(node->key);
			in[u] = indegree(G, u, out);
		}

		for(i = 0; i < MAX; i++) {
			if(in[i] >= max) {
				max = in[i];
				v = i;
			}
		}

		printf("%s\n", getVertex(G, v));
	} 

	// Print out self-reference web, otherwise print 'OK'
	else if (strcmp(task, "selfref") == 0) { // selfref <file_name>

		if(argc != 3) {
			printf("Error! Incorrect command!\n");
			exit(1);
		}

		strcpy(file_name, argv[2]);
		file = fopen(file_name, "r");

		if(file == NULL) {
			printf("Error! Cannot open file %s!\n", file_name);
			exit(1);
		}

		getDataFrom(file, &G, &N, &M);

		JRB node, tree, tmp;
		int u, v;

		jrb_traverse(node, G.edges) {
			u = jval_i(node->key);
			tree = (JRB)jval_v(node->val);

			jrb_traverse(tmp, tree) {
				v = jval_i(tmp->key);
				if(u == v) {
					printf("%s\n", getVertex(G, v));
					return 0;
				}
			}
		}

		printf("OK\n");

	} 

	// List all webs that 'id' can go to with less than k connections
	else if (strcmp(task, "list") == 0) { // list <file_name> <id> <k>

		if(argc != 5) {
			printf("Error! Incorrect command!\n");
			exit(1);
		}

		strcpy(file_name, argv[2]);
		file = fopen(file_name, "r");

		if(file == NULL) {
			printf("Error! Cannot open file %s!\n", file_name);
			exit(1);
		}

		getDataFrom(file, &G, &N, &M);

		int id;
		if(!(id = atoi(argv[3]))) {
			printf("Error! Undefined 'id'!\n");
			exit(1);
		}

		int k;
		if(!(k = atoi(argv[4]))) {
			printf("Error! Undefined 'k'!\n");
			exit(1);
		}

		list(G, id, -1, k, visit);

	} 

	else {
		printf("Error! Undefined task! Exiting...\n");
		exit(1);
	}

	drop(&G);
	
	return 0;
}

void getDataFrom(FILE *file, Graph *ptr_G, int *N, int *M) {
	int i, id, v1, v2;

	// Read N
	fscanf(file, "%d\n", N);

	// Read vertices
	for(i = 0; i < (*N); i++) {
		char *name = (char*)malloc(sizeof(char) * MAX);
		fscanf(file, "%s %d\n", name, &id);
		addVertex(ptr_G, id, name);
	}

	// Read M
	fscanf(file, "%d\n", M);

	// Read edges
	for(i = 0; i < (*M); i++) {
		fscanf(file, "%d %d\n", &v1, &v2);
		addEdge(*ptr_G, v1, v2);
	}
}

void list(Graph G, int start, int stop, int k, void (*visit)(int)) {
	Dllist S, node;
	int i, _k, n, u, v;
	int count = 0;

	n = getHighestID(G) + 1;

	JRB _node = jrb_find_int(G.edges, start);
	if(_node == NULL) return;

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
			printf("%s\n", getVertex(G, u));
			visited[u] = 1;

			if(u == stop) return;


			count++;
			if(count <= k) {
				_k = outdegree(G, u, out);

				for(i = 0; i < _k; i++) {
					v = out[i];

					if(visited[v] == 0) {
						dll_append(S, new_jval_i(v));
					}
				}
			}
		}
	}
}