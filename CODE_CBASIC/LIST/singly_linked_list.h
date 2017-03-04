#include<stdio.h>
#include<stdlib.h>

typedef long elementtype;
struct node {
	elementtype e;
	struct node *next;
};
typedef struct node node;

node *makeNewNode(elementtype e);

node *insertFirst(node **root, node** cur, node** prev,elementtype e);

node *insertLast(node **root, node** cur, node** prev,elementtype e);

node *insertBeforeCur(node **root, node** cur, node** prev,elementtype e);

node *insertAfterCur(node **root, node** cur, node** prev,elementtype e);

node *insert(node **root, node** cur, node** prev,elementtype e,int n);

node *deleteFirst(node **root, node** cur, node** prev);

node *deleteCur(node **root, node** cur, node** prev);

node *deleteLast(node **root, node** cur, node** prev);

node *delete(node **root, node** cur, node** prev,int n);

void freeList(node **root);

void printNode(node *p);

void printList(node *root);

int is_empty(node *root);



node *makeNewNode(elementtype e){
	node *new;
	new = (node *)malloc(sizeof(node));
	new->e = e;
	new->next = NULL;
}

node *insertFirst(node **root, node** cur, node** prev,elementtype e){
	node *new = makeNewNode(e);
	new->next = *root;
	*root = new;
	*cur = new;
	*prev = NULL;
	return *root;
}

node *insertLast(node **root, node** cur, node** prev,elementtype e){
	node *new = makeNewNode(e);
	node *temp = *root;
	while(temp->next != NULL) temp = temp->next;
	temp->next = new;
	*cur = new;
	*prev = temp;
	return new;
}

node *insertAfterCur(node **root, node** cur, node** prev,elementtype e){
	if(*root == NULL){
		insertFirst(root,cur,prev,e);
		return;
	}
	node *new = makeNewNode(e);
	new->next = (*cur)->next;
	(*cur)->next = new;
	*prev = *cur;
	*cur = new;
	return new;
}

node *insertBeforeCur(node **root, node** cur, node** prev,elementtype e){
	if(*root == NULL || *cur == *root){
		insertFirst(root,cur,prev,e);
		return;
	}
	node *new = makeNewNode(e);
	new->next = *cur;
	(*prev)->next = new;
	*cur = new;
	return new;
}

node *insert(node **root, node** cur, node** prev,elementtype e,int n){
	if(n == 0){
		insertFirst(root,cur,prev,e);
		return *root;
	}
	int i,num_node = 0;
	node *temp = NULL;
	for(temp = *root ; temp != NULL ; temp = temp->next) num_node++;
	if (n < 0) printf("Error %d < 0\n",n);
	else if(n > num_node){
		printf("Error overflow list\n");
		return *root;
	}
	temp = *root;
	for(i = 0; i < n; i++) temp = temp->next;
	*cur = temp;
	insertAfterCur(root,cur,prev,e);
	return *cur;
}

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

node *delete(node **root, node** cur, node** prev,int n){
  if(*root == NULL) { printf("Empty list\n"); return; }
  if(n == 0){ printf("Error\n"); return; }
  int i=0;
  node *temp = NULL; temp = *root;
  for(i = 0; i < n; i++) temp = temp->next;
  *cur = temp ;
  deleteCur(root,cur,prev);
  return *root;
}

int is_empty(node *root){
	return !root ;
}

void printNode(node *p){
	if(p == NULL){
		printf("Error NULL pointer\n");
		return;
	}
	printf("%ld\n",p->e);
}

void printList(node *root){
	node *p = NULL;
	if(root == NULL){
		printf("Empty list\n");
		return;
	}
	for(p = root; p != NULL; p = p->next){
      printf("%d\n",p->e);
	}
    return;
}

void freeList(node **root){
	node* to_free;
  	to_free = *root;
  	while(to_free != NULL) {
    *root = (*root)->next;
    free(to_free);
    to_free = *root;
	}
}
