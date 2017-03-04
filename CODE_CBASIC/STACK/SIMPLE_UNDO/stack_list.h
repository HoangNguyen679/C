#include<stdio.h>
#include<stdlib.h>
#define MAX 81

typedef struct dl
{
  int n;
  char str[MAX];
}dl;
typedef dl  elementtype;
typedef struct stackNode
{
  elementtype data;
  struct stackNode *next;
}stackNode;
struct stack
{
  stackNode *top;
};
typedef struct stack stack;

stack *stackConstruct();

int isEmpty_stack(stack *s);

int isFull_stack();

int push(stack *s, elementtype e);

elementtype pop(stack *s);

void printStack(stack *s);

elementtype top(stack s);

stack *stackConstruct()
{
  stack *s;
  s = (stack *)malloc(sizeof(stack));
  if(s == NULL) return NULL;
  s->top = NULL;
  return s;
}

int isEmpty_stack(stack *s)
{
  return (s->top == NULL);
}

int isFull_stack()
{
  printf("\n NO MEMORY! STACK IS FULL\n");
  return 1;
}

int push(stack *s, elementtype e)
{
  stackNode *node;
  node = (stackNode *)malloc(sizeof(stackNode));
  if (node == NULL) {
    isFull_stack();
    return 1;
  }
  node->data = e;
  node->next = s->top;
  s->top = node;
  return 0;
}
elementtype pop(stack *s)
{
  elementtype e;
  stackNode *node;
  if(isEmpty_stack(s)){ printf("\nEMPTY STACK\n"); return ; }
  node = s->top;
  e = node->data;
  s->top = node->next;
  free(node);
  return e;
}

void printStack(stack *s)
{
  stackNode *node;
  int ct = 0; dl m;
  printf("\n\n>>>>>STACK INFO<<<<<\n\n");
  if(isEmpty_stack(s))
    {printf("\n\n >>>>> EMPTY STACK <<<<<\n\n"); return;}
  node = s->top;
  do{
    m = node->data ;printf("%d\t%-5s\n",m.n,m.str); ct++;
    if(ct % 9 == 0) printf("\n");
    node = node->next;
  } while( !(node == NULL));
  printf("\n");
}

elementtype top(stack s){
  if(isEmpty_stack(&s))
    {printf("\nEMPTY STACK\n"); return;}
  return s.top->data;
}
