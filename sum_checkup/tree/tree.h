#include <stdio.h>
#include <stdlib.h>

typedef int  elementType;
typedef struct node {
  elementType elements;
  struct node *left,
  struct node *right;
} node;

///////////////////////////////////////////////// cay rong

int isEmpty(node* T){
  return (T == NULL);
}

///////////////////////////////////////////////// con trai 

node *leftChild(node* T){
  if(T != NULL) return T->left;
  else return NULL;
}

///////////////////////////////////////////////// con phai

node *rightChild(node* T){
  if(T != NULL) return T->right;
  else return NULL;
}

///////////////////////////////////////////////// ktra la

int isLeaf(node* T){
  if(T != NULL)
    return (leftChild(T) == NULL) && (rightChild(T) == NULL);
  else return -1;
}

/////////////////////////////////////////////////  so nut cua cay

int nofNode(node *T){
  if(T == NULL) return 0;
  else 
    return 1 + nofNode(T->left) + nofNode(T->right) ;
}

///////////////////////////////////////////////// tao cay

node *creat(elementType e)
{
  node *new;
  new = (node*)malloc(sizeof(node));
  new->elements = e;
  new->left = NULL;
  new->right = NULL;
  return new;
}

///////////////////////////////////////////////// gop cay

node *merge(elementType e,node *tree1,node *tree2)
{
  node *new;
  new = creat(x);
  new->left = tree1;
  new->right = tree2;
  return new;
}

///////////////////////////////////////////////// max, min

int max(int a, int b){
  return ((a > b) ? a : b) ;
}

int min(int a, int b){
  return ((a < b) ? a : b) ;
}

///////////////////////////////////////////////// chieu cao cay

int high(node *root)
{
  if(root == NULL) return 0;
  else 
    return 1+ max(high(root->left),high(root->right));
}

///////////////////////////////////////////////// vi tri tu goc den nut hien tai

int position(node *root, node *cur)
{
  if (cur == root || root == NULL) return 0;
  else 
    return 1 + min(position(root->left,cur),position(root->right,cur));
}

///////////////////////////////////////////////// duyet giua

void inorder(node *root){
  if(root != NULL) {
      inorder(root->left);
      printf("%4d\n",root->elements);
      inorder(root->right);
    }
}

///////////////////////////////////////////////// duyet thu tu truoc

void preorder(node *root){
  if(root != NULL){
      printf("%4d\n",root->elements);
      preorder(root->left);
      preorder(root->right);
    }
}

///////////////////////////////////////////////// duyet thu tu sau
void postorder(node *root){
  if(root != NULL) {
      postorder(root->left);
      postorder(root->right);
      printf("%4d\n",root->elements);
    }
}
//Binary Search Tree 's Function

///////////////////////////////////////////////// chen

node *insert(node *tree,elementType e){
  node *new = NULL;
  if(tree == NULL) return creat(e);
  if(tree != NULL)
    if(e < tree->elements) {
      if(tree->left == NULL)
        tree->left = creat(e);
      else
        tree->left = insert(tree->left,e);
    } else {
      if(tree->right == NULL)
        tree->right = creat(e);
      else
        tree->right = insert(tree->right,e);
    }
  return tree;
}

///////////////////////////////////////////////// in cay

void show(node *tree,int n){
  int i;
  if(tree!=NULL){
      show(tree->left, n-1);
      for(i = 0; i < n-1; i++) 
        printf("%3s"," ");
      printf("%3d",tree->elements);
      show(tree->right, n-1);
    }
}

///////////////////////////////////////////////// tim kiem 

node *search(node *tree, elementType e)
{
  if(tree != NULL)
    if(e < tree->elements)
      tree = search(tree->left,e);
    else if (e > tree->data)
      tree = search(tree->right,e);
  return tree;
}

///////////////////////////////////////////////// nut co gia tri nho nhat

node *findMin(node *tree){
  if (tree == NULL) return NULL;
  if (tree->left == NULL) return tree;
  else return find_min(tree->left);
}

///////////////////////////////////////////////// nut co gia tri lon nhat

node *findMax(node *tree){
  if(tree != NULL)
    while(tree->right != NULL)
      tree = tree->right;
  return tree;
}

///////////////////////////////////////////////// xoa cay

node *delete(node *tree, elementType e){
  node *tmp;
  if(tree == NULL) printf("Not found\n");
  else if (e < tree->data)
    tree->left = delete(tree->left,e);
  else if (e > tree->data)
    tree->right = delete(tree->right,e);
  else
    if (tree->left && tree->right){
        tmp = findMin(tree->right);
        tree->data = tmp->data;
        tree->right = delete(tree->right, tree->data);
      } else {
        tmp = tree;
        if (tree->left == NULL)
          tree = tree->right;
        else if (tree->right == NULL)
          tree = tree->left;
        free(tmp);
      }
  return tree;
}

void freeTree(node *tree)
{
  if (tree == NULL) return;
  free(tree->left);
  free(tree->right);
  free(tree);
  return;
}
