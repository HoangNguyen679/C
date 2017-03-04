#include<stdio.h>
#include<stdlib.h>
typedef struct {
  int inf;} KeyType;
typedef struct Node{
  KeyType key;
  struct node* left, right;} NodeType;
typedef Node* TreeType;

void InsertNode(KeyType x, TreeType *Root) {
  if(*Root==NULL) {
    /*Creat a new node for key x */
    *Root=(NodeType*)malloc(sizeof(NodeType));
    (*Root)->key=x;
    (*Root)->left=NULL;
    (*Root)->right=NULL;
  }
  else if(x<(*Root)->key) InsertNode(x,&(*Root)->left);
  else if(x>(*Root)->key) InsertNode(x,&(*Root)->right);}

TreeType Search(KeyType x, TreeType Root) {
  if(Root==NULL) return NULL; //Not found
  else if( Root->key==x) //foun x
    return Root;
  else if(Root->key<x) //continue searching in the right sub tree
    return Search(x,Root->right);
  else {  //continue searching in the left sub tree
    return Search(x,Root->left);}}


KeyType DeleteMin(TreeType *Root) {
  KeyType k;
  if((*Root)->left==NULL) {
    k=(*Root)->key;
    (*Root)=(*Root)->right;
    return k;}
  else
    return DeleteMin(&(*Root)->left);}
}

void DeleteNode(key x, TreeType *Root) {
  if(*Root!=NULL) 
    if(x<(*Root)->key) DeleteNode(x,&(*Root)->left)
      else if (x>(*Root)->key)
	DeleteNode(x,&(*Root)->right) ;
      else if(((*Root)->left==NULL)&&((*Root)->right==NULL))
	*Root=NULL;
      else if((*Root)->left==NULL)
	*Root=(*Root)->right;
      else if((*Root)->right==NULL)
	*Root=(*Root)->left;
      else (*Root)->key=DeleteMin(&(*Root)->right);}

TreeType findMin(TreeType *Root) {
  if(Root==NULL)
    return NULL;
  else 
    if(Root->left==NULL) 
      return Root;
  else 
    return findMin(Root->left);}

TreeType findMax(TreeType *Root) {
  if(Root==NULL)
    return NULL;
  else
    if(Root->right==NULL)
      return Root;
    else
      return findMax(Root->right);}


