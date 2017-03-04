#include<stdio.h>
#include<stdlib.h>
#define MAX 80
typedef char add;
typedef struct node
{add data;struct node *left,*right;}node;
//Binary Tree 's Functions
node *creat(add data)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->data=data;
  new->left=NULL;
  new->right=NULL;
  return new;
}
int isleaf(node *tree)
{
  if(tree!=NULL)
    {if(tree->left==NULL&&tree->right==NULL) return 1;}
  else return 0;
}
int nofNode(node *tree)
{
  if(tree==NULL) return 0;
  else return (1+nofNode(tree->left)+nofNode(tree->right));
}
node *merge(add data,node *tree1,node *tree2)
{
  node *new;
  new=creat(data);
  new->left=tree1;
  new->right=tree2;
  return new;
}
int max(int a,int b)
{if(a>b) return a; else return b;}
int min(int a,int b)
{if(a<b) return a;else return b;}
int high(node *root)
{
  if(root==NULL) return 0;
  else return  1+max(high(root->left),high(root->right));
}
int position(node *cur,node *root)
{
  if(cur==root||root==NULL) return 0;
  else return 1+min(position(cur,root->left),position(cur,root->right));
}
void preoder(node *root)
{
  if(root!=NULL)
    {printf("%3c",root->data);
      preoder(root->left);
      preoder(root->right);
    }
}
void inoder(node *root)
{
  if(root!=NULL)
    {
      printf("(");
      inoder(root->left);
      printf("%3c",root->data);
      inoder(root->right);
      printf(")");
    }
}
void postoder(node *root)
{
  if(root!=NULL)
    {   postoder(root->left);
      postoder(root->right);
      printf("%3c",root->data);
    }
}
//Binary Search Tree 's Function
node *insert(node *tree,add data)
{
  node *new=NULL;
  if(tree==NULL) return creat(data);
  if(tree!=NULL)
    if(data<tree->data)
      if(tree->left==NULL)
        tree->left=creat(data);
      else
        tree->left=insert(tree->left,data);
    else
      if(tree->right==NULL)
        tree->right=creat(data);
      else
        tree->right=insert(tree->right,data);
  return tree;
}
