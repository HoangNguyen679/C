#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 20
#define FILENAME "nokia.dat"
#define FILESAVE "NokiaDB.dat"

typedef struct Element_Type{
	char model[MAX];
	float storage;
	float scrSize;
	int price;
} elementType;

#include "DLListLib.h"

int GetMenu(void);
elementType AddNewPhone(void);
elementType ReadFile(FILE *fileIn);
void SearchAndUpdate(char* search);

int main(int argc, char argv[]){
	int menu, optionAdd, optionDelete, position, traverseOrder;
	char search[MAX], saveName[MAX];
	FILE *fileSave;
	FILE *fileIn = NULL;
	do{
		switch(menu = GetMenu()){
			////////////////1. Import Data/////////////////////////////////////////
			case 1:
			fileIn = fopen(FILENAME, "rb");
			if(fileIn == NULL){
				perror("ERROR");
				return;	
			}
			ImportFile(fileIn);
			printf("IMPORT SUCCESSFULLY\n");
			break;

			////////////////2. Traverse List/////////////////////////////////////////
			case 2:
			do{
				printf("   Traverse Order (1. Forward | 2. Reverse): ");
				clrBuff(); scanf("%d", &traverseOrder);
			} while (traverseOrder < 1 || traverseOrder >2);
			if (traverseOrder == 1)
				TraverseList();	
			else TraverseRevertList();
			break;

			////////////////3. Add New Data/////////////////////////////////////////
			case 3:
			do{
				printf("   1. Insert After Current\n");
				printf("   2. Insert Before Current\n");
				printf("   3. Insert At Position\n");
				printf("   Your option: ");
				clrBuff(); scanf("%d", &optionAdd);
			} while (optionAdd < 1 || optionAdd > 3);
			if(optionAdd == 1) InsertAfterCurrent(AddNewPhone());
			else if(optionAdd ==2) InsertBeforeCurrent(AddNewPhone());
			else {
				printf("Input Position to Add: ");
				clrBuff(); scanf("%d", &position);
				InsertAtPosition(AddNewPhone(), position);
			}
			printf("Add Phone Complete!\n");
			break;

			////////////////4. Delete Data/////////////////////////////////////////
			case 4:
			do{
				printf("   1. Delete First\n");
				printf("   2. Delete End\n");
				printf("   3. Delete Current");
				printf("   4. Delete At Position\n");
				clrBuff(); scanf("%d", &optionDelete);
			} while (optionDelete < 1 || optionDelete > 4);
			switch(optionDelete){
				case 1: 
				DeleteAtPosition(0);
				break;

				case 2: 
				cur = tail;
				DeleteCurrent();
				break;

				case 3:
				DeleteCurrent();
				break;

				case 4: 
				do{
					printf("Input Position to Delete: ");
					clrBuff(); scanf("%d", &position);
					DeleteAtPosition(position);
				} while (position < 0);
				break;
			}
			break;

			////////////////5. Search And Update////////////////////////////////////
			case 5: 
			printf("Enter Phone Model: "); clrBuff(); scanf("%s", search);
			SearchAndUpdate(search);
			break;

			case 6: 
			clrBuff();
			printf("Name of save file: "); scanf("%[A-Za-z0-9. -]s", saveName);
			fileSave = fopen(saveName, "wb"); //Create file to save
			node *p=head;
			//Do a loop to write to file node by node
			for(p = head; p != NULL; p = p->next)
				fwrite(&p->element, sizeof(elementType), 1, fileSave);
			fclose(fileSave); //Done save
			printf("WROTE %s SUCCESSFULLY\n", saveName);
			break;
		}
	}while(menu != 0); //0 to exit do...while
	return 0;
}



///////////////////////////////
int GetMenu(void){
	int menu;
	do{
		printf("\n----MENU----\n");
		printf("1. Import from nokia.dat\n");
		printf("2. Display (Tranverse)\n");
		printf("3. Add Data\n");
		printf("4. Delete Data\n");
		printf("5. Search and Update\n");
		printf("6. Save to File\n");
		printf("0. Exit\n");
		printf("Your choice: ");
		scanf("%d", &menu);
	}while(menu<0 || menu>6);
	return menu;
} 


elementType AddNewPhone(){
	elementType e;
	clrBuff();
	printf("Phone Model: "); scanf("%[A-Za-z0-9 ]s", &e.model); clrBuff();
	printf("Phone Storage: "); scanf("%f", &e.storage);
	printf("Phone Screen Size: "); scanf("%f", &e.scrSize);
	printf("Phone Price: "); scanf("%d", &e.price);  
	return e;
}

void PrintData(elementType e){
	printf("%-8s  %-12g  %-12.1f  %-10d\n",
		e.model,
		e.storage,
		e.scrSize,
		e.price);
}

void SearchAndUpdate(char* search){
	node *p = head;
	int changeOption=-1;

		//Do a loop to compare key to model
	for(p = head; p != NULL; p = p->next){ 

			//Compare key to model
		if (strcmp(search,p->element.model) == 0) { 
			PrintData(p->element); //Print out model if match

			//Update phone
			printf("Do you want to change this phone (1-Yes/0-No)? ");
			scanf("%d", &changeOption);

			if (changeOption == 1) p->element = AddNewPhone(); 
			//Use AddNewPhone function to change data of phone
		}
	}
}
