typedef struct stackType_t{
	elementType element;
	struct stackType_t *next;
} stackType;

void Push(elementType element, stackType **top){
	stackType *p;
	p = (stackType*)malloc(sizeof(stackType));
	if(p == NULL) printf("MAlloc Error!\n");
	else{
		p->element = element;
		p->next = *top;
		*top = p;
	}
}

elementType Pop(stackType **top){
	if(*top == NULL) printf("Stack Underflow!\n");
	else{
		elementType temp;
		stackType *p;
		temp = (*top)->element;
		p = *top;
		*top = (*top)->next;
		free(p);
		return temp;
	}
}

