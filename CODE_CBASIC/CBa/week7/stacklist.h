#include<stdio.h>
#include<stdlib.h>

struct node{
  int data;
  struct node *next;
};
typedef struct node stacknode;

stacknode *push(stacknode *p, int value) {
  stacknode *temp;
  temp=(stacknode*)malloc(sizeof(stacknode));
  if(temp == 0) {
    printf("No memory available error\n");
    return;
  }
  temp->data = value;
  temp->next = p;
  p = temp;
  return(p);
}

stacknode *pop(stacknode *p, int *value) {
  stacknode *temp;
  if(p == 0) {
    printf("The stack is empty can not pop! Error\n");
    return;
  }
  *value = p->data;
  temp = p;
  p = p->next;
  free(temp);
  return(p);
}
