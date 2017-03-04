#include<stdio.h>
#include<stdlib.h>

typedef char  elementtype;
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

node *creat(elementtype x)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->data=x;
  new->left=NULL;
  new->right=NULL;
  return new;
}

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

void inorder(node *root)
{
  if(root != NULL)
    {
      printf("(");
      inorder(root->left);
      printf("%4c",root->data);
      inorder(root->right);
      printf(")");
    }
}

void preorder(node *root)
{
  if(root != NULL)
    {
      printf("%4c",root->data);
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
      printf("%4c",root->data);
    }
}

//Binary Search Tree 's Function
node *insert(node *tree,elementtype x)
{
  node *new=NULL;
  if(tree==NULL) return creat(x);
  if(tree!=NULL)
    if(x < tree->data)
      if(tree->left==NULL)
        tree->left=creat(x);
      else
        tree->left=insert(tree->left,x);
    else
      if(tree->right==NULL)
        tree->right=creat(x);
      else
        tree->right=insert(tree->right,x);
  return tree;
}
