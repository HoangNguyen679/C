typedef struct StackType_t{
	ElementType element;
	struct StackType_t *next;
} StackType;

int IsEmpty(StackType**top){
	return (*top == NULL);
}

void Push(ElementType element, StackType **top){
	StackType *p;
	p = (StackType*)malloc(sizeof(StackType));
	if(p == NULL) printf("MAlloc Error!\n");
	else{
		p->element = element;
		p->next = *top;
		*top = p;
	}
}

ElementType Pop(StackType **top){
	if(*top == NULL) {}
	else{
		ElementType temp;
		StackType *p;
		temp = (*top)->element;
		p = *top;
		*top = (*top)->next;
		free(p);
		return temp;
	}
}