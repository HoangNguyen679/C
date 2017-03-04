#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX 20
#define FILENAME "nokia.dat"

typedef struct Element_Type{
  char model[MAX];
  float storage;
  float scrSize;
  int price;
} elementType;

////PROGRAM's PROTOTYPE DECLATION
void PrintData(elementType e);
elementType AddNewPhone(void);
void InsertSorted(elementType e);
int GetMenu(void);
void InsertPhone(void);
void DeletePhone(void);
void SearchPhone(void);
void SaveToFile(void);
////////////////////////////////////

#include "SLLLib.h"

elementType SearchResult[100];

node *SearchAndUpdate(char []);
int SearchByKey(char *key);
void AdvanceSearch();
void DeletePhoneByKey();


int main(int argc, char const *argv[]){
  int menu;

  do{ 
    switch(menu = GetMenu()){
      case 1: ImportFile(FILENAME); printf("Import Complete!\n"); break; 
      //ImportFileSorted(FILENAME); break; //Uncomment to change into Sorted List
      case 2: TraverseList(); break;
      case 3: InsertPhone(); break;
      //InsertSorted(AddNewPhone()); break; //Uncomment to change into Sorted List
      case 4: DeletePhone(); break;
      case 5: SearchPhone(); break;
      case 6: ListReverse(); break;
      case 7: SaveToFile(); break;
      case 8: AdvanceSearch("1"); break;
    }
  }while(menu != 0);

  FreeAllList();
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
  node *p = root;
  node *re = NULL;
  int changeOption=-1;

  for(p = root; p != NULL; p = p->next){
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
  if(optionAdd == 1) InsertAfterCurrent(AddNewPhone());
  else if(optionAdd == 2) InsertBeforeCurrent(AddNewPhone());
  else if(optionAdd == 3) {
    clrBuff();
    do{
      printf("What position do you want to insert?");
      scanf("%d", &position);
    } while(position < 0);
    InsertAtPosition(AddNewPhone(), position);
  }
}

void DeletePhone(void){
  int optionDelete = 0, position;
  do{
    printf("   1. Delete First\n   2. Delete Current\n   3. Delete At Position\n   4. Delete by Search\n   0. Cancel\n   Your option: ");
    clrBuff();
    scanf("%d", &optionDelete);
  }while(optionDelete < 0 || optionDelete > 4);
  if(optionDelete == 1) DeleteFirst();
  else if(optionDelete == 2) DeleteCurrent();
  else if(optionDelete == 3){
    do{
      printf("What position do you want to delete?");
      scanf("%d", &position);
    } while(position < 0);
    DeleteAtPosition(position);
  }
  else if(optionDelete == 4) DeletePhoneByKey();
}

void SearchPhone(void){
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
    cur = temp;
    elementType etemp = temp->element;
    switch (optionSearch){
      case 2: DeleteCurrent(); InsertAtPosition(etemp, 0); break;
      case 3: DeleteCurrent(); InsertBeforeCurrent(etemp); break;
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
  node *p=root;
    //Do a loop to write to file node by node
  for(p = root; p->next != NULL; p = p->next){
    fwrite(&p->element, sizeof(elementType), 1, fileSave);
    fclose(fileSave); //Done save
    printf("WROTE %s SUCCESSFULLY\n", saveName);
  }
}


void ImportFileSorted(char* filename){
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
    InsertSorted(temp);
    //InsertAfterCurrent(temp);
  }
  fclose(fileIn);
}

void InsertSorted(elementType e){
  node *new = MakeNewNode(e);
  if(e.price == 0) return;
  if(root == NULL) {
    root = new;
    root->next = NULL;
    cur =  new;
  }else if(new->element.price > root->element.price) {
    new->next = root;
    root = new;
    cur = new;
  }else {
    node *prev;
    cur = root;
    while(cur != NULL && new->element.price <= cur->element.price){
      prev = cur;
      cur = cur->next;
    }
    prev->next= new;
    new->next = cur;
  }
}

int SearchByKey(char *key){ //return number of results
  int isFound = 0, i = 0;
  node *p = root;
  for(p=root; p!=NULL; p=p->next){
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

void AdvanceSearch(){
  char key[MAX];
  clrBuff(); printf("Input keyword: "); scanf("%s", key);
  int numOfResult = SearchByKey(key);
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
}

void DeletePhoneByKey(){
  char key[MAX];
  clrBuff(); printf("Input keyword: "); scanf("%s", key);
  node *p = root;
  for(p=root; p!=NULL; p=p->next){
    if(strstr(p->element.model, key)) {
      char temp[MAX];
      strcpy(temp,p->element.model);
      temp[strlen(key)] = '\0';
      if(strcmp(temp, key) == 0){
        printf("Deleting: Model "); printf("%s\n", p->element.model);
        cur = p;
        DeleteCurrent();
      }
    }
  }
}



