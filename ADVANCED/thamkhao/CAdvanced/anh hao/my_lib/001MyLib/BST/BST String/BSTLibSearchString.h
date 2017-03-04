#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct nodeType_t{
	elementType element;
	struct nodeType_t *left, *right;
} nodeTree;

typedef struct treeType_t{
	nodeTree *root;
} treeType;


void InitTree(nodeTree **T);
int IsEmptyTree(nodeTree *T);
nodeTree *LeftChild(nodeTree *l);
nodeTree *RightChild(nodeTree *r);
nodeTree *MakeNewNodeTree(elementType e);
int IsLeaf(nodeTree *n);
int NumberNode(nodeTree *T);
nodeTree *CreatTreeFrom2Tree(nodeTree *l, nodeTree *r, elementType e);
nodeTree *AddMostLeft(nodeTree *T, elementType e);
nodeTree *AddMostRight(nodeTree *T, elementType e);
int HeightTree(nodeTree *T);
int NumberLeaf(nodeTree *T);
int NumberInternalNode(nodeTree *T);
int NumberRightChild(nodeTree *T, int *count);
int NumberLeftChild(nodeTree *T, int *count);
void InsertToBTS(nodeTree **T, elementType e);
void PreOrderTraverser(nodeTree *T);
void InOrderTraverser(nodeTree *T);
void PostOrderTraverser(nodeTree *T);
nodeTree *SearchTree(nodeTree *T, elementType key);
elementType DeleteMin (nodeTree **Root);
void DeleteNode(nodeTree **T, elementType key);
void PrintTree(nodeTree *T, int height);


void DeleteNode(nodeTree **T, elementType key){
	if (*T == NULL) {printf("Tree is Empty"); return;}
	if (strcmp(key.info,(*T)->element.info) == -1) {DeleteNode(&((*T)->left), key); return;}
	if (strcmp(key.info,(*T)->element.info) == 1) {DeleteNode(&((*T)->right), key); return;}
	if (IsLeaf(*T)) {free(*T); *T = NULL; return;}
	if ((*T)->left == NULL) {
		nodeTree *temp1 = *T;
		*T = (*T)->right;
		free(temp1);
		return;
	}
	if ((*T)->right == NULL) {
		nodeTree *temp1 = *T;
		*T = (*T)->left;
		free(temp1);
		return;
	}
	DeleteMin(T);
}

elementType DeleteMin (nodeTree **Root){
	elementType k;
	if ((*Root)->left == NULL){
		k = (*Root)->element;
		(*Root) = (*Root)->right;
		return k;
	}
	else return DeleteMin(&(*Root)->left);
}

void InitTree(nodeTree **T){
	*T = (nodeTree *)malloc(sizeof(nodeTree));
	(*T) = NULL;
	//(*T)->element.count = 0;
}

int IsEmptyTree(nodeTree *T){
	return (T == NULL);
}

nodeTree *LeftChild(nodeTree *l){
	if (l != NULL) return (l->left);
	else return NULL;
}

nodeTree *RightChild(nodeTree *r){
	if (r != NULL) return r->right;
	else return NULL;
}

nodeTree *MakeNewNodeTree(elementType e){
	nodeTree *newn = (nodeTree*)malloc(sizeof(nodeTree));
	newn->element = e;
	newn->left = NULL; newn->right = NULL;
	return newn;
}

int IsLeaf(nodeTree *n){
	if (n != NULL){
		return (LeftChild(n)==NULL && RightChild(n)==NULL);
	}
	return -1;
}

int NumberNode(nodeTree *T){
	if (T == NULL) return 0;
	return (NumberNode(T->left) + NumberNode(T->right) + 1);
}

nodeTree *CreatTreeFrom2Tree(nodeTree *l, nodeTree *r, elementType e){
	nodeTree *T = (nodeTree*)malloc(sizeof(nodeTree));
	T->element = e;
	T->left = l; T->right = r;
	return T;
}

