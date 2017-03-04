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
int height, temp, numberOfChild;
int isRemove, maxVal, sum;
void admit(Node* v, Node* pv){
	// add pair v, pv into the tree, pv is the parent of v, v will be added in the right of chilrend list of pv
	if(pv == NULL) return;
	if(pv->leftmost_child == NULL){
		pv->leftmost_child = v;	
	} else {
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
		fscanf(f,"%d %d", &v, &pv);
		p[v] = pv;
		//cout << "read v = " << v << " pv = " << pv << endl;
	}		
	fclose(f);
	// building the tree with above data structure
	// Make New Node
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
	if(r == NULL) return;

	Node *p = r->leftmost_child;
	if(p == NULL){
		cout << r->value << " ";
		return;
	}
	inOrderTraversal(p);
	cout << r->value << " ";	
	p = p->right_sibling;
	while(p != NULL){
		inOrderTraversal(p);
		p = p->right_sibling;
	}
}

void postOrderTraversal(Node* r){
	if(r==NULL) return;
	Node *p=r->leftmost_child;
	while(p!=NULL){
        postOrderTraversal(p);
        p=p->right_sibling;
    }
    cout<< r->value <<" ";
}
int Height(Node* r){// compute the height of the node pointed by p
	if(r == NULL) return 0;
	Node *q= r->leftmost_child;
    int max = Height(q);
    while(q!=NULL){
        q=q->right_sibling;
        if( Height(q) > max ) max = Height(q);
    }
    return max+1;
}

int numberChildren(Node* r){// compute the number of descendants of p
	// TODO
	// We use pre Order Traversal to compute do this action
	if(r == NULL) return 0;
	numberOfChild++;	// plus temp when go to a child
	Node *p = r->leftmost_child;
	if(p == NULL){
		return 0;
	}
	numberChildren(p);
	p = p->right_sibling;
	while(p != NULL){
		numberChildren(p);
		p = p->right_sibling;
	}
	return numberOfChild;
}


void remove(int x,  Node* r){// remove node having value = x from the tree rooted by r HW
	if(r == NULL) return;
	if(r->value == x) {
		free(r);
		return;
	}
	Node* p = r->leftmost_child;
	while(p != NULL){
		remove(x,p);
		p = p->right_sibling;
	}
	return;
}



int maxNode(Node* r){// find the maximal value of nodes of the tree rooted by r
	// TODO
	if(r == NULL) return 0;

	if(maxVal < r->value) maxVal = r->value;

	Node* p = r->leftmost_child;
	if(p == NULL) return 0;
	maxNode(p);
	p = p->right_sibling;

	while(p != NULL){
		maxNode(p);
		p = p->right_sibling;
	}
	return maxVal;
}


int computeSum(Node* r){// compute the sum of values of all nodes of the tree rooted by r
	// TODO
	if(r == NULL) return 0;
	sum += r->value;

	Node* p = r->leftmost_child;
	if(p == NULL) return 0;
	computeSum(p);
	p = p->right_sibling;

	while(p != NULL){
		computeSum(p);
		p = p->right_sibling;
	}
	return sum;
}

void print(Node* r, int d){
	if(d > 0){
		for(int i = 1; i <= d-1; i++) printf("|---");
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
	int tmp = a;
	a = b;
	b = tmp;
}



Node* free(Node* root){
	if(root == NULL)
		return NULL;
	root->right_sibling = free(root->right_sibling);
	Node* p = root->leftmost_child;
	root->leftmost_child = free(p);
	cout << "delete node " << root->value << endl;
	delete root;
	return NULL;
}

int GetMenu(void);


int main(int argc, char** argv){
	if(argc != 2){
		cout << "Invalid Argument! (Argv 1 is file to read)" << endl;
		return 1;
	}
	readData(argv[1]);
	print(root,1); cout << endl;

	int menu;
	int valToRemove;

	do {
		cout <<endl; print(root,1); cout << endl;
		switch(menu = GetMenu()) {
			case 1:
			cout << "pre-order : ";
			preOrderTraversal(root);
			cout << endl;
			break;

			case 2:
			cout << "post-order: ";
			postOrderTraversal(root);
			cout << endl;
			break;

			case 3:
			cout << "in-order  : ";
			inOrderTraversal(root);
			cout << endl;
			break;

			case 4:
			height = temp = 0;
			cout << "Height of Tree: " << Height(root)+1 << endl;
			break;

			case 5:
			numberOfChild = 0;
			cout << "Number of Children of Tree: " << numberChildren(root) << endl;	
			break;

			case 6: maxVal = 0;
			cout << "Max Value in Tree: " << maxNode(root->leftmost_child->right_sibling) <<endl;
			break;

			case 7: sum = 0;
			cout << "Sum of All node in Tree: " << computeSum(root) <<endl;
			break;
			case 10: free(root); break;
		} 	
	} while(menu != 0);
	freeTree(root);
}


int GetMenu(void){
	int menu;
	do{
		printf("\n----MENU----\n");
		printf("1. Pre Order Traversal\n");
		printf("2. In Order Traversal\n");
		printf("3. Post Order Traversal\n");
		printf("4. Height of Tree\n");
		printf("5. Number of Children of Tree\n");
		printf("6. Max Value in Tree\n");
		printf("7. Sum of All node in Tree\n");
		printf("8. Remove a Node\n");
		printf("9. Find a Node\n");
		printf("10.Free Tree\n");
		printf("0. Exit\n");
		printf("Your choice: ");
		scanf("%d", &menu);
	}while(menu<0 || menu>10);
	return menu;
} 