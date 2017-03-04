#include<stdio.h>
#define MAX 50

typedef int elementtype;
typedef elementtype stacktype[Max];
int top;

void Initialize(stacktype stack) {
  top = 0;
}

int isEmpty(stacktype stack) {
  return top == 0;
}

int isFull(stacktype stack) {
  return top == MAX;
}

void push(elementtype e, stacktype stack) {
  if(isFull(stack))
    printf("Stack overflow\n");
  else stack[top++] = e;
}

elementtype pop(stacktype stack) {
  if(isEmpty(stack))
    printf("Stack underflow\n");
  else return stack[--top];
}
