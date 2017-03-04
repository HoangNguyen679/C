#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(a,b) (a > b ? a : b) 

typedef struct node {
	int bal; // chua dung
	int value ;
	struct node *left;
	struct node *right;
} avlTree;


/* the height of a node */
int height(avlTree *node){
	if(node == NULL) return 0;
	else 
		return 1 + MAX(height(node->left),height(node->right));
}

/* Creat new tree */
avlTree *create(){
	avlTree *T = (avlTree *)malloc(sizeof(avlTree));
	T->left = NULL;
	T->right = NULL;
	T->value = 0;
	T->bal = height(T->left) - height(T->right);

	return T;
}

/* ktra rong */
int isEmpty(avlTree *T){
	return !T;
}

/* the balance factor */
int balanceFactor(avlTree *node){
	return height(node->left) - height(node->right);
}

/* Left Rotation */
avlTree *leftRotate(avlTree *node){
	avlTree *tmp = node->right;
	node->right = tmp ->left;
	tmp->left = node;
	return tmp;
}

/* Right Rotation */
avlTree *rightRotate(avlTree *node){
	avlTree *tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	return tmp;
}

/* left -> right rotation */
avlTree *leftRightRotate(avlTree *node){
	node->left = leftRotate(node->left);
	return rightRotate(node);
}

/* right -> left rotation */
avlTree *rightLeftRotate(avlTree *node){
	node->right = rightRotate(node->right);
	return leftRotate(node);
}

/* make balance node*/
avlTree *balanceNode(avlTree *node){
	if(node->left) 
		node->left = balanceNode(node->left);
	if(node->right)
		node->right = balanceNode(node->right);
	
	avlTree *tmp;
	int factor = balanceFactor(node);
	if(factor >= 2){
		if(balanceFactor(node->left) > 0)
			tmp = rightRotate(node);
		else 
			tmp = leftRightRotate(node);
	} else if(factor <= -2) {
		if(balanceFactor(node->right) < 0)
			tmp = leftRotate(node);
		else 
			tmp = rightLeftRotate(node);
	} else tmp = node;

	return tmp;
}

/* tim kiem */
avlTree *find( avlTree *T, int value ) {
	avlTree *current = T;

	while( current && current->value != value ) {
		if( value > current->value )
			current = current->right;
		else
			current = current->left;
	}

	return current;
}

/* chen    */
avlTree *insert( avlTree *T, int value ) {
	avlTree *node = NULL;
	avlTree *next = NULL;
	avlTree *last = NULL;

	if( T == NULL ) {
		T = create();
		T->value = value;
	} else {
		next = T;

		if(value < T->value){
			if(T->left == NULL){
				T->left = create();
				T->left->value = value;
			} else {
				T->left = insert(T->left, value);
			}
		} else {
			if(T->right == NULL){
				T->right = create();
				T->right->value = value;
			} else {
				T->right = insert(T->right, value);
			}
		}
	}
	return T;
}

/* duyet cay */
void traverseDFS( avlTree *node, int n ) {
	int i = 0;
	if(node != NULL){
		if( node->left ) traverseDFS( node->left, n - 1 );
		for(i = 0; i < n-1; i++) 
        	printf("%3s"," ");
      	printf("%3d\n",node->value);
		if( node->right ) traverseDFS( node->right, n - 1 );
	}
}