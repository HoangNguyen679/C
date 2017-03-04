typedef struct stackType_t{
	elementType element[MAX];
	int top;
} stackType;

void Initialize(stackType *stack){
	stack->top = 0;
}

int IsFull(stackType *stack){
	return (stack->top == MAX);
}


int IsEmpty(stackType *stack){
	return (stack->top == 0);
}


void Push(elementType element, stackType *stack){
	if(IsFull(stack)) printf("Stack Overflow!\n");
	else stack->element[stack->top++] = element;
}

elementType Pop(stackType *stack){
	if(IsEmpty(stack)) printf("Stack Underflow!\n");
	else return (stack->element[--stack->top]);
}