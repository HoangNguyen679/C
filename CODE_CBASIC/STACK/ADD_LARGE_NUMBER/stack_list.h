#include<stdio.h>
#include<stdlib.h>

typedef int elementtype;
typedef struct stackNode{
  elementtype e;
  struct stackNode *next;
}stackNode;
struct stack{
  stackNode *top;
};
typedef struct stack stack;

stack *stackConstruct();

int isEmpty(stack *s);

int isFull();

int push(stack *s, elementtype e);

elementtype pop(stack *s);

void printStack(stack *s);

stack *stackConstruct(){
  stack *s;
  s = (stack *)malloc(sizeof(stack));
  if(s == NULL) return NULL;
  s->top = NULL;
  return s;
}

int isEmpty(stack *s){
  return (s->top == NULL);
}

int isFull(){
  printf("\n NO MEMORY! STACK IS FULL\n");
  return 1;
}

int push(stack *s, elementtype e){
  stackNode *node;
  node = (stackNode *)malloc(sizeof(stackNode));
  if (node == NULL) {
    isFull();
    return 1;
  }
  node->e = e;
  node->next = s->top;
  s->top = node;
  return 0;
}
elementtype pop(stack *s){
  elementtype e;
  stackNode *node;
  if(isEmpty(s)){ printf("\nEMPTY STACK\n"); return ; }
  node = s->top;
  e = node->e;
  s->top = node->next;
  free(node);
  return e;
}

void printStack(stack *s){
  stackNode *node; int m;
  if(isEmpty(s)){
    printf("\n\n >>>>> EMPTY STACK <<<<<\n\n");
    return;
  }
  node = s->top;
  do{
    m = node->e ;printf("%d",m);
    node = node->next;
  } while( !(node == NULL));
  printf("\n");
}

void printStackMinus(stack *s){
  stackNode *node; int m;
  if(isEmpty(s)){
    printf("\n\n >>>>> EMPTY STACK <<<<<\n\n");
    return;
  }
  node = s->top;
  m = node->e ; if(m != 0){printf("%d",m);node=node->next;} else node =node->next;
  do{
    if(node != NULL){
      m = node->e ;printf("%d",m);
      node = node->next;
    } else break;
  } while(1);
  printf("\n");
}
