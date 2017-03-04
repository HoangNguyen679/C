#include<stdio.h>
#include<stdlib.h>

typedef int  elementtype;
typedef struct node
{
  elementtype data;
  struct node *left,*right;
}node;

node *creat(elementtype x)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->data=x;
  new->left=NULL;
  new->right=NULL;
  return new;
}

void inorder(node *root)
{
  if(root != NULL)
    {
      printf("(");
      inorder(root->left);
      printf("%4d",root->data);
      inorder(root->right);
      printf(")");
    }
}

void preorder(node *root)
{
  if(root != NULL)
    {
      printf("%4d",root->data);
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
      printf("%4d",root->data);
    }
}

void freetree(node *tree)
{
  if (tree == NULL) return;
  free(tree->left);
  free(tree->right);
  free(tree);
  return;
}

node *insert(node *tree,elementtype x)
{
  node *new=NULL;
  if(tree == NULL) return creat(x);
  else if(x < tree->data)
    tree->left=insert(tree->left,x);
  else if(x > tree->data)
    tree->right=insert(tree->right,x);
  return tree;
}

void show(node *tree,int n)
{
  int i;
  if(tree!=NULL)
    {
      show(tree->left,n-1);
      for(i=0;i<n-1;i++) printf("%3s"," ");
      printf("%3d",tree->data);
      show(tree->right,n-1);
    }
}

node *search(node *tree, elementtype x)
{
  if(tree != NULL)
    if(x < tree->data)
      tree = search(tree->left,x);
    else if (x > tree->data)
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
  else if (x < tree->data)
    tree->left = delete(tree->left,x);
  else if (x > tree->data)
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
