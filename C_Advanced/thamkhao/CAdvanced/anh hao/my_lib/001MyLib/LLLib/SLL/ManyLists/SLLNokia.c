#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 20
#define FILENAME "C:\\Users\\Hao\\Desktop\\C Basic\\Source\\001MyLib\\LLLib\\SLL\\ManyLists\\nokia.dat"

typedef struct Element_Type{
  char model[MAX];
  float storage;
  float scrSize;
  int price;
} elementType;

void PrintData(elementType e);

#include "C:\\Users\\Hao\\Desktop\\C Basic\\Source\\001MyLib\\LLLib\\SLL\\ManyLists\\SLLLibWithManyLists.h"

////PROGRAM's PROTOTYPE DECLATION
elementType AddNewPhone(void);
void InsertSorted(SLList *List, elementType e);
int GetMenu(void);
void InsertPhone(void);
void DeletePhone(void);
void SearchPhone(SLList *List);
void SaveToFile(void);
////////////////////////////////////

SLList *myphone;

elementType SearchResult[100];

node *SearchAndUpdate(char []);
int SearchByKey(SLList *List, char *key);
void AdvanceSearch(SLList *List);
void DeletePhoneByKey(SLList *List);


int main(int argc, char const *argv[]){
  int menu;
  myphone = (SLList *)malloc(sizeof(SLList));
  myphone->root = NULL;
  do{ 
    switch(menu = GetMenu()){
      case 1: ImportFile(myphone, FILENAME); printf("Import Complete!\n"); break; 
      //ImportFileSorted(FILENAME); break; //Uncomment to change into Sorted List
      case 2: TraverseList(myphone); break;
      case 3: InsertPhone(); break;
      //InsertSorted(AddNewPhone()); break; //Uncomment to change into Sorted List
      case 4: DeletePhone(); break;
      case 5: SearchPhone(myphone); break;
      case 6: ListReverse(myphone); break;
      case 7: SaveToFile(); break;
      //case 8: AdvanceSearch(myphone); break;
    }
  }while(menu != 0);

  FreeAllList(myphone);
  printf("Goodbye");
  return 0;
}



/////PROGRAM FUNCTION//////////////////////////////
int GetMenu(void){
  int menu;
  do{
    printf("\n----MENU----\n");
    printf("1. Import from nokia.dat\n");
    printf("2. Display (Tranverse)\n");
    printf("3. Add New Phone\n");
    printf("4. Delete Phone\n");
    printf("5. Search and Update\n");
    printf("6. Reverse List\n");
    printf("7. Save to File\n");
    printf("8. Advance Search\n");
    printf("0. Exit\n");
    printf("Your choice: ");
    scanf("%d", &menu);
  }while(menu<0 || menu>8);
  return menu;
}

node *SearchAndUpdate(char search[]){
  node *p = myphone->root;
  node *re = NULL;
  int changeOption=-1;

  for(p = myphone->root; p != NULL; p = p->next){
    if(strcmp(search,p->element.model) == 0) {
      PrintData(p->element); 
      //Update phone
      printf("Do you want to change this phone (1-Yes/0-No)? ");
      scanf("%d", &changeOption);

      if(changeOption == 1) p->element = AddNewPhone();
      //Use AddNewPhone function to change data of phone
      return p;
    }
  }
  printf("No Phone Found!\n");
}


