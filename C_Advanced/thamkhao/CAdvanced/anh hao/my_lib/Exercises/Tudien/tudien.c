#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define MAX 20

typedef struct Word {
  char eng[MAX];
  char vie[MAX];
} elementType;

#include "BSTLibSearchString.h"
typedef elementType ElementType;
#include "QueueLLLib.h"
QueueType Q;

int GetMenu(void);
void clrBuf(void);
void ReadFile(char *fileName);
void PrintDataTree(elementType e);
void Translate(char *s);

nodeTree *myDict;

int main(){
  char s[200];
  int menu = 0;
  do {
    switch (menu = GetMenu()) {
    case 1: InitTree(&myDict); ReadFile("data.txt"); break;
    case 2: InOrderTraverser(myDict); break;
    case 3: 
      printf("Input a sentence:\n");
      clrBuf(); 
      gets(s);
      Translate(s);
      break;
    case 0: printf("Goodbye!\n"); break;
    default: printf("Invalid Option\n"); break;
    }
  } while (menu != 0);
  FreeTree(&myDict);
  return 0;
}

void ReadFile(char *fileName) {
  FILE *f = fopen("data.txt", "r");
  if (f == NULL) {
    printf("Can not open file!\n");
    exit(1);
  }
  elementType temp;
  while (!feof(f)) {
    fscanf(f, "%s\t", temp.eng);
    fgets(temp.vie, 100, f);
    int n = strlen(temp.vie)-2;
    temp.vie[n] = '\0';
    InsertToBTS(&myDict, temp); 
  }
  fclose(f);
}

void PrintDataTree(elementType e) {
  printf("%-20s%-20s\n", e.eng, e.vie);
}

void Translate(char *s) {
  InitQueue(&Q);
  char *pch;
  int i = 0, lenP = 0;
  elementType temp;
  pch = strtok(s, " ,.|()-?:");
  while (pch != NULL) {
    lenP = strlen(pch);
    for (i = 0; i < lenP; i++) pch[i] = tolower(pch[i]);
    strcpy(temp.eng, pch);
    nodeTree *re = SearchTree(myDict, temp);
    if (re == NULL) {
      printf("[%s:notfound] ", temp.eng);
      //return;
      EnQueue(temp, &Q);
    } else printf("%s ", re->element.vie);
  pch = strtok(NULL, " ,.|()-?:");
  }
  printf("\n");
  
  FILE *f = fopen("data.txt","a");
  if (f == NULL) {printf("Cannot open file"); return;}
  if (!IsEmpty(&Q)) {
    printf("There are some missing word! Please import to database\n");
  } 
  while (!IsEmpty(&Q)) {
    temp = DeQueue(&Q); 
    printf("%s: ", temp.eng);
    gets(temp.vie);
    InsertToBTS(&myDict, temp);
    fprintf(f, "%s\t%s\n", temp.eng, temp.vie); 
  }
  fclose(f);
  
  FreeQueue(&Q);
}


int GetMenu(void) {
  int menu = 0;

  printf("\n---MENU---\n");
  printf("1. Import File\n");
  printf("2. Show Dict\n");
  printf("3. Translate\n");
  printf("0. Exit\n");
  printf("Your Choice: ");
  //  clrBuf();
  scanf("%d", &menu);
  return menu;
}

void clrBuf(void) {
  while(getchar() != '\n');
}

