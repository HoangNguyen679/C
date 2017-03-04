#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct phone_address{
  char name[25];
  char tel[12];
  char email[25];
}phone_address;
typedef phone_address elementtype;

typedef struct stack{
  elementtype storage[MAX];
  int top;
}stack;

stack stackConstruct(stack *s);

int isEmpty(stack s);

int isFull(stack s);

void push(stack *s, elementtype e);

elementtype pop(stack *s);

void printStack(stack s);

stack stackConstruct(stack *s){
  (*s).top = 0;
  return *s;
}

int isEmpty(stack s){
  return s.top == 0;
}

int isFull(stack s){
  return s.top == MAX;
}

void push(stack *s, elementtype e){
  if (isFull(*s)) { printf("\nFULL STACK\n"); return; }
  (*s).storage[(*s).top++] = e;
}

elementtype pop(stack *s){
  if(isEmpty(*s)) printf("\nEMPTY STACK\n");
  else  return (*s).storage[--(*s).top];
}

void printStack(stack s){
  if(isEmpty(s)) { printf("\n>>>EMPTY STACK<<<\n"); return; }
  int i =0; printf("\n\n>>>STACK INFO<<<\n\n");
  while(i < s.top){
    printf("%-25s%-12s%-25s\n",s.storage[i].name,s.storage[i].tel,s.storage[i].email);

    i++;
  }
}
