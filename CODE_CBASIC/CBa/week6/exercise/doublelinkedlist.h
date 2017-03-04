#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX  81

typedef struct{
  char model[25];
  char rom[3];
  char screen[5];
  char price[8];
}info;

typedef info elementtype;

typedef struct node{
  elementtype e;
  node *prev;
  node *next;
};
typedef node *doublelist;

void MakeNullList (doublelist *root, doublelist *tail, doublelist *cur,doublelist*prev) {
  (*root) = NULL;
  (*tail) = NULL;
  (*cur) = NULL;
  (*prev) = NULL;
}

int isEmpty (doublelist root) {
  return (root == NULL);
}

node* MakeNewNode(elementtype e) {
  node* new = (node*)malloc(sizeof(node));
  new->e = e;
  new->next = NULL;
  new->prev = NULL;
  return new;
}

elementtype readNode() {
  elementtype tmp;
  printf("Name: ");gets(tmp.name);
  printf("Tel: ");gets(tmp.tel);
  printf("Email: ");gets(tmp.email);
  return tmp;
}

void displayNode(node *p) {
  elementtype tmp = p->e;
  if(p == NULL) {
    printf("Mistake pointer NULL\n");
    return;
  }
  printf("%-30s\t%-12s\t%-30s\n",tmp.name,tmp.tel,tmp.email);
}

void insertFirst(elementtype e, doublelist *root, doublelist *cur, doublelist *tail) {
  node* new = makeNewNode(e);
  *root = new;
  *cur = *root;
  new->next = (*cur)->next;
  if((*cur)->next != NULL)
    (*cur)->next->prev = new;
  if(new->next == NULL) *tail = new;
}

void insertAfterCurrent (elementtype e, doublelist *root, doublelist *cur, doublelist *tail) {
  node* new = makeNewNode(e);
  if(*root == NULL) {
    /*if there is no element */
    *root = new;
    *tail = new;
    *cur = *root;
  }
  else {
    new->next = (*cur)->next;
    if((*cur)->next != NULL)
      (*cur)->next->prev = new;
    new->prev = *cur;
    (*cur)->next = new;
    *cur = new;
    if(new->next == NULL) *tail = new;
  }
}

void insertEnd(elementtype e, doublelist *root, doublelist *cur, doublelist *tail) {
  if((*root) == NULL) {
    insertFirst(e,root,cur,tail);
    return;
  }
  node* new = makeNewNode(e);
  (*tail)->prev->next = new;
  new->prev = (*tail)->prev;
  tail->prev = new;
}

void insertBeforCurrent (elementtype e, doublelist *root, doublelist *cur, doublelist *tail) {
  node* new = makeNewNode(e);
  if(*root == NULL) {
    *root = new;
    *tail = new;
    *cur = *root;
  }
  else {
    if(*cur == NULL) {
      insertEnd(e,root,cur,end);
      return;
    } else {
      new->next = *cur;
      new->prev = *cur->prev;
      *cur->prev->next = new;
      *cur->prev = new;
    }
  }
}

void delFirst(doublelist *root){
  if(*root == NULL) {
    printf("List is empty\n");
    return;
  }
  doublelist *del;
  *del = *root;
  *root = (*del)->next;
  free(*del);
}

void delLast(doublelist *root,doublelist *cur,doublelist *tail){
  if(*root == NULL) {
    printf("List is empty\n");
    return;
  }
  if((*root)->next == NULL) {
    delFirst(root);
    return;
  }
  doublelist *del;
  *del = *tail;
  (*tail)->prev->next = NULL;
  *tail = *tail->prev;
  free(del);
}

void delCur(doublelist *root,doublelist *cur,doublelist *tail){
  if(*root == NULL) {
    printf("List is empty\n");
    return;
  }
  if(*cur == *root) {
    delFirst(root);
    return;
  }
  (*cur)->prev->next = (*cur)->next;
  (*cur)->next->prev = (*cur)->prev;
  (*cur) = (*cur)->prev;
}

void traversingList() {
  node*p;
  for(p = root ; p != NULL ; p = p->next)
    displayNode(p);
}
