/**************************** Stack Implement ***************************\
* Program: 		Stack Exmple
* Author:		Nguyen Van Hao
* 
* This program is used to test Stack Library with Single Link List
\************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int elementType; //example stack with integer

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


int GetMenu(void); //Print main menu

int main(int argc, char *argv[]) {
	stackType *top = NULL; //define a link list stack with root is top
	undoStack *undoTop = NULL;

	elementType temp;
	undoElement tempUndo;
	int poped;
	int menuOption;		// option for main menu
	
	do {
		switch(menuOption = GetMenu()){
			case 1:
			printf("Input element to Push: "); scanf("%d", &temp);
			Push(temp, &top); //push element temp to top of stack
			tempUndo.action = "POP";
			tempUndo.num = temp;
			PushU(tempUndo, &undoTop);
			break;

			case 2:
			
			poped = Pop(&top);
			printf("Pop element: %d", poped); // pop top element of stack
			tempUndo.action = "PUSH";
			tempUndo.num = poped;
			PushU(tempUndo, &undoTop);
			break;

			case 3: 
			if(top == NULL) printf("Stack Empty\n");
			else printf("Top: %d\n", top->element);
			break;

			case 4:
			if(undoTop == NULL) printf("Nothing to Undo!\n");
			else{
				printf("Undo Done: %s %d in stack\n", undoTop->element.action, undoTop->element.num);
				if(undoTop->element.action == "POP") Pop(&top);
				else if(undoTop->element.action == "PUSH") Push(undoTop->element.num, &top);
				PopU(&undoTop);
			}
			break;
		}
	} while (menuOption != 0);

	return 0;
}

int GetMenu(void){
	int menuOption = 0;
	do {
		printf("\n\n---STACK MENU---\n");
		printf("1. Push\n");
		printf("2. Pop\n");
		printf("3. View Top\n");
		printf("4. Undo\n");
		printf("0. Exit\n");
		printf("Your Choice: ");
		scanf("%d", &menuOption);
	} while(menuOption < 0 || menuOption > 4);
	return menuOption;
}