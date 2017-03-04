#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
typedef int elementType;
typedef struct node{
	elementType elements;
	int id;
	struct node *next;
} node;

///////////////////////////////////////////////////////////   MAKE NEW NODE

node *makeNewNode(elementType e,int key){
  node *new;
  new = (node *)malloc(sizeof(node));
  new->elements = e;
  new->id = key;
  new->next = NULL;

  return new;
}

int isEmpty(node *root){
  return !root ;
}

///////////////////////////////////////////////////////////   INSERT

node *insert(node **root, elementType e,int key) {
	node *new = makeNewNode(e,key);
	if(*root == NULL) {
		*root = new;
		return new;
	}
	
	node *tmp = *root, *tmp1;
	while(key > tmp->id){
		tmp1 = tmp;
		if(tmp->next != NULL) tmp = tmp->next;
		else {
			tmp->next = new;
			return new;
		}
	}

	if(key == tmp->id){
		tmp->elements = e;
		return *root;
	}

	new->next = tmp;
	if(tmp == *root) {
		*root = new; 
	} else {
		tmp1->next = new;	
	}

	return new;
	
}

///////////////////////////////////////////////////////////   DELETE

node *delete(node **root, int key){
	if(*root == NULL){
		printf("Empty list\n");
		return NULL;
	}

	node *tmp = *root, *tmp1;
	while(key > tmp->id){
		tmp1 = tmp;
		if(tmp->next != NULL) tmp = tmp->next;
		else {
			return NULL;
		}
	}

	if(key == tmp->id){
		node *del;
		if(tmp == *root){
			del = *root;
			(*root) = (*root)->next;
			free(del);
			return *root;
		} else {
			del = tmp;
			tmp1->next = tmp->next;
			free(del);
			return *root;
		}
	}

}

node *freeALL(node **root){
	node *del;
	while(!isEmpty(*root)){
		del = *root;
		(*root) = (*root)->next;
		free(del);
	}
}

///////////////////////////////////////////////////////////   PRINT

void printNode(node *p)
{
  if(p == NULL) return;
  else printf("ID: %4d\tDATA: %d\n",p->id,p->elements);
}

void printList(node *root)
{
  if(root == NULL){
  	printf("Empty list\n");
  	return;
  }

  node *p = NULL;
	for(p = root; p != NULL; p = p->next)
      printNode(p);
   	printf("\n");
    return;
}
