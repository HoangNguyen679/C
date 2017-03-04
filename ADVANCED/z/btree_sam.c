#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEVEL 1000
typedef enum bool
  {
    true,false
  } bool;

typedef struct _BTreeNode
{
  bool leaf;
  float *key;
  int numkey;
  int minfac;
  struct _BTreeNode *child[MAX_LEVEL];
} BTreeNode;

typedef struct _BTree
{
  BTreeNode *root;
} BTree;

BTree *curtree;
int t = -1; //facetor

bool fequal(float a, float b)
{
  float precision = 0.0000000001;
  return fabs(a-b) < precision;
}

bool FloatCompare(float f1, float f2)
{
  float precision = 0.0000000001;
  if((f1-precision) > f2)
    return true;
  else
    return false;
}

BTreeNode *AllocatedNode(BTreeNode *p, bool leaf)
{
  p = (BTreeNode *)malloc(sizeof(BTreeNode));
  p->leaf = leaf;
  p->minfac = t;
  p->key = (float *)malloc((2*t) * sizeof(float));
  p->numkey = 0;
  int i = 1;
  for(i = 1; i < p->minfac + 1; i++)
    p->child[i] = NULL;
  return p;
}

BTree *BTreeCreate(BTree *p)
{
  AllocatedNode(p->root,true);
}

void BTreeSplitChild(BTreeNode *x, int i, BTreeNode *y)
{
  BTreeNode *z;
  int j, Ldiv2;
  if( t%2 != 0)
    Ldiv2 = t/2 + 1;
  else
    Ldiv2 = t/2;

  z = AllocatedNode(z,y->leaf);
  z->numkey = t - Ldiv2 - 1;
  for(j = 1; j < z->numkey + 1; j++)
    z->key[j] = y->key[j + Ldiv2];

  if(y->leaf == false)
    {
      for(j = 1; j < z->numkey + 2; j++)
	z->child[j] = y->child[j + Ldiv2];
    }
  y->numkey = Ldiv2 - 1;
  for(j = x->numkey +1; j > i; j--)
    x->child[j+1] = x->child[j];
  x->child[i+1] = z;

  for(j = x->numkey +1; j > i-1; j--)
    x->key[j+1] = x->key[j];
  x->key[i] = y->key[Ldiv2];
  x->numkey += 1;
}

void BTreeInsert(BTree *tree,float k)
{
  
}

void preorderBTree(BTreeNode *root)
{
  
}

void inorderBTree(BTreeNode *root)
{
  
}

void postorderBTree(BTreeNode *root)
{
  
}

int main()
{
  int n = 12;
  int A[12] = {72,59,36,14,86,54,20,77,79,49,48,54};

  int j;
  t = 5;
  curtree = BTreeCreate(curtree);
  for(j = 0; j < n; j++)
    {
      printf("%d\n",A[j]);
      BTreeInsert(curtree,A[j]);
    }
  preorderBTree(curtree->root);
  return 0;
}
