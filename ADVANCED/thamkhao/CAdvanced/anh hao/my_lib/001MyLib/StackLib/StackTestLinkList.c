/**************************** Stack Implement ***************************\
* Program: 		Stack Exmple
* Author:		Nguyen Van Hao
* 
* This program is used to test Stack Library with Single Link List
\************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType; //example stack with integer

#include "StackLinkList.h"

StackType *top = NULL; //define a link list stack with root is top

int GetMenu(void); //Print main menu

int main(int argc, char const *argv[]) {
	
	ElementType temp;
	int menuOption;		// option for main menu
	do {
		switch(menuOption = GetMenu()){
			case 1:
			printf("Input element to Push: "); scanf("%d", &temp);
			Push(temp, &top); //push element temp to top of stack
			break;

			case 2:
			printf("Pop element: %d", Pop(&top)); // pop top element of stack
			break;
		}
	} while (menuOption != 0);

	FreeStack(&top);
	return 0;
}

int GetMenu(void){
	int menuOption = 0;
	do {
		printf("\n\n---STACK MENU---\n");
		printf("1. Push\n");
		printf("2. Pop\n");
		printf("0. Exit\n");
		printf("Your Choice: ");
		scanf("%d", &menuOption);
	} while(menuOption < 0 || menuOption > 2);
	return menuOption;
}