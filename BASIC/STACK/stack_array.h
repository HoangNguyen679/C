#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef float elementtype;
typedef elementtype stack[MAX];
int top;

elementtype stackConstruct();

int isEmpty_stack(stack s);

int isFull_stack(stack s);

void push(stack s, elementtype e);

elementtype pop(stack s);

void printStack(stack s);

elementtype stackConstruct(){
  stack s;
  top = 0;
  return top;
}

int isEmpty_stack(stack s){
  return top == 0;
}

int isFull_stack(stack s){
  return top == MAX;
}

void push(stack s, elementtype e){
  if (isFull_stack(s)) { printf("\nFULL STACK\n"); return; }
  s[top++] = e;
}

elementtype pop(stack s){
  if(isEmpty_stack(s)) printf("\nEMPTY STACK\n");
  else  return s[--top];
}

void printStack(stack s){
  if(isEmpty_stack(s)) { printf("\n>>>EMPTY STACK<<<\n"); return; }
  int i =0; printf("\n\n>>>STACK INFO<<<\n\n");
  while(i < top){
    printf("%f\n",s[i]);
    i++;
  }
}
