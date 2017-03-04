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

typedef struct My_Node{
  elementType element;
  struct My_Node *next;
} node;

node *root;
node *cur;
FILE *fileIn;

////PROGRAM's PROTOTYPE DECLATION
void clrBuff();
void SearchAndUpdate(char []);
elementType AddNewPhone();
int GetMenu();
////////////////////////////////////
////LINK LIST's PROTOTYPE DECLATION
node *MakeNewNode(elementType);
void InsertAfterCurrent(elementType);
void TranverseList();
elementType ReadFile();
void InsertBeforeCurrent(elementType);
void DeleteCurrent();
void DeleteFirst();
node *FindPre();
void FreeAllList();
////////////////////////////////////




int main(int argc, char const *argv[]){

  FILE *fileSave; //This file to save in Option 6
  char saveName[MAX];
  //open database file
  fileIn = fopen(FILENAME, "rb");
  if(fileIn == NULL){
    perror("ERROR");
    return 1;
  }

  //This will Insert node from dat file (Insert after Current)
  while(!feof(fileIn)) InsertAfterCurrent(ReadFile());
  DeleteCurrent(); //Delete a raw last node because of reading file

  int menu, optionAdd; //menu: Option in main menu, optionAdd: option to Insert (befor or after cur)
  char search[MAX]; //key to search phone model

  //FreeAllList();

  do{ //Show menu
    switch(menu = GetMenu()){

    case 1: //Print all node
      TranverseList();
      break;

    case 2: //Insert new phone by Input and Choose Insert after of before current
      do{
	printf("   1. Insert After Current\n   2. Insert Before Current\n   Your option: ");
	clrBuff();
	scanf("%d", &optionAdd);
      }while(optionAdd < 1 || optionAdd > 2);
      if(optionAdd == 1) InsertAfterCurrent(AddNewPhone());
      else InsertBeforeCurrent(AddNewPhone());
      break;

    case 3: //Delete Current Node
      DeleteCurrent();
      break;

    case 4: //Delete First (root) node
      DeleteFirst();
      break;

    case 5: //Search Phone Model by enter model. Update is manual.
      printf("Enter Phone Model: "); clrBuff(); scanf("%s", search);
      SearchAndUpdate(search);
			
    case 6: //Export to File
      clrBuff();
      printf("Name of save file: "); scanf("%[A-Za-z0-9. -]s", saveName);
      fileSave = fopen(saveName, "wb"); //Create file to save
      node *p=root;
      //Do a loop to write to file node by node
      for(p = root; p->next != NULL; p = p->next)
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
    printf("1. Display (Tranverse)\n");
    printf("2. Add New Phone\n");
    printf("3. Delete Current\n");
    printf("4. Delete First\n");
    printf("5. Search and Update\n");
    printf("6. Save to File\n");
    printf("0. Exit\n");
    printf("Your choice: ");
    scanf("%d", &menu);
  }while(menu<0 || menu>=7);
  return menu;
} 


void SearchAndUpdate(char search[]){
  node *p = root;
  int changeOption=-1;

  //Do a loop to compare key to model
  for(p = root; p != NULL; p = p->next){ 

    //Compare key to model
    if(strcmp(search,p->element.model) == 0) { 
      PrintData(p->element); //Print out model if match
			
      //Update phone
      printf("Do you want to change this phone (1-Yes/0-No)? ");
      scanf("%d", &changeOption);
			
      if(changeOption == 1) p->element = AddNewPhone(); 
      //Use AddNewPhone function to change data of phone
    }
  }

  if (changeOption == -1) printf("No Phone Found!\n");	
  // if there exits a phone which be found, 
  // changeOption must be 0 or 1, but default is -1
}

void clrBuff(){
  while(getchar()!='\n');
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
////////////////////////////////////////////////////





/////LINK LIST FUNCTION////////////////////////////
node *MakeNewNode(elementType e){
  node *new = (node*)malloc(sizeof(node));
  new->element = e;
  new->next = NULL;
  return new;
}

void InsertAfterCurrent(elementType e){
  node *new = MakeNewNode(e);
  if(root == NULL){
    root = new;
    cur = root;
  }else{
    new->next = cur->next;
    cur->next = new;
    cur = cur->next;
  }
}

void InsertBeforeCurrent(elementType e){
  node *new = MakeNewNode(e);
  if(root == NULL){
    root = new;
    cur = root;
  }
  else if(cur == root){
    new->next = root;
    root = new;
    cur = new;
  }
  else{
    node *pre = FindPre();
    pre->next = new;
    new->next = cur;
    cur = new;
  }
}

void TranverseList(){
  node *p;
  if (root == NULL){ printf("List is empty!\n"); return;}
  for(p = root; p != NULL; p = p->next){
    PrintData(p->element);
  }
}

elementType ReadFile(){
  elementType temp;
  fread(&temp, sizeof(elementType), 1, fileIn);
  return temp;
}

void DeleteCurrent(){
  if (cur == root) DeleteFirst();
  else{
    node *pre = FindPre();
    pre->next = cur->next;
    free(cur);
    cur = pre;
  }
}

void DeleteFirst(){
  node *del = root;
  root = root->next;
  free(del);
}

node *FindPre(){
  if (root ==  NULL) return NULL;
  else if (cur == root) return root;
  else{
    node *pre = root;
    while (pre->next != cur) pre = pre->next;
    return pre;
  }
}

void FreeAllList(){
  node *toFree = root;
  while(toFree != NULL) {
    root = root->next;
    free(toFree);
    toFree = root;
  }
}
///////////////////////////////////////////////////