nodeTree *AddMostLeft(nodeTree *T, elementType e){
	nodeTree *newn = MakeNewNodeTree(e);
	if (newn == NULL) return newn;
	if (T == NULL) T = newn;
	else {
		nodeTree *lmost = T;
		while(lmost != NULL) lmost = lmost->left;
		lmost = newn;
	}
	return newn;
}

nodeTree *AddMostRight(nodeTree *T, elementType e){
	nodeTree *newn = MakeNewNodeTree(e);
	if (newn == NULL) return newn;
	if (T == NULL) T = newn;
	else {
		nodeTree *rmost = T;
		while(rmost != NULL) rmost = rmost->right;
		rmost = newn;
	}
	return newn;
}

int HeightTree(nodeTree *T){
	if (T == NULL) return 0;
	return (HeightTree(T->left)> HeightTree(T->right)? HeightTree(T->left) +1: HeightTree(T->right)+1);
}

int NumberLeaf(nodeTree *T){
	if (T->left == NULL && T->right == NULL) return 1;
	if (T->left == NULL) return NumberLeaf(T->right);
	if (T->right == NULL) return NumberLeaf(T->left);
	return (NumberLeaf(T->left)+NumberLeaf(T->right));
}

int NumberInternalNode(nodeTree *T){
	if (T->left == NULL && T->right == NULL) return 0;
	if (T->left == NULL) return NumberLeaf(T->right)+1;
	if (T->right == NULL) return NumberLeaf(T->left)+1;
	return (NumberLeaf(T->left)+NumberLeaf(T->right));
}

int NumberRightChild(nodeTree *T, int *count){
	if (T == NULL) return 0;
	if (T->right != NULL) (*count)++;
	NumberRightChild(T->left, count);
	NumberRightChild(T->right, count);
}

int NumberLeftChild(nodeTree *T, int *count){
	if (T == NULL) return 0;
	if (T->left != NULL) (*count)++;
	NumberRightChild(T->left, count);
	NumberRightChild(T->right, count);
}


//////////////BST Functions

void InsertToBTS(nodeTree **T, elementType e){
	if (*T == NULL) {
		*T = MakeNewNodeTree(e);
		return;
	}
	if (strcmp(e.info,(*T)->element.info) == -1) {
		InsertToBTS(&(*T)->left, e);
		return;
	}
	if (strcmp(e.info,(*T)->element.info) == 1) {
		InsertToBTS(&(*T)->right, e);
		return;
	}
	if (strcmp(e.info,(*T)->element.info) == 0) {
		((*T)->element.count)++;
		return;
	}
}


void PreOrderTraverser(nodeTree *T){
	if (T == NULL) return;
	PrintDataTree(T->element);
	PreOrderTraverser(T->left);
	PreOrderTraverser(T->right);
}

void InOrderTraverser(nodeTree *T){
	if (T == NULL) return;
	InOrderTraverser(T->left);
	PrintDataTree(T->element);
	InOrderTraverser(T->right);
}

void PrintTree(nodeTree *T , int height){
	if (T == NULL) return;
	int i;

	PrintTree(T->left, height);
	nodeTree *p = T;
	for(i = 0; i < HeightTree(p); i++) printf("\t");
	PrintDataTree(T->element);
	printf("\n");
	PrintTree(T->right, height);
}


void PostOrderTraverser(nodeTree *T){
	if (T == NULL) return;
	PostOrderTraverser(T->left);
	PostOrderTraverser(T->right);
	PrintDataTree(T->element);
}

nodeTree *SearchTree(nodeTree *T, elementType key){
	nodeTree notFound;
	notFound.element.count = 0;
	if (T == NULL) return (&notFound);
	if (strcmp(key.info, T->element.info) == 0) return T;
	if (strcmp(key.info, T->element.info) == -1) return SearchTree(T->left, key);
	else return SearchTree(T->right, key);
}

void FreeTree(nodeTree **T){
	if (*T == NULL) return;
	FreeTree(&((*T)->left));
	FreeTree(&((*T)->right));
	nodeTree *temp;
	temp = *T;
	free(temp);
	*T = NULL;
}