void PrintData(elementType e){
  printf("%-8s  %-12g  %-12.1f  %-10d\n", e.model, e.storage, e.scrSize, e.price);
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

void InsertPhone(void){
  int optionAdd = 0, position;
  do{
    printf("   1. Insert After Current\n   2. Insert Before Current\n   3. Insert At Position\n   0. Cancel\n   Your option: ");
    clrBuff();
    scanf("%d", &optionAdd);
  }while(optionAdd < 0 || optionAdd > 3);
  if(optionAdd == 1) InsertAfterCurrent(myphone, AddNewPhone());
  else if(optionAdd == 2) InsertBeforeCurrent(myphone, AddNewPhone());
  else if(optionAdd == 3) {
    clrBuff();
    do{
      printf("What position do you want to insert?");
      scanf("%d", &position);
    } while(position < 0);
    InsertAtPosition(myphone, AddNewPhone(), position);
  }
}

void DeletePhone(void){
  int optionDelete = 0, position;
  do{
    printf("   1. Delete First\n   2. Delete Current\n   3. Delete At Position\n   4. Delete by Search\n   0. Cancel\n   Your option: ");
    clrBuff();
    scanf("%d", &optionDelete);
  }while(optionDelete < 0 || optionDelete > 4);
  if(optionDelete == 1) DeleteFirst(myphone);
  else if(optionDelete == 2) DeleteCurrent(myphone);
  else if(optionDelete == 3){
    do{
      printf("What position do you want to delete?");
      scanf("%d", &position);
    } while(position < 0);
    DeleteAtPosition(myphone, position);
  }
  else if(optionDelete == 4) DeletePhoneByKey(myphone);
}

void SearchPhone(SLList *List){
  int optionSearch = 0;
  do{
    printf("   1. Normal Search\n   2. Search and move to front\n   3. Search Tranpose\n   0. Cancel\n   Your choice: ");
    clrBuff(); scanf("%d", &optionSearch);
  } while (optionSearch < 0 || optionSearch > 3);
  char search[MAX];
  printf("Enter Phone Model: "); clrBuff(); scanf("%s", search);

  node* temp = SearchAndUpdate(search);
  if (temp == NULL) return;
  else {
    List->cur = temp;
    elementType etemp = temp->element;
    switch (optionSearch){
      case 2: DeleteCurrent(List); InsertAtPosition(List, etemp, 0); break;
      case 3: DeleteCurrent(List); InsertBeforeCurrent(List, etemp); break;
    } 
  }
}

void SaveToFile(void){
  //Export to File
  FILE *fileSave; //This file to save in Option 6
  char saveName[MAX];
  clrBuff();
  printf("Name of save file: "); scanf("%[A-Za-z0-9. -]s", saveName);
  fileSave = fopen(saveName, "wb"); //Create file to save
  node *p=myphone->root;
    //Do a loop to write to file node by node
  for(p = myphone->root; p->next != NULL; p = p->next){
    fwrite(&p->element, sizeof(elementType), 1, fileSave);
    fclose(fileSave); //Done save
    printf("WROTE %s SUCCESSFULLY\n", saveName);
  }
}


/*
void ImportFileSorted(SLList *List, char* filename){
  //open database file
  FILE* fileIn = fopen(filename, "rb");
  if(fileIn == NULL){
    perror("ERROR");
    return;
  }
  //This will Insert node from dat file (Insert after Current)
  elementType temp;
  int irc;
  while(1){
    irc = fread(&temp, sizeof(elementType), 1, fileIn);
    if (irc == 0) break;
    InsertSorted(List, temp);
    //InsertAfterCurrent(temp);
  }
  fclose(fileIn);
}

void InsertSorted(SLList *List, elementType e){
  node *new = MakeNewNode(e);
  if(e.price == 0) return;
  if(myphone->root == NULL) {
    List->root = new;
    List->root->next = NULL;
    List->cur =  new;
  }else if(new->element.price > root->element.price) {
    new->next = List->root;
    List->root = new;
    List->cur = new;
  }else {
    node *prev;
    List->cur = List->root;
    while(List->cur != NULL && new->element.price <= List->cur->element.price){
      prev = List->cur;
      List->cur = List->cur->next;
    }
    prev->next= new;
    new->next = List->cur;
  }
}
*/
int SearchByKey(SLList *List, char *key){ //return number of results
  int isFound = 0, i = 0;
  node *p = List->root;
  for(p=List->root; p!=NULL; p=p->next){
    if(strstr(p->element.model, key)) {
      char temp[MAX];
      strcpy(temp,p->element.model);
      temp[strlen(key)] = '\0';
      if(strcmp(temp, key) == 0){
        //PrintData(p->element);
        SearchResult[i] = p->element;
        isFound = 1;
        i++;
      }
    }
  }
  if(isFound == 0) printf("Could not found!");
  return i;
}

/*void AdvanceSearch(SLList *List){
  char key[MAX];
  clrBuff(); printf("Input keyword: "); scanf("%s", key);
  int numOfResult = SearchByKey(List, key);
  if(numOfResult) {
    int optionSort = 0, i, j, k;
    do{
      printf("Sort by Price? (1.Yes/0.No): ");
      clrBuff(); scanf("%d", &optionSort);
    }while(optionSort != 0 && optionSort != 1);

    switch(optionSort){
      case 0:
      for(i=0; i<numOfResult; i++){
        PrintData(SearchResult[i]);
      }
      break;

      case 1:
      for(i=0; i<numOfResult; i++){
        for(j=0; j<i; j++){
          if(SearchResult[i].price > SearchResult[j].price){
            elementType temp = SearchResult[i];
            SearchResult[i] = SearchResult[j];
            SearchResult[j] = temp;
          }
        }
      }
      for(i=0; i<numOfResult; i++) PrintData(SearchResult[i]);
    }
  }
}*/

void DeletePhoneByKey(SLList *List){
  char key[MAX];
  clrBuff(); printf("Input keyword: "); scanf("%s", key);
  node *p = List->root;
  for(p=List->root; p!=NULL; p=p->next){
    if(strstr(p->element.model, key)) {
      char temp[MAX];
      strcpy(temp,p->element.model);
      temp[strlen(key)] = '\0';
      if(strcmp(temp, key) == 0){
        printf("Deleting: Model "); printf("%s\n", p->element.model);
        List->cur = p;
        DeleteCurrent(List);
      }
    }
  }
}



