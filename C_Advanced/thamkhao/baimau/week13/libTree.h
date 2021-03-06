#include<stdio.h>
#include<stdlib.h>
typedef int add;
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
node *makefull(node *tree,int n,add data)
{
  if(n==0) tree=creat(data);
  else
    {
      tree=creat(data);
      tree->left=makefull(tree->left,n-1,data);
      tree->right=makefull(tree->right,n-1,data);
    }
  return tree;
}
int isleaf(node *tree)
{
  if(tree!=NULL)
    {if((tree->left==NULL)&&(tree->right==NULL)) return 1;}
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
int high(node *root)
{
  if(root==NULL) return 0;
  else return  1+max(high(root->left),high(root->right));
}
//Binary Search Tree 's Function
int cmp(add data1,add data2)
{
  if(data1<data2) return -1;
  else
    if(data1==data2) return 0;
    else return 1;
}
node *insert(node *tree,add data)
{
  node *new=NULL;
  if(tree==NULL) return creat(data);
  if(tree!=NULL)
    if(cmp(data,tree->data)<0)
      tree->left=insert(tree->left,data);
    else
      tree->right=insert(tree->right,data);
  return tree;
}
node *search(node *tree,add data)
{
  if(tree!=NULL)
    if(cmp(data,tree->data)==0) return tree;
    else
      if(cmp(data,tree->data)<0) return search(tree->left,data);
      else return search(tree->right,data);
  else
    return NULL;
}
node *leftTree(node *tree)
{
  if(tree!=NULL)
    if(tree->left==NULL) return tree;
    else return leftTree(tree->left);
}
node *del(node *tree,add data)
{
  node *tmp,*n_del;
  if((tmp=search(tree,data))==NULL) return tree;
  else
    if(isleaf(tmp)==1) tmp=NULL;
    else
      {
        if(tmp->left==NULL) tmp=tmp->right;
        else
          if(tmp->right==NULL) tmp=tmp->left;
          else
            {
              leftTree(tmp->right)->left=tmp->left;
              tmp=tmp->right;
            }
      }
  return tree;
}
