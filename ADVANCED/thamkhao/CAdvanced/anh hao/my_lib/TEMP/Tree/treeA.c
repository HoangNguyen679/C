#include <stdio.h>
#include <stdlib.h>

struct Node {
	int value;
	Node *leftmostChild;
	Node *rightSibling;
	Node *parent;
};

Node *root = NULL;

void admit(Node *v, Node *pv){
	//addd pair v, pv into the tree, pv is the parent of v, v will be added in the right of children list of pv
	if(pv == NULL) return;
	if(pv->leftmostChild == NULL){
		pv->leftmostChild = v;
	}else {
		Node * p = pv->leftmostChild;
		while(p->rightSibling != NULL){
			p = p->rightSibling
		}
		p->rightSibling = v;
	}
}

void ReadData(char *fn){
	FILE *f = fopen(fn, "r");
	int n;
	fscanf(f, "%d", &n);
	int p[n+1]; //p[i] is the parent of the node i
	for(int i = 1; i<=n; i++){
		fscanf("")
	}

	fclose(f);

	//building
}


void print(Node *r, int d){
	if(d > 0){
		for(int i =1; i <= d-1; i++) printf("|---");
	}
	printf("%d\n", r->value);
	Node *p = r->leftmostChild;
	int i = 1;
	while(p != NULL){
		print(p , d+1);
		p = p->rightSibling;
		i++;
	}
}

Node *find(int x, Node *r){
	if(r == NULL) return NULL;
	if(r->value == x) return r;
	Node *p = r->leftmostChild;
	while(p != NULL){
		Node *node = find(x,p);
	}
}

void PreOrderTraversal(Node *r){
	if(r == NULL) return;
	printf("%d", r->value);
	Node *p = r->leftmostChild;
	if(p == NULL) return;
	PreOrderTraversal(p);
	p = p->rightSibling;
	while(p != NULL){
		PreOrderTraversal(p);
		p = p->rightSibling;
	}
