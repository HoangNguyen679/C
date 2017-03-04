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

node *root = NULL;
node *cur = NULL;
FILE *fileIn;

////PROGRAM's PROTOTYPE DECLATION
void clrBuff();
void SearchAndUpdate(char []);
void PrintData(elementType);
elementType AddNewPhone();
int GetMenu();
////////////////////////////////////
////LINK LIST's PROTOTYPE DECLATION
node *MakeNewNode(elementType);
void InsertAfterCurrent(elementType);
void TranverseList();
void ImportFile(FILE *fileIn);
elementType ReadFile();
void InsertBeforeCurrent(elementType);
void DeleteCurrent();
void DeleteFirst();
node *FindPre();
void FreeAllList();
void DeleteAtPosition(int);
void InsertAtPosition(elementType, int);
void ListReverse();
////////////////////////////////////


void InsertSorted(elementType e){
  node *new = MakeNewNode(e);
  if(e.price == NULL) return;
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

  char search[MAX]; //key to search phone model
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
      InsertSorted(AddNewPhone());
      break;

    case 4:
      break;
    case 5:
      clrBuff();
      do{
	printf("What position do you want to delete?");
	scanf("%d", &position);
      } while(position < 0);
      DeleteAtPosition(position);
      break;
    case 6: //Delete Current Node
      DeleteCurrent();
      break;

    case 7: //Delete First (root) node
      DeleteFirst();
      break;

    case 8: //Search Phone Model by enter model. Update is manual.
      printf("Enter Phone Model: "); clrBuff(); scanf("%s", search);
      SearchAndUpdate(search);
      break;

    case 9:
      ListReverse();
      break;

    case 10: //Export to File
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
    printf("1. Import from nokia.dat\n");
    printf("2. Display (Tranverse)\n");
    printf("3. Insert Phone\n");
    printf("5. Delete at Position\n");
    printf("6. Delete Current\n");
    printf("7. Delete First\n");
    printf("8. Search and Update\n");
    printf("9. Reverse List\n");
    printf("10. Save to File\n");
    printf("0. Exit\n");
    printf("Your choice: ");
    scanf("%d", &menu);
  }while(menu<0 || menu>=12);
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

void ImportFile(FILE *fileIn){
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
  cur = root;
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

void DeleteAtPosition(int position){
  cur = root;
  int i;
  for (i = 0; i < position; i++) {
    if(cur->next == NULL) {
    }
    else
      cur= cur->next;
  }
  DeleteCurrent();
}

void InsertAtPosition(elementType e, int position){
  cur = root;
  if(position == 0) {
    InsertBeforeCurrent(e);
    return;
  }
  int i;
  for (i = 1; i < position; i++) {
    if(cur->next == NULL) {
    }
    else cur= cur->next;
  }
  InsertAfterCurrent(e);
}


void ListReverse(){
  node *prev;
  cur = prev = NULL;
  while(root->next != NULL){
    cur = root;
    root = root->next;
    cur->next = prev;
    prev = cur;
  }
  root->next = cur;
  cur = root;
}


elementType ReadFile(){
  elementType temp;
  fread(&temp, sizeof(elementType), 1, fileIn);
  return temp;
}
