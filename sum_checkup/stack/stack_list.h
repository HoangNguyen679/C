#include <stdio.h>
#include <stdlib.h>

typedef int elementType;
typedef struct stackNode{
  elementType elements;
  struct stackNode *next;
}stackNode;

typedef struct stack{
  stackNode *top;
} stack;

///////////////////////////////////////////////// KHOI TAO

stack *stackConstruct(){
  stack *s;
  s = (stack *)malloc(sizeof(stack));
  if(s == NULL) return NULL;
  s->top = NULL;
  return s;
}

///////////////////////////////////////////////// KT RONG

int isEmpty(stack *s){
  return (s->top == NULL);
}

//////////////////////////////////////////////// KT DAY

int isFull(){
  printf("\n NO MEMORY! STACK IS FULL\n");
  return 1;
}

///////////////////////////////////////////////// PUSH

int push(stack *s, elementType e){
  stackNode *node;
  node = (stackNode *)malloc(sizeof(stackNode));
  if (node == NULL) {
    isFull();
    return 1;
  }
  node->elements = e;
  node->next = s->top;
  s->top = node;
  return 0;
}

///////////////////////////////////////////////// POP

elementType pop(stack *s){
  elementType e;
  stackNode *node;
  if(isEmpty(s)){ 
    printf("\nEMPTY STACK\n"); 
    return 0; 
  }
  node = s->top;
  e = node->elements;
  s->top = node->next;
  free(node);
  return e;
}

void printStack(stack *s){
  if(isEmpty(s)){
    printf("\n\n >>>>> EMPTY STACK <<<<<\n\n");
    return;
  }
  printf("\n\n>>>>>STACK INFO<<<<<\n\n");
  stackNode *node = s->top;
  do{
    printf("%d\n",node->elements); 
    node = node->next;
  } while( node != NULL);
  printf("\n");
}
