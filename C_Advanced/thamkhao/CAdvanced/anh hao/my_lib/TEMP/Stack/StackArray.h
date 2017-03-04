typedef elementType stackType[MAX];

int top;

void Initialize(stackType *stack){
	top = 0;
}

int IsEmpty(stackType *stack){
	return (top == 0);
}

int IsFull(stackType *stack){
	return (top == MAX);
}

void Push(elementType element, stackType *stack){
	if(IsFull(stack)) printf("Stack Overflow!\n");
	else *stack[top++] = element;
}

elementType Pop(stackType *stack){
	if(IsEmpty(stack)) printf("Stack Underflow!\n");
	else return *stack[--top];
}