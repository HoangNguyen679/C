#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 81

typedef struct {
  char mskh[MAX];
  char ten[MAX];
  double tien;
  int food,electronic,cloth;
}customer_info;

typedef customer_info  elementtype;
typedef struct node
{
  elementtype data;
  struct node *left,*right;
}node;
typedef node * treetype;

int isEmptyTree(node* tree)
{
  return tree == NULL;
}

node* leftChild(node* tree)
{
  if(tree != NULL) return tree->left;
  return NULL;
}

node* rightChild(node* tree)
{
  if(tree != NULL) return tree->right;
  return NULL;
}

int isLeaf(node* tree)
{
  if(tree != NULL)
    return (leftChild(tree) == NULL) && (rightChild(tree) == NULL);
  return -1;
}
// number of tree node
int nofNode(node *tree)
{
  if(tree == NULL) return 0;
  return 1 + nofNode(tree->left) + nofNode(tree->right) ;
}

int nof_leaf(node *tree)
{
  if(tree == NULL) return 0;
  if(isLeaf(tree)) return 1;
  else return nof_leaf(tree->left) + nof_leaf(tree->right);
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
////////////////////////////////////////////////////////////////////// add phan tu vao la tan cung ben trai
node * add_left(node **tree,elementtype x)
{
  node *new = creat(x);
  if(new == NULL) return NULL;
  if(*tree == NULL) *tree = new;
  else
    {
      node *Lnode = *tree;
      while(Lnode->left != NULL)
        Lnode = Lnode->left;
      Lnode->left = new;
    }
  return new;
}

////////////////////////////////////////////////////////////////////////// add phan tu vao la tan cung ben phai
node * add_right(node **tree,elementtype x)
{
  node *new = creat(x);
  if(new == NULL) return NULL;
  if(*tree == NULL) *tree = new;
  else
    {
      node *Rnode = *tree;
      while(Rnode->right != NULL)
        Rnode = Rnode->right;
      Rnode->right = new;
    }
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
////////////////////////////////////////////////////////////////////////duyet cay theo cac thu tu giua trc sau
void inorder(node *tree)
{
  if(tree != NULL)
    {
      inorder(tree->left);
      printf("%8s%20s%8.1f\t%5d\t%10d\t%6d\n",tree->data.mskh,tree->data.ten,tree->data.tien,tree->data.food,tree->data.electronic,tree->data.cloth);
      inorder(tree->right);
    }
}

void preorder(node *tree)
{
  if(tree != NULL)
    {
      printf("%8s%20s%8.1f\t%5d\t%10d\t%6d\n",tree->data.mskh,tree->data.ten,tree->data.tien,tree->data.food,tree->data.electronic,tree->data.cloth);
      preorder(tree->left);
      preorder(tree->right);
    }
}
void postorder(node *tree)
{
  if(tree != NULL)
    {
      postorder(tree->left);
      postorder(tree->right);
      printf("%8s%20s%8.1f\t%5d\t%10d\t%6d\n",tree->data.mskh,tree->data.ten,tree->data.tien,tree->data.food,tree->data.electronic,tree->data.cloth);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////insert
node *insert(node *tree,elementtype x)
{
  node *new=NULL;
  if(tree==NULL) return creat(x);
  if(tree!=NULL)
    if(strcmp(x.mskh,tree->data.mskh) < 0)
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
///////////////////////////////////////////////////////////////////////////////////////////search
node *search(node *tree, elementtype x)
{
  if(tree != NULL)
    if(strcmp(x.mskh,tree->data.mskh) < 0)
      tree = search(tree->left,x);
    else if (strcmp(x.mskh,tree->data.mskh) > 0)
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

node * delete(node *tree,elementtype x)
{
  node *tmp;
  if(tree == NULL) printf("Not found\n");
  else if (strcmp(x.mskh,tree->data.mskh) <0)
    tree->left = delete(tree->left,x);
  else if (strcmp(x.mskh,tree->data.mskh) >0)
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
