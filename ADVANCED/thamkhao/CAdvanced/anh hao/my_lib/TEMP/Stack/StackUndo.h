typedef struct UndoElement{
	char* action;
	int num;
} undoElement;

typedef struct UndoStack{
	undoElement element;
	struct UndoStack *next;
} undoStack;

void PushU(undoElement element, undoStack **top){
	undoStack *p;
	p = (undoStack*)malloc(sizeof(undoStack));
	if(p == NULL) printf("MAlloc Error!\n");
	else{
		p->element = element;
		p->next = *top;
		*top = p;
	}
}

undoElement PopU(undoStack **top){
	if(*top == NULL) printf("Stack Underflow!\n");
	else{
		undoElement temp;
		undoStack *p;
		temp = (*top)->element;
		p = *top;
		*top = (*top)->next;
		free(p);
		return temp;
	}
}