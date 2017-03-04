#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "jrb.h"

#define ARRSIZE 	10
#define RANGE 		26
#define EPSILON 	1E-7
#define MAX_BUFF 	512

#define NEWLINE 	printf("%s", "\n");


int GetMenu(void);

int main(int argc, char const *argv[])
{
	JRB integersTree, ptr;
	int menu = 0;
	int tmp;

	integersTree = make_jrb();

	do
	{
		switch(menu = GetMenu())
		{
			case 1: 
			printf("Input an interger: "); 
			scanf("%d", &tmp);
			jrb_insert_int(integersTree, tmp, new_jval_v(NULL));
			break;
			
			case 2: 
			jrb_traverse(ptr, integersTree)
			{
				printf("%d\n", ptr->key);
			}
			break;
			
			case 0: 
			jrb_free_tree(integersTree);
			break;
			
			default: printf("%s", "Invalid input choice!");
		}
	} while (menu != 0);

	return 0;
}

int GetMenu(void)
{
	int menuOption = 0;

	printf("\n\n---SORT MENU---\n");
	printf("1. Insert Node\n");
	printf("2. Display\n");
	printf("0. Destroy Tree & Exit\n");
	printf("Your Choice: ");
	scanf("%d", &menuOption);

	return menuOption;
}