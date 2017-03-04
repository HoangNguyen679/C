#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Node{
	int value;
	Node* leftmost_child;
	Node* right_sibling;
	Node* parent;
};

Node* root = NULL;

void admit(Node* v, Node* pv){
	// add pair v, pv into the tree, pv is the parent of v, v will be added in the right of chilrend list of pv
	if(pv == NULL) return;
	if(pv->leftmost_child == NULL){
		pv->leftmost_child = v;	
	}else{
		Node* p = pv->leftmost_child;
		while(p->right_sibling != NULL){
			p = p->right_sibling;
		}
		p->right_sibling = v;
	}
	v->parent = pv;
}

void readData(char *fn){
	FILE* f = fopen(fn,"r");
	if(f == NULL){
		perror("ERROR");
		exit(1);
	}
	
	int n;
	fscanf(f,"%d",&n);
	int p[n+1];// p[i] is the parent of node i
	for(int i = 1; i <= n; i++){
		int v, pv;
		fscanf(f,"%d %d",&v,&pv);
		p[v] = pv;
		//cout << "read v = " << v << " pv = " << pv << endl;
	}		
	fclose(f);

	// building the tree with above data structure
		
	Node* nodes[n+1];
	for(int v = 1; v <= n; v++){
		nodes[v] = new Node;
		nodes[v]->value = v;
		nodes[v]->leftmost_child = NULL;
		nodes[v]->right_sibling = NULL;		
		nodes[v]->parent = NULL;
	}
	cout << "OK, starting admit" << endl;
	for(int v = 1; v <= n; v++){
		int pv = p[v];
		Node* nod_v = nodes[v];
		Node* nod_pv = NULL;
		//cout << "v = " << v << " pv = " << pv << endl;
		if(pv == 0)
			root = nod_v;
		else 
			nod_pv = nodes[pv];
		admit(nod_v, nod_pv);

	}	

}

void preOrderTraversal(Node* r){
	if(r == NULL) return;
	cout << r->value << " ";
	Node* p = r->leftmost_child;
	if(p == NULL) return;
	preOrderTraversal(p);
	p = p->right_sibling;
	while(p != NULL){
		preOrderTraversal(p);
		p = p->right_sibling;
	}
}

void inOrderTraversal(Node* r){
	// TODO
}

void postOrderTraversal(Node* r){
	// TODO
}

int height(Node* p){// compute the height of the node pointed by p
	// TODO
}

int numberChildren(Node* p){// compute the number of descendants of p
	// TODO
}

void remove(int x,  Node* r){// remove node having value = x from the tree rooted by r
	// TODO
}

int maxNode(Node* r){// find the maximal value of nodes of the tree rooted by r
	// TODO
}

int computeSum(Node* r){// compute the sum of values of all nodes of the tree rooted by r
	// TODO
}

void print(Node* r, int d){
	if(d > 0){
		for(int i = 1;i<=d-1;i++) printf("|---");
	}
	
	printf("%d\n",r->value);
	Node* p = r->leftmost_child;
	int i = 1;
	while(p != NULL){
		print(p,d+1);
		p = p->right_sibling;
		i++;
	}	
}

Node* find(int x, Node* r){
	if(r == NULL) return NULL;
	if(r->value == x) return r;
	Node* p = r->leftmost_child;
	//Node* node = find(p);
	//if(node != NULL) return node;
	while(p != NULL){
		Node* node = find(x,p);
		if(node != NULL) return node;
		p = p->right_sibling;
	}
	return NULL;
}

void addNode(int x, Node* r){
	// add a new node with label x to the children of r
	Node* p = new Node;
	p->value = x;
	p->leftmost_child = NULL;
	p->right_sibling = NULL;
	
	if(root == NULL && r == NULL){
		root = p;
	}else{
		Node* pi = r->leftmost_child;
		if(pi == NULL){
			r->leftmost_child = p;
		}else{
			while(pi->right_sibling != NULL)
				pi = pi->right_sibling;
			pi->right_sibling = p;
		}
	}
}

void freeTree(Node* r){
	Node*p = r->leftmost_child;
	while(p != NULL){
		Node* next = p->right_sibling;
		freeTree(p);
		p = next;
	}
	delete r;
}

void swap(int& a, int& b){
	int tmp = a; a = b; b = tmp;
}



Node* free(Node* root){
	if(root == NULL)
		return NULL;
	root->right_sibling = free(root->right_sibling);
	Node* p = root->leftmost_child;
	root->leftmost_child = free(p);
	cout << "delete nod " << root->value << endl;
	delete root;
	
	return NULL;
}

int main(int argc, char** argv){
	if(argc != 2){
		cout << "Invalid Argument! (Argv 1 is file to read)" << endl;
		return 1;
	}
	readData(argv[1]);
	print(root,1);

	cout << "pre-order: ";
	preOrderTraversal(root);
	cout << endl;

	/*	
	cout << "in-order: ";
	inOrderTraversal(root);
	cout << endl;
	cout << "post-order: ";
	postOrderTraversal(root);
	cout << endl;
	root = free(root);
	return 0;
	*/


	/*
	int a = 3;
	int b = 2;
	swap(a,b);
	printf("a = %d b = %d\n",a,b);
	
	while(1){
		int x;
		printf("Nhap x = ");
		scanf("%d",&x);
		if(x == 0) break;
		
		int node;
		printf("Nhap nut de them nut con = ");
		scanf("%d",&node);
		Node* p = find(node,root);
		//if(p == NULL) printf("Cannot find node %d\n",node);
		//else {
			printf("addNode %d as a child of %d\n",x,node);
			addNode(x,p);
			print(root,0);
			printf("**************************************************************\n");
		//}
	}
	
	print(root,1);
	
	printf("Press enter to finish\n");
	freeTree(root);
	//getch();
	*/
}
