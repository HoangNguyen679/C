#include<stdio.h>
#define MAX 50

typedef int elementtype;
typedef struct StackRec{
  elementtype storage[MAX];
  int top;
}stacktype;

Initialize(stacktype *stack)
{
	(*stack).top = 0;
}

isEmpty(stacktype stack)
{
	return stack.top == 0;
}

isFull(stacktype stack)
{
	return stack.top == MAX;
}

push(elementtype e, stacktype *stack)
{
	if (isFull(*stack))
		printf("Stack overflow\n");
	else (*stack).storage[(*stack).top++] = e;
}

elementtype pop(stacktype *stack)
{
	if (isEmpty(*stack))
		printf("Stack underflow\n");
	else return (*stack).storage[--(*stack).top];
}
