#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 81

typedef struct
{
  char ten[MAX];
  double diem;
}infosv;
typedef infosv elementtype;
typedef struct node
{
  elementtype data;
  struct node *next;
}node;

node *makeNewNode(elementtype e)
{
  node *new;
  new = (node *)malloc(sizeof(node));
  new->data = e;
  new->next = NULL;
}

int is_empty(node *root)
{
  return !root ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////   INSERT
node *insert(node **root, node** cur, node** prev,elementtype e)
{
  node *new = makeNewNode(e);
  if(*root == NULL)
    {
      new->next = *root;
      *root = new;
      *cur = new;
      *prev = NULL;
      return *root;
    }
  node *temp= *root,*temp2=*root;
  while (e.diem >= (temp)->data.diem)
    {
      if (temp->next != NULL) temp = temp->next;
      else
        {
          new->next = NULL;
          temp ->next = new;
          (*prev) = temp;
          (*cur) = new;
          return new;
        }
    }
  if(temp == *root)
    {
      new->next = temp;
      *root = new;
      (*prev) = NULL;
      (*cur)=new;
      return new;
    }
  for(;temp2->next != temp; temp2 = temp2->next);
  (*prev) = temp2;
  temp2->next = new;
  new->next = temp;
  (*cur)=new;
  return new;
}
////////////////////////////////////////////////////////////////////////////////////////////////////  DELETE
node *deleteFirst(node **root, node** cur, node** prev){
	if(*root == NULL){
		printf("Empty list\n");
		return;
	}
	node *del = NULL;
	del = *root;
	*root = (*root)->next;
	free(del);
	*cur = *root;
	return *root;
}

node *deleteCur(node **root, node** cur, node** prev){
	if(*root == NULL){
		printf("Empty list\n");
		return;
	}
	node *del;
	del = *cur;
	(*prev)->next = (*cur)->next;
	*cur = (*cur)->next;
	free(del);
	return *root;
}

node *deleteLast(node **root, node** cur, node** prev){
	if(*root == NULL){
		printf("Empty list\n");
		return;
	}
	node *temp = NULL;
	for(temp = *root; temp->next != NULL; temp = temp->next);
	*cur = temp;
	deleteCur(root,cur,prev);
	return *root;
}

node *delete_position(node **root, node** cur, node** prev,int n){
  if(*root == NULL)
    {printf("Empty list\n"); return;}
  if(n == 0)
    {printf("Error\n"); return; }
  int i=0;
  node *temp =  *root;
  for(i = 0; i < n; i++) temp = temp->next;
  *cur = temp ;
  deleteCur(root,cur,prev);
  return *root;
}
/*
node *delete(node **root, node** cur, node** prev,elementtype e)
{
  if(*root == NULL)
    {printf("Empty list\n"); return;}
  node *temp= *root,*temp2=*root;
  while (e.key != (temp)->data.key)
    {
      if (temp->next != NULL) temp = temp->next;
      else
        {
          printf("NOT FOUND\n");
          return *root;
        }
    }
  node *del;
  if(temp == *root)
    {
      (*cur)=(*root) = (*root)->next;
      (*prev) = NULL;
      free(temp);
      return *root;
    }
  for(;temp2->next != temp; temp2 = temp2->next);
  temp2->next = temp->next;
  free(temp);
  (*cur)=(*root);
  (*prev)=NULL;
  return *root;
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////  PRINT
void printNode(node *p)
{
  if(p == NULL)
    {printf("Error NULL pointer\n");return;}
  printf("%-25s\t%4.1f\n",p->data.ten,p->data.diem);
}

void printList(node *root)
{
  node *p = NULL;
  if(root == NULL)
    {printf("Empty list\n");return;}
	for(p = root; p != NULL; p = p->next)
      printNode(p);
    return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////  FREE
void freeList(node **root)
{
  node* to_free;
  to_free = *root;
  while(to_free != NULL)
    {
      *root = (*root)->next;
      free(to_free);
      to_free = *root;
	}
}
