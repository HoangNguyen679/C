#include<stdio.h>
#include<stdlib.h>
#include"element.h"
typedef struct node
{elementtype data;struct node *next;}node;
//==========================================================
node *push(node *root,elementtype data);
node *pop(node *root,elementtype *data);
//==========================================================
//Push =====================================================
node *push(node *root,elementtype data)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  if(new==NULL)
    {printf("Stack is Full\n");return(root);}
  new->data=data;
  new->next=root;
  root=new;
  return root;
}
//Pop ======================================================
node *pop(node *root,elementtype *data)
{
  node *tmp;
  if(root==NULL) {printf("Stack is empty\n");return root;}
  tmp=root;root=root->next;*data=tmp->data;free(tmp);return root;
}
