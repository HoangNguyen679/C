#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 20
#define FILENAME "gradedb.dat"
#define FILESAVE "GradeDB.dat"

typedef struct Element_Type{
	int id;
	char name[MAX];
	int grade;
} elementType;

#include "DLListLib.h"

int GetMenu(void);
//elementType AddNewPhone(void);
elementType ReadFile(FILE *fileIn);
void SearchAndUpdate(int search);

elementType AddNewStudent(void){
	elementType e;
	clrBuff();
	printf("ID: "); scanf("%d", &e.id); clrBuff();
	printf("Name: "); scanf("%[A-Za-z0-9 ]s", e.name);
	printf("Grade: "); scanf("%d", &e.grade);
	return e;
}

int main(int argc, char argv[]){
	int menu, optionAdd, optionDelete, position, traverseOrder, search;
	char saveName[MAX];
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
			if(optionAdd == 1) InsertAfterCurrent(AddNewStudent());
			else if(optionAdd ==2) InsertBeforeCurrent(AddNewStudent());
			else {
				printf("Input Position to Add: ");
				clrBuff(); scanf("%d", &position);
				InsertAtPosition(AddNewStudent(), position);
			}
			printf("Add Phone Complete!\n");
			break;

			////////////////4. Delete Data/////////////////////////////////////////
			case 4:
			do{
				printf("   1. Delete First\n");
				printf("   2. Delete End\n");
				printf("   3. Delete Current\n");
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
			printf("Enter ID to search: "); clrBuff(); scanf("%d", &search);
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
		printf("1. Import from grade.dat\n");
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



void PrintData(elementType e){
	printf("%-2d %-20s %-2d\n", e.id, e.name, e.grade);
}

void SearchAndUpdate(int search){
	node *p = head;
	int changeOption=-1;

		//Do a loop to compare key to model
	for(p = head; p != NULL; p = p->next){ 

			//Compare key to model
		if (search == (int)p->element.id) { 
			PrintData(p->element); //Print out model if match

			//Update phone
			printf("Do you want to change this student (1-Yes/0-No)? ");
			scanf("%d", &changeOption);

			if (changeOption == 1) p->element = AddNewStudent(); 
			//Use AddNewPhone function to change data of phone
		}
	}
}
