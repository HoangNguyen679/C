/**************************** Stack Implement ***************************\
* Program: 		Stack Exmple
* Author:		Nguyen Van Hao
* 
* This program is used to test Stack Library with array and struct
\************************************************************************/


#include <stdio.h>

#define MAX 50 //max elements of one stack

typedef int elementType; //example stack with integer

#include "StackArray.h" 	//Using stack library with array
//#include "StackStruct.h"	//Using stack library with struct

int GetMenu(void);	//Print main menu

int main(int argc, char const *argv[]) {
	stackType myStack; 	//define a stack
	elementType temp;	//
	int menuOption;		// option for main menu

	Initialize(&myStack);
	
	do {
		switch(menuOption = GetMenu()){
			case 1:
			printf("Input element to Push: "); scanf("%d", &temp);
			Push(temp, &myStack); //push element temp to top of stack
			break;

			case 2:
			printf("Pop element: %d", Pop(&myStack)); // pop top element of stack
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
		printf("0. Exit\n");
		printf("Your Choice: ");
		scanf("%d", &menuOption);
	} while(menuOption < 0 || menuOption > 2);
	return menuOption;
}