#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctype.h>

#define MAX 20
#define FILENAME "contact.dat"

typedef struct Element_Type{
  char name[MAX];
  char number[MAX];
  char email[MAX];
} elementType;

typedef struct My_Node{
  elementType element;
  struct My_Node *next;
} node;

node *root;
node *cur;

FILE *fileIn;

node *MakeNewNode(elementType);
void InsertAfterCurrent(elementType);
void TranverseList();
elementType ReadData();
void InsertBeforeCurrent(elementType);




void PrintData(elementType e){
  printf("%s - %s - %s\n", e.name, e.number, e.email);
}


int main(int argc, char const *argv[])
{
  //printf("Hello!\n");
  fileIn = fopen(FILENAME, "rb");
  if(fileIn == NULL){
    perror("ERROR");
    return 1;
  }

  while(!feof(fileIn)){
    InsertBeforeCurrent(ReadData());
    //PrintData(ReadData());
  }

  TranverseList();
  fclose(fileIn);
  return 0;
}


/////LINK LIST FUNCTION
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
  else if(root->next == NULL){
    new->next = root;
    root = new;
    cur = root->next;
  }
  else{
    node *pre = root;
    while(pre->next != cur){
      pre = pre->next;
    }
    pre->next = new;
    new->next = cur;
    cur = new->next;
  }
}

void TranverseList(){
  node *p;
  for(p = root; p != NULL; p = p->next){
    PrintData(p->element);
  }
}

elementType ReadData(){
  elementType temp;
  fread(&temp, sizeof(elementType), 1, fileIn);
  return temp;
}
