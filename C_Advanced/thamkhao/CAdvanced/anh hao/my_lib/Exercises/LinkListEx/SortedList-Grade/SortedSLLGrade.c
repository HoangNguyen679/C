#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 20
#define FILENAME "grade.dat"
#define FILESAVE "GradeSave.dat"



typedef struct Element_Type{
  int id;
  char name[MAX];
  int grade;
} elementType;

FILE *fileIn;


////PROGRAM's PROTOTYPE DECLATION
void SearchAndUpdate(int search);
void PrintData(elementType e);
elementType AddNewStudent();
int GetMenu();
void InsertSorted(elementType e);
////////////////////////////////////


#include "SLLLib.h"



int main(int argc, char const *argv[]){

  FILE *fileSave; //This file to save in Option 6
  char saveName[MAX];

  //open database file
  fileIn = fopen(FILENAME, "rb");
  if(fileIn == NULL){
    perror("ERROR");
    return 1;
  }


  int menu, optionAdd, position;
  //menu: Option in main menu
  // optionAdd: option to Insert (befor or after cur)
  //position: position to Inset or Dele

  int search; //key to search phone model
  int i = 0;


  do{ //Show menu
    switch(menu = GetMenu()){

    case 1:
      //This will Insert node from dat file (Insert after Current)
      // while(!feof(fileIn))
      //  InsertSorted(ReadFile());
      ImportFile(fileIn);
        //DeleteCurrent(); //Delete a raw last node because of reading file
      break;

    case 2: //Print all node
      TranverseList();
      break;

    case 3:
      InsertSorted(AddNewStudent());
      break;

    case 4:
      clrBuff();
      do{
        printf("What position do you want to delete?");
        scanf("%d", &position);
      } while(position < 0);
      DeleteAtPosition(position);
      printf("Deleted\n");
      break;
    case 5: //Delete Current Node
      DeleteCurrent();
      printf("Deleted\n");
      break;

    case 6: //Delete First (root) node
      DeleteFirst();
      printf("Deleted\n");
      break;

    case 7: //Search Phone Model by enter model. Update is manual.
      printf("Enter ID: "); clrBuff(); scanf("%d", &search);
      SearchAndUpdate(search);
      break;

    case 8:
      ListReverse();
      break;

    case 9: //Export to File
      clrBuff();
      printf("Name of save file: "); scanf("%[A-Za-z0-9. -]s", saveName);
      fileSave = fopen(saveName, "wb"); //Create file to save
      node *p=root;
      //Do a loop to write to file node by node
      for(p = root; p != NULL; p = p->next)
        fwrite(&p->element, sizeof(elementType), 1, fileSave);
      fclose(fileSave); //Done save
      printf("WROTE %s SUCCESSFULLY\n", saveName);
    }
  }while(menu != 0); //0 to exit do..while

  fclose(fileIn); //Close database file
  return 0;
}



/////PROGRAM FUNCTION//////////////////////////////
int GetMenu(void){
  int menu;
  do{
    printf("\n----MENU----\n");
    printf("1. Import from grade.dat\n");
    printf("2. Display (Tranverse)\n");
    printf("3. Insert Student\n");
    printf("4. Delete at Position\n");
    printf("5. Delete Current\n");
    printf("6. Delete First\n");
    printf("7. Search and Update\n");
    printf("8. Reverse List\n");
    printf("9. Save to File\n");
    printf("0. Exit\n");
    printf("Your choice: ");
    scanf("%d", &menu);
  }while(menu<0 || menu>=12);
  return menu;
}


void SearchAndUpdate(int search){
  node *p = root;
  int changeOption=-1;

  //Do a loop to compare key to model
  for(p = root; p != NULL; p = p->next){

    //Compare key to model
    if(search == p->element.id) {
      PrintData(p->element); //Print out model if match

      //Update phone
      printf("Do you want to change this student (1-Yes/0-No)? ");
      scanf("%d", &changeOption);

      if(changeOption == 1){
        cur = p;
        DeleteCurrent();
        InsertSorted(AddNewStudent());
      }
      //Use AddNewPhone function to change data of phone
    }
  }

  if (changeOption == -1) printf("No Phone Found!\n");
  // if there exits a phone which be found,
  // changeOption must be 0 or 1, but default is -1
}



void PrintData(elementType e){
  printf("%-20s  %-10d  %5d\n", e.name, e.id, e.grade);
}

elementType AddNewStudent(){
  elementType e;
  clrBuff();
  printf("ID: "); scanf("%d", &e.id); clrBuff();
  printf("Name: "); scanf("%[A-Za-z0-9 ]s", &e.name); clrBuff();
  printf("Grade: "); scanf("%d", &e.grade);
  return e;
}

void InsertSorted(elementType e){
  node *new = MakeNewNode(e);
  if(e.grade > 10) return;
  if(root == NULL) {
    root = new;
    root->next = NULL;
    cur =  new;
  }else if(new->element.grade >= root->element.grade) {
    new->next = root;
    root = new;
    cur = new;
  }else {
    node *prev;
    cur = root;
    while(cur != NULL && new->element.grade <= cur->element.grade){
      prev = cur;
      cur = cur->next;
    }
    prev->next= new;
    new->next = cur;
  }
}

////////////////////////////////////////////////////





