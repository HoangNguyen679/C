#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 81
typedef struct
{
  char user[MAX];
  char pass[MAX];
  float diem;
}data_student;
typedef data_student elementtype;
typedef struct node
{
  elementtype data;
  struct node *left,*right;
}node;

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
////////////////////////////////////////////////////////// CREAT
node *creat(elementtype x)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->data=x;
  new->left=NULL;
  new->right=NULL;
  return new;
}
//////////////////////////////////////////////////////////// MERGE
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
/////////////////////////////////////////////////////////// Duyet cay

void inorder(node *root)
{
  if(root != NULL)
    {
      inorder(root->left);
      if(strcmp(root->data.user,"Admin") != 0)
        printf("%15s\t%10s\t%3.1f\n",root->data.user,root->data.pass,root->data.diem);
      inorder(root->right);
    }
}

void preorder(node *root)
{
  if(root != NULL)
    {
      printf("%15s\t%10s\t%3.1f\n",root->data.user,root->data.pass,root->data.diem);
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
      printf("%15s\t%10s\t%3.1f\n",root->data.user,root->data.pass,root->data.diem);
    }
}

/////////////////////////////////////////////////////// INSERT

node *insert(node *tree,elementtype x)
{
  if(tree==NULL) return creat(x);
  if(tree!=NULL)
    if(strcmp(x.user,tree->data.user) < 0)
      tree->left=insert(tree->left,x);
    else
      tree->right=insert(tree->right,x);
  return tree;
}

//////////////////////////////////////////////////// SEARCH

node *search(node *tree, elementtype x)
{
  if(tree != NULL)
    if(strcmp(x.user,tree->data.user) < 0)
      tree = search(tree->left,x);
    else if (strcmp(x.user,tree->data.user) > 0)
      tree = search(tree->right,x);
  return tree;
}

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
////////////////////////////////////////////////// DELETE

node * delete(node *tree,elementtype x)
{
  node *tmp;
  if(tree == NULL) printf("Not found\n");
  else if (strcmp(x.user,tree->data.user) < 0)
    tree->left = delete(tree->left,x);
  else if (strcmp(x.user,tree->data.user) > 0)
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

void freetree(node *tree)
{
  if (tree == NULL) return;
  free(tree->left);
  free(tree->right);
  free(tree);
  return;
}
