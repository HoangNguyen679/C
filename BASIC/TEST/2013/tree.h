#include<stdio.h>
#include<stdlib.h>
#define MAX 81
/////////////////////////////////////////////////////////////////////////////////////////////////////////// khai bao
typedef struct
{
  char ma[10];
  int diem;
}soccer_data;

typedef soccer_data  elementtype;

typedef struct node
{
  elementtype data;
  struct node *left,*right;
}node;
////////////////////////////////////////////////////////////////////////////////////////////////////// cac ham co ban
int isEmptyTree(node* T)
{
  return T == NULL;
}

node* leftChild(node* T)
{
  if(T != NULL) return T->left;
  return NULL;
}

node* rightChild(node* T)
{
  if(T != NULL) return T->right;
  return NULL;
}

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
//////////////////////////////////////////////////////////////////////////////////////////////////////// tao node moi
node *creat(elementtype x)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->data=x;
  new->left=NULL;
  new->right=NULL;
  return new;
}
////////////////////////////////////////////////////////////////////////////////////////////////////// ghep cay to tu hai cay con
node *merge(elementtype x,node *tree1,node *tree2)
{
  node *new;
  new=creat(x);
  new->left=tree1;
  new->right=tree2;
  return new;
}

int max(int a, int b)
{
  return a > b ? a : b ;
}

int min(int a, int b)
{
  return a < b ? a : b ;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////// chieu cao cua cay
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
///////////////////////////////////////////////////////////////////////////////////////////////////// duyet cay theo cac thu tu
void inorder(node *root)
{
  if(root != NULL)
    {
      inorder(root->left);
      printf("%13s\t%3d\n",root->data.ma,root->data.diem);
      inorder(root->right);
    }
}

void preorder(node *root)
{
  if(root != NULL)
    {
      printf("%13s\t%3d\n",root->data.ma,root->data.diem);
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
      printf("%13s\t%3d\n",root->data.ma,root->data.diem);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////  insert
node *insert(node *tree,soccer_data data)
{
  node *new=NULL;
  if(tree==NULL) return creat(data);
  if(tree!=NULL)
    if(strcmp(data.ma,tree->data.ma) < 0)
      tree->left=insert(tree->left,data);
    else
      tree->right=insert(tree->right,data);
  return tree;
}

//////////////////////////////////////////////////////////////////////////////////////////////// search
node *search(node *tree, soccer_data x)
{
  if(tree != NULL)
    if(strcmp(x.ma,tree->data.ma) < 0)
      tree = search(tree->left,x);
    else if (strcmp(x.ma,tree->data.ma) > 0)
      tree = search(tree->right,x);
  return tree;
}

///////////////////////////////////////////////////////////////////////////////////////////////////  delete

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

node * delete(node *tree,soccer_data x)
{
  node *tmp;
  if(tree == NULL) printf("Not found\n");
  else if (strcmp(x.ma,tree->data.ma) < 0)
    tree->left = delete(tree->left,x);
  else if (strcmp(x.ma,tree->data.ma) > 0)
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

///////////////////////////////////////////////////////////////////////////////////////////////  free
void freetree(node *tree)
{
  if (tree == NULL) return;
  free(tree->left);
  free(tree->right);
  free(tree);
  return;
}
void xoa(node *tree,int x,node *root)
{
  if(!isEmptyTree(root))
    {
      xoa(tree,x,root->left);
      if(root->data.diem<x)
        {
          printf("%s\n",root->data.ma);
          tree=delete(tree,root->data);
        }
      xoa(tree,x,root->right);
    }
}
