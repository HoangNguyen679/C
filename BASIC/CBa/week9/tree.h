#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char elementtype;
typedef struct node
{
  elementtype data[20];
  struct node *left,*right;
}node;
typedef node *treetype;

void makeNullTree(treetype *T);

int isEmptyTree(treetype T);

treetype leftChild(treetype T);

treetype rightChild(treetype T);

node *createNewNode(elementtype x);

int isLeaf(treetype T);

int nb_nodes(treetype T);

treetype creatfrom2(elementtype x, treetype l, treetype r);

treetype add_Left(treetype *T, elementtype x);

treetype add_Right(treetype *T, elementtype x);

int delph(treetype T);

void printPreorder(treetype T);

void makeNullTree(treetype *T)
{
  (*T) = NULL;
}

int isEmptyTree(treetype T)
{
  return T == NULL;
}

treetype leftChild(treetype T)
{
  if(T != NULL) return T->left;
  return NULL;
}

treetype rightChild(treetype T)
{
  if(T != NULL) return T->right;
  return NULL;
}

node *createNewNode(elementtype x)
{
  node *n;
  n = (node *)malloc(sizeof(node));
  if(n != NULL)
    {
      n->left = NULL;
      n->right = NULL;
      n->data = x;
    }
  return n;
}

int isLeaf(treetype T)
{
  if(T != NULL)
    return (leftChild(T) == NULL) && (rightChild(T) == NULL);
  return -1;
}

int nb_nodes(treetype T)
{
  if(isEmptyTree(T)) return 0;
  return 1 + nb_nodes(leftChild(T)) + nb_nodes(rightChild(T));
}

treetype creatfrom2(elementtype x, treetype l, treetype r)
{
  treetype T;
  T = (node *)malloc(sizeof(node));
  strcpy(T->data,x);
  T->left = l;
  T->right = r;
  return T;
}

treetype add_Left(treetype *T, elementtype x)
{
  node *new = createNewNode(x);
  if(new == NULL) return new;
  if((*T) == NULL)
    (*T) = new;
  else
    {
      node *Lnode = (*T);
      while(Lnode->left != NULL)
        Lnode = Lnode->left;
      Lnode->left = new;
    }
  return new;
}

treetype add_Right(treetype *T, elementtype x)
{
  node *new = createNewNode(x);
  if(new == NULL) return new;
  if((*T) == NULL)
    (*T) = new;
  else
    {
      node *Rnode = (*T);
      while(Rnode->right != NULL)
        Rnode = Rnode->right;
      Rnode->right = new;
    }
  return new;
}

int delph(treetype T)
{
  if(T == NULL) return 0;
  int ld = delph(T->left);
  int rd = delph(T->right);
  return 1 + (ld > rd ? ld : rd);
}

void printPreorder(treetype T)
{
  if(T != NULL)
    {
      printf("%s\n",T->data);
      printPreorder(T->left);
      printPreorder(T->right);
    }
}
