#include <stdio.h>
#define MAX 100
typedef int elementType;
typedef struct stack{
  elementType elements[MAX];
  int top;
} stack;

///////////////////////////////////////////////// KHOI TAO

stack *stackConstruct(stack *s){
	s->top = 0;
	return s;
}

///////////////////////////////////////////////// KT RONG

int isEmpty(stack s){
	return s.top == 0;
}

//////////////////////////////////////////////// KT DAY

int isFull(stack s){
	return s.top == MAX;
}

///////////////////////////////////////////////// PUSH

void push(stack *s, elementType e){
	if (isFull(*s)) { 
		printf("\nFULL STACK\n"); 
		return; 
	}
  	s->elements[(s->top)++] = e;
}

///////////////////////////////////////////////// POP

elementType pop(stack *s){
  if(isEmpty(*s)) 
  	printf("\nEMPTY STACK\n");
  else {  	
  	return s->elements[--(s->top)];
  }  
}

///////////////////////////////////////////////// TOP

elementType top(stack *s){
  if(isEmpty(*s)) 
  	printf("\nEMPTY STACK\n");
  else  return s->elements[s->top];
}
///////////////////////////////////////////////// PRINT

void printStack(stack s){
  if(isEmpty(s)) { 
  	printf("\n>>>EMPTY STACK<<<\n"); 
  	return; 
  }
  int i =0; 
  printf("\n\n>>>STACK INFO<<<\n\n");
  while(i < s.top){
    printf("%d\n",s.elements[i++]);
  }
}

