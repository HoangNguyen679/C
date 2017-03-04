#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef float elementtype;
typedef struct stack{
  elementtype storage[MAX];
  int top;
}stack;

stack stackConstruct(stack *s);

int isEmpty_stack(stack s);

int isFull_stack(stack s);

void push(stack *s, elementtype e);

elementtype pop(stack *s);

void printStack(stack s);

stack stackConstruct(stack *s){
  (*s).top = 0;
  return *s;
}

int isEmpty_stack(stack s){
  return s.top == 0;
}

int isFull_stack(stack s){
  return s.top == MAX;
}

void push(stack *s, elementtype e){
  if (isFull_stack(*s)) { printf("\nFULL STACK\n"); return; }
  (*s).storage[(*s).top++] = e;
}

elementtype pop(stack *s){
  if(isEmpty_stack(*s)) printf("\nEMPTY STACK\n");
  else  return (*s).storage[--(*s).top];
}

void printStack(stack s){
  if(isEmpty_stack(s)) { printf("\n>>>EMPTY STACK<<<\n"); return; }
  int i =0; printf("\n\n>>>STACK INFO<<<\n\n");
  while(i < s.top){
    printf("%f\n",s.storage[i]);
    i++;
  }
}
