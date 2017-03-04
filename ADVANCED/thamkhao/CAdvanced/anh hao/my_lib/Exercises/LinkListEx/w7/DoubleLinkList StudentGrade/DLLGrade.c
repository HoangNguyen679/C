#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 20 				//student's name length

#define FILENAME "grade.dat" 		//default file to open
#define FILESAVE "GradeSave.dat" 	//default file name to save

typedef struct Element_Type{
  int id;
  char name[MAX];
  int grade;
} elementType;



#include "DLListLib.h"		//include library of link list

DLList Class1;
DLList Class2;

int GetMenu(void);			//show menu to user
//elementType ReadFile(FILE *fileIn);	//read data to import from file
void SearchAndUpdate(int search);	//search and update student's data f
void PrintData(elementType);		//print out individual student's information
elementType AddNewStudent(void);	//add specific student with full of information
void SaveClassToFile(DLList *List){
  clrBuff();
  FILE *fileSave;
  char saveName[MAX];
  printf("Name of save file: "); scanf("%[A-Za-z0-9. -]s", saveName);
  fileSave = fopen(saveName, "wb");     //Create file to save
  node *p = List->head;
  //Do a loop to write to file node by node
  for(p = List->head; p != NULL; p = p->next)
    fwrite(&p->element, sizeof(elementType), 1, fileSave);
  fclose(fileSave); //Done save
  printf("WROTE %s SUCCESSFULLY\n", saveName);
}

int main(int argc, char argv[]){

  int menu,		// option of menu, which is user's choice
    optionAdd, 		// option to add student (current, at position)
    optionDelete, 	// delete student (cur, at position, head,...)
    saveOption,		// save file or not, option from user
    position, 		// a position add or delete a student
    traverseOrder, 	// option to traverse (forwart or reverse)
    search,		// student's ID, to search a student
    n2; 		// length of list 2 in split function
  char saveName[MAX];	// savefile's name, input by user

  FILE *fileSave, *fileIn;

  // do a loop for main menu until user choice '0', exit program
  do{
    switch(menu = GetMenu()){
      ////////////////1. Import Data////////////////////////////////////////
    case 1:
      fileIn = fopen(FILENAME, "rb");
      if(fileIn == NULL){    // if file doesn't exist, exit program
        perror("ERROR");
        return;
      }
      ImportFile(&Class1, fileIn);
      printf("IMPORT SUCCESSFULLY\n");
      break;

      ////////////////2. Traverse List//////////////////////////////////////
    case 2:
      do{
        printf("   Traverse Order (1. Forward | 2. Reverse): ");
        clrBuff(); scanf("%d", &traverseOrder);
      } while (traverseOrder < 1 || traverseOrder >2);
      if (traverseOrder == 1)
        TraverseList(&Class1);
      else TraverseRevertList(&Class1);
      break;

      ////////////////3. Add New Data////////////////////////////////////////
    case 3:
      do{
        printf("   1. Insert After Current\n");
        printf("   2. Insert Before Current\n");
        printf("   3. Insert At Position\n");
        printf("   0. Cancel\n");
        printf("   Your Option: ");
        clrBuff(); scanf("%d", &optionAdd);
      } while (optionAdd < 0 || optionAdd > 3);
      if(optionAdd == 0) break;
      else if(optionAdd == 1) InsertAfterCurrent(&Class1, AddNewStudent());
      else if(optionAdd ==2) InsertBeforeCurrent(&Class1, AddNewStudent());
      else {
        printf("Input Position to Add: ");
        clrBuff(); scanf("%d", &position);
        InsertAtPosition(&Class1, AddNewStudent(), position);
      }
      printf("Add Phone Complete!\n");
      break;

      ////////////////4. Delete Data///////////////////////////////////////
    case 4:
      do{
        printf("   1. Delete First\n");
        printf("   2. Delete End\n");
        printf("   3. Delete Current\n");
        printf("   4. Delete At Position\n");
        printf("   0. Cancel\n");
        printf("   Your Option: ");
        clrBuff(); scanf("%d", &optionDelete);
      } while (optionDelete < 0 || optionDelete > 4);
      if (optionDelete == 0) break;
      else if (optionDelete == 1)	DeleteAtPosition(&Class1, 0);
      else if (optionDelete == 2)	{
        Class1.cur = Class1.tail;
        DeleteCurrent(&Class1);
      }
      else if (optionDelete == 3)	DeleteCurrent(&Class1);
      else{
        do{
          printf("Input Position to Delete: ");
          clrBuff(); scanf("%d", &position);
          DeleteAtPosition(&Class1, position);
        } while (position < 0);
      }
      printf("Delete Complete!\n");
      break;

      ////////////////5. Search And Update/////////////////////////////////
    case 5:
      printf("Enter ID to search: "); clrBuff(); scanf("%d", &search);
      SearchAndUpdate(search);
      break;

      ////////////////6. Devide List//////////////////////////////////////
    case 6:
      FreeList(&Class2);
      printf("Position to Devide: ");
      clrBuff(); scanf("%d", &position);
      DevideList(&Class1, &Class2, position);
      TraverseList(&Class2);

      do{
        printf("Do you want to save this Split (1.Yes/0.No): ");
        clrBuff(); scanf("%d", &saveOption);
      } while (saveOption < 0 || saveOption > 1);
      if(saveOption == 1) SaveClassToFile(&Class2);

      break;

      ////////////////7. Split List////////////////////////////////////////
    case 7:
      FreeList(&Class2);
      printf("Position to Split: ");
      clrBuff(); scanf("%d", &position);
      printf("Length of List 2: ");
      clrBuff(); scanf("%d", &n2);
      SplitList(&Class1, &Class2, position, n2);
      TraverseList(&Class2);

      do{
        printf("Do you want to save this Split (1.Yes/0.No): ");
        clrBuff(); scanf("%d", &saveOption);
      } while (saveOption < 0 || saveOption > 1);
      if(saveOption == 1) SaveClassToFile(&Class2);
      break;


      ////////////////8. Free List/////////////////////////////////////////
    case 8:
      FreeList(&Class1);
      break;
      ////////////////9. Save to File//////////////////////////////////////
    case 9:
      SaveClassToFile(&Class1);
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
    printf("6. Devide List\n");
    printf("7. Split List\n");
    printf("8. Free List\n");
    printf("9. Save to File\n");
    printf("0. Exit\n");
    printf("Your choice: ");
    scanf("%d", &menu);
  }while(menu<0 || menu>9);
  return menu;
}



void PrintData(elementType e){
  printf(" %-20s %-10d %-2d\n", e.name,  e.id, e.grade);
}

void SearchAndUpdate(int search){
  node *p = Class1.head;
  int changeOption=-1;

  //Do a loop to compare key to model
  for(p = Class1.head; p != NULL; p = p->next){

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

elementType AddNewStudent(void){
  elementType e;
  clrBuff();
  printf("ID: "); scanf("%d", &e.id); clrBuff();
  printf("Name: "); scanf("%[A-Za-z0-9 ]s", e.name);
  do{
    printf("Grade (0-10): "); scanf("%d", &e.grade);
  } while(e.grade < 0 || e.grade > 10);
  return e;
}
