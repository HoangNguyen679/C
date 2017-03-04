#include<stdio.h>
#include<stdlib.h>
#include"element.h"
typedef struct node
{elementtype data;struct node *left,*right;}node;
//==========================================================
int max(int a,int b);
int cmp(elementtype data1,elementtype data2);
int isleaf(node *tree);
int nofnode(node *tree);
int high(node *tree);
node *left_node(node *tree);
node *creat(elementtype data);
node *makefulltree(node *tree,int n,elementtype data);
node *merge(elementtype data,node *tree1,node *tree2);
node *search(node *tree,elementtype data);
node *insert(node *tree,elementtype data);
node *del(node *tree,elementtype data);
void freeTree(node *tree);
void show(node *tree,int n);
void print(elementtype data);
//==========================================================
//Create ===================================================
node *creat(elementtype data)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->data=data;
  new->left=NULL;
  new->right=NULL;
  return new;
}
//MakeFull =================================================
node *makefull(node *tree,int n,elementtype data)
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
//IsLeaf ===================================================
int isleaf(node *tree)
{
  if(tree!=NULL)
    if((tree->left==NULL)&&(tree->right==NULL)) return 1;
    else return 0;
}
//Number of Node ===========================================
int nofNode(node *tree)
{
  if(tree==NULL) return 0;
  else return (1+nofNode(tree->left)+nofNode(tree->right));
}
//Merge ====================================================
node *merge(elementtype data,node *tree1,node *tree2)
{
  node *new;
  new=creat(data);
  new->left=tree1;
  new->right=tree2;
  return new;
}
//Max ======================================================
int max(int a,int b)
{
  if(a>b) return a; else return b;
}
//High =====================================================
int high(node *root)
{
  if(root==NULL) return 0;
  else return  1+max(high(root->left),high(root->right));
}
//Insert ===================================================
node *insert(node *tree,elementtype data)
{
  node *new=NULL;
  int i;
  if(tree==NULL) return creat(data);
  if(tree!=NULL)
    if((i=cmp(data,tree->data))<0)
      tree->left=insert(tree->left,data);
    else
      if(i>0)
        tree->right=insert(tree->right,data);
      else
        if(i==0)
          tree->data=data;
  return tree;
}
//Search ===================================================
node *search(node *tree,elementtype data)
{
  if(tree!=NULL)
    if(cmp(data,tree->data)==0) return tree;
    else
      if(cmp(data,tree->data)<0) return search(tree->left,data);
      else return search(tree->right,data);
  else
    return NULL;
}
//Del Min ==================================================
node *left_node(node* tree)
{
  while(tree->left!=NULL)
    {tree=tree->left;}
  return tree;
}
//Delete ===================================================
node *del(node *tree,elementtype data)
{
  node *tmp,*t;
  int i;
  if(tree!=NULL)
    {if((i=cmp(tree->data,data))<0) tree->right=del(tree->right,data);
      else
        if(i>0) tree->left=del(tree->left,data);
        else
          {
            if(tree->right==NULL)
              {tmp=tree;tree=tree->left;free(tmp);}
            else
              if(tree->left==NULL)
                {tmp=tree;tree=tree->right;free(tmp);}
              else
                {
                  tree->data=left_node(tree->right)->data;
                  tree->right=del(tree->right,tree->data);
                }
          }
    }
  return tree;
}
//Free =====================================================
void freeTree(node *tree)
{
  if(tree!=NULL)
    {
      freeTree(tree->left);
      freeTree(tree->right);
      free(tree);
    }
}
//Show =====================================================
void show(node *tree,int n)
{
  int i;
  if(tree!=NULL)
    {
      show(tree->left,n-1);
      for(i=0;i<n-1;i++) printf("%10s"," ");
      print(tree->data);
      show(tree->right,n-1);
    }
}
