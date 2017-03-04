#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct
{
  int maso ;
  char dochoi[30];
}infodochoi;

typedef infodochoi  elementtype;

typedef struct node
{
  elementtype data;
  struct node *left,*right;
}node;

int isEmptyTree(node* T)
{ return T == NULL;}

node* leftChild(node* T)
{ if(T != NULL) return T->left; return NULL;}

node* rightChild(node* T)
{ if(T != NULL) return T->right; return NULL;}

int isLeaf(node* T)
{
  if(T != NULL)
    return (leftChild(T) == NULL) && (rightChild(T) == NULL);
  return -1;
}

int nofNode(node *T)
{
  if(T == NULL) return 0;
  return 1 + nofNode(T->left) + nofNode(T->right) ;
}
int max(int a, int b)
{ return a > b ? a : b ;}

int min(int a, int b)
{ return a < b ? a : b ;}

int high(node *root)
{
  if(root == NULL) return 0;
  else return 1+ max(high(root->left),high(root->right));
}

int position(node *root, node *cur)
{
  if (cur == root || root == NULL) return 0;
  else return 1 + min(position(root->left,cur),position(root->right,cur));
}
//////////////////////////////////////////////////////////////////////////////////////////////////  CREAT
node *creat(elementtype x)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->data=x;
  new->left=NULL;
  new->right=NULL;
  return new;
}
//////////////////////////////////////////////////////////////////////////////////////////////////  MERGE
node *merge(elementtype x,node *tree1,node *tree2)
{
  node *new;
  new=creat(x);
  new->left=tree1;
  new->right=tree2;
  return new;
}
////////////////////////////////////////////////////////////////////////////////////////////////// INORDER
void inorder(node *root)
{
  if(root != NULL)
    {
      inorder(root->left);
      printf("%4d\t%-30s\n",root->data.maso,root->data.dochoi);
      inorder(root->right);
    }
}

void preorder(node *root)
{
  if(root != NULL)
    {
      printf("%4d\t%-30s\n",root->data.maso,root->data.dochoi);
      preorder(root->left);
      preorder(root->right);
    }
}

void postorder(node *root)
{
  if(root != NULL)
    {
      postorder(root->left);
      postorder(root->right);
      printf("%4d\t%-30s\n",root->data.maso,root->data.dochoi);
    }
}


node *insert(node *tree,elementtype x)
{
  node *new=NULL;
  if(tree==NULL) return creat(x);
  if(tree!=NULL)
    if(x.maso < tree->data.maso)
      tree->left=insert(tree->left,x);
    else
      tree->right=insert(tree->right,x);
  return tree;
}

node *search(node *tree, infodochoi x)
{
  if(tree != NULL)
    if(x.maso < tree->data.maso)
      tree = search(tree->left,x);
    else if (x.maso > tree->data.maso)
      tree = search(tree->right,x);
  return tree;
}

//////////////////////////////////////////////////////////////////////////////////////////////////  FINDMIN
node *find_min(node *tree)
{
  if (tree == NULL) return NULL;
  if(tree->left == NULL) return tree;
  else return find_min(tree->left);
}


node *find_max(node *tree)
{
  if(tree != NULL)
    while(tree->right != NULL)
      tree = tree->right;
  return tree;
}



node * delete(node *tree,infodochoi x)
{
  node *tmp;
  if(tree == NULL) printf("Not found\n");
  else if (x.maso < tree->data.maso)
    tree->left = delete(tree->left,x);
  else if (x.maso > tree->data.maso)
    tree->right = delete(tree->right,x);
  else
    if (tree->left && tree->right)
      {
        tmp = find_min(tree->right);
        tree->data = tmp->data;
        tree->right = delete(tree->right,tree->data);
      }
    else
      {
        tmp = tree;
        if (tree->left == NULL)
          tree = tree->right;
        else if (tree->right == NULL)
          tree = tree->left;
        free(tmp);
      }
  return tree;
}

//////////////////////////////////////////////////////////////////////////////////////////////////  FREE
void freetree(node *tree)
{
  if (tree == NULL) return;
  free(tree->left);
  free(tree->right);
  free(tree);
  return;
}
