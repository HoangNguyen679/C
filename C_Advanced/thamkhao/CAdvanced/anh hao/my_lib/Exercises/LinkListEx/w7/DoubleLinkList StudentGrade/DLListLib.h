/****************************** Module Header ******************************\
 * Library Name: Double Link List
 * Author:	 Nguyen Van Hao
 *
 * Provides essential functions of Double Link List Data Structure
 *
 * For use, Include this library after declare Element Type of each Program.
 *
 * #include <stdio.h>
 * typedef struct Element_Type{
 *	int id;
 *	char name[MAX];
 *	int grade;
 *	} elementType;
 * #include "DLListLib.h"
 *
 * another function and main program go here...
 *
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
\***************************************************************************/

typedef struct My_Node{
  struct My_Node *prev;
  elementType element;
  struct My_Node *next;
} node;

typedef struct DLList_t{
  node *head;// = NULL;
  node *tail; // = NULL;
  node *cur; // = NULL;
} DLList;

void clrBuff(void);
void ImportFile(DLList *List, FILE *fileIn);
node *MakeNewNode(elementType e);
void PrintData(elementType e);

void InsertAfterCurrent(DLList *List, elementType e);
void InsertBeforeCurrent(DLList *List, elementType e);
void InsertAtPosition(DLList *List, elementType e, int position);
void DeleteAtPosition(DLList *List, int position);
void DeleteCurrent(DLList *List);
node *MoveCurToPosition(DLList *List, int position);
DLList *DevideList(DLList *List1, DLList *List2, int position);
DLList *SplitList(DLList *List1, DLList *List2, int position, int List2Length);

void TraverseList(DLList *List);
void TraverseRevertList(DLList *List);
void FreeList(DLList *List);


void clrBuff(){
  while(getchar()!='\n');
}

/*elementType ReadFile(FILE *fileIn){
  elementType temp;
  int irc;
  irc = fread(&temp, sizeof(elementType), 1, fileIn);
  if (irc == 0) return;
  return temp;
  }*/

void ImportFile(DLList *List, FILE *fileIn){
  //This will Insert node from dat file (Insert after Current)
  elementType temp;
  int irc;
  while(1){
    irc = fread(&temp, sizeof(elementType), 1, fileIn);
    if (irc == 0) break;
    InsertAfterCurrent(List, temp);
  }
  fclose(fileIn);
}

node *MakeNewNode(elementType e){
  node *new = (node*)malloc(sizeof(node));
  new->prev = NULL;
  new->next = NULL;
  new->element = e;
  return new;
}



void TraverseList(DLList *List){
  node *p;
  if(List->head == NULL){
    printf("List is Empty!\n");
    return;
  }
  for(p = List->head; p != NULL; p = p->next){
    PrintData(p->element);
  }
}

void TraverseRevertList(DLList *List){
  node *p;
  if(List->head == NULL){
    printf("List is Empty!\n");
    return;
  }
  for(p = List->tail; p != NULL; p = p->prev){
    PrintData(p->element);
  }
}


void InsertAfterCurrent(DLList *List, elementType e){
  node *new = MakeNewNode(e);
  if(List->head == NULL){
    List->head = new;
    List->tail = new;
    List->cur = new;
  }
  else if(List->cur == List->tail){
    new->prev = List->cur;
    new->next = NULL;

    List->cur->next = new;
    List->tail = new;
    List->cur = List->tail;
  }
  else{
    new->prev = List->cur;
    new->next = List->cur->next;

    List->cur->next->prev = new;
    List->cur->next = new;

    //current must be new
    List->cur = new;
  }
}

void InsertBeforeCurrent(DLList *List, elementType e){
  if(List->cur == List->head){
    node *new = MakeNewNode(e);
    new->prev = NULL;
    new->next = List->head;

    List->cur->prev = new;
    List->head = new;
    List->cur = new;
  }
  else{
    List->cur = List->cur->prev;
    InsertAfterCurrent(List, e);
  }
}

/*void InsertBeforeCurrent(elementType e){
  node *new = MakeNewNode(e);
  if(head == NULL){
  head = new;
  tail = new;
  cur = new;
  }
  else if(cur->prev == NULL){
  new->prev = NULL;
  new->next = cur;

  cur->prev = new;
  head = new;
  cur = new;
  }
  else{
  new->prev = cur->prev;
  new->next = cur;

  cur->prev->next = new;
  cur->prev = new;

  //current must be new
  cur = new;
  }
  }*/

node *MoveCurToPosition(DLList *List, int position){
  List->cur = List->head;
  int i;
  for(i = 0; i < position; i++){
    if (List->cur->next == NULL){
    }
    else List->cur = List->cur->next;
  }
  return List->cur;
}

void InsertAtPosition(DLList *List, elementType e, int position){
  List->cur = List->head;
  if(position == 0) InsertBeforeCurrent(List, e);
  else{
    int i;
    for(i = 1; i < position; i++){
      if (List->cur->next == NULL){
      }
      else List->cur = List->cur->next;
    }
    InsertAfterCurrent(List, e);
  }
}

void DeleteCurrent(DLList *List){
  if (List->cur == List->head){
    List->head->next->prev = NULL;
    List->head = List->head->next;
    free(List->cur);
    List->cur = List->head;
  }
  else if (List->cur == List->tail){
    List->tail->prev->next = NULL;
    List->tail = List->tail->prev;
    free(List->cur);
    List->cur = List->tail;
  }
  else{
    node *toDel = List->cur;
    List->cur->prev->next = List->cur->next;
    List->cur->next->prev = List->cur->prev;
    List->cur = List->cur->prev;
    free(toDel);
  }
}

void DeleteAtPosition(DLList *List, int position){
  List->cur = MoveCurToPosition(List, position);
  DeleteCurrent(List);
}

void FreeList(DLList *List){
  node *toFree = List->head;
  while(toFree != NULL) {
    List->head = List->head->next;
    free(toFree);
    toFree = List->head;
  }
}

DLList *DevideList(DLList *List1, DLList *List2, int position){
  node *n; //n will be the devide point, n should be the end of list 1 and the head of list 2

  n = MoveCurToPosition(List1, position);

  List2->head = n;
  List2->cur = n;
  List2->tail = List1->tail;

  n->prev->next = NULL;
  List1->tail = n->prev;
  List1->cur = List1->head;

  return List2;
}

DLList *SplitList(DLList *List1, DLList *List2, int position, int List2Length){
  node *n, *p; //n will be the devide point, n should be the start of list 2
  // p should be the end of list 2 and p will connect to n to continue list 1
  // p-n is length of list 2

  n = MoveCurToPosition(List1, position);

  List2->head = n;
  List2->cur = n;

  p = MoveCurToPosition(List1, position+List2Length-1);
  List2->tail = p;

  n->prev->next = p->next;
  p->next->prev = n->prev;

  List2->tail->next = NULL;
}
