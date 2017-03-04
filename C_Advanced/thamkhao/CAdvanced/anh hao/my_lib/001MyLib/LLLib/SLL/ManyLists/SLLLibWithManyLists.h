typedef struct My_Node{
  elementType element;
  struct My_Node *next;
} node;

typedef struct SLL_t{
  node *root;
  node *cur;
} SLList;



////LINK LIST's PROTOTYPE DECLATION
void clrBuff();
void InitSLList(SLList *List);
node *MakeNewNode(elementType);
void InsertAfterCurrent(SLList *List, elementType);
void TraverseList(SLList *List);
void ImportFile(SLList *List, char *filename);
//void ImportFileSorted(SLList *List, char* filename);
elementType ReadFile(FILE *fileIn);
void InsertBeforeCurrent(SLList *List, elementType);
void DeleteCurrent(SLList *List);
void DeleteFirst(SLList *List);
node *FindPre(SLList *List);
void FreeAllList(SLList *List);
void DeleteAtPosition(SLList *List, int);
void InsertAtPosition(SLList *List, elementType, int);
void ListReverse(SLList *List);
////////////////////////////////////


void clrBuff(){
  while(getchar()!='\n');
}

node *MakeNewNode(elementType e){
  node *newn = (node*)malloc(sizeof(node));
  newn->element = e;
  newn->next = NULL;
  return newn;
}

void InsertAfterCurrent(SLList *List, elementType e){
  node *newn = MakeNewNode(e);
  if(List->root == NULL){
    List->root = newn;
    List->cur = List->root;
  }else{
    newn->next = List->cur->next;
    List->cur->next = newn;
    List->cur = List->cur->next;
  }
}

void InsertBeforeCurrent(SLList *List, elementType e){
  node *newn = MakeNewNode(e);
  if(List->root == NULL){
    List->root = newn;
    List->cur = List->root;
  }
  else if(List->cur == List->root){
    newn->next = List->root;
    List->root = newn;
    List->cur = newn;
  }
  else{
    node *pre = FindPre(List);
    pre->next = newn;
    newn->next = List->cur;
    List->cur = newn;
  }
}

void TraverseList(SLList *List){
  node *p;
  if (List->root == NULL){ printf("List is empty!\n"); return;}
  for(p = List->root; p != NULL; p = p->next){
    PrintData(p->element);
  }
}

void ImportFile(SLList *List, char* filename){
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
    //InsertSorted(temp);
    printf("1");
    InsertAfterCurrent(List, temp);
  }
  fclose(fileIn);
}

void DeleteCurrent(SLList *List){
  if (List->cur == List->root) DeleteFirst(List);
  else{
    node *pre = FindPre(List);
    pre->next = List->cur->next;
    free(List->cur);
    List->cur = pre;
  }
}

void DeleteFirst(SLList *List){
  node *del = List->root;
  List->root = List->root->next;
  free(del);
  List->cur = List->root;
}

node *FindPre(SLList *List){
  if (List->root ==  NULL) return NULL;
  else if (List->cur == List->root) return List->root;
  else{
    node *pre = List->root;
    while (pre->next != List->cur) pre = pre->next;
    return pre;
  }
}

void FreeAllList(SLList *List){
  node *toFree = List->root;
  while(toFree != NULL) {
    List->root = List->root->next;
    free(toFree);
    toFree = List->root;
  }
}

void DeleteAtPosition(SLList *List, int position){
  List->cur = List->root;
  int i;
  for (i = 0; i < position; i++) {
    if(List->cur->next == NULL) {
    }
    else
      List->cur= List->cur->next;
  }
  DeleteCurrent(List);
}

void InsertAtPosition(SLList *List, elementType e, int position){
  List->cur = List->root;
  if(position == 0) {
    InsertBeforeCurrent(List, e);
    return;
  }
  int i;
  for (i = 1; i < position; i++) {
    if(List->cur->next == NULL) {
    }
    else List->cur= List->cur->next;
  }
  InsertAfterCurrent(List, e);
}


void ListReverse(SLList *List){
  node *prev;
  List->cur = prev = NULL;
  while(List->root->next != NULL){
    List->cur = List->root;
    List->root = List->root->next;
    List->cur->next = prev;
    prev = List->cur;
  }
  List->root->next = List->cur;
  List->cur = List->root;
}


elementType ReadFile(FILE *fileIn){
  elementType temp;
  fread(&temp, sizeof(elementType), 1, fileIn);
  return temp;
}

void InitSLList(SLList *List){
  List->root = NULL;
  List->cur = NULL;
}

// void ImportFileSorted(char* filename){
//   //open database file
//   FILE* fileIn = fopen(filename, "rb");
//   if(fileIn == NULL){
//     perror("ERROR");
//     return;
//   }
//   //This will Insert node from dat file (Insert after current)
//   elementType temp;
//   int irc;
//   while(1){
//     irc = fread(&temp, sizeof(elementType), 1, fileIn);
//     if (irc == 0) break;
//     InsertSorted(temp);
//     //InsertAfterCurrent(temp);
//   }
//   fclose(fileIn);
// }

// void InsertSorted(elementType e){
//   node *newn = MakeNewNode(e);
//   if(e.price == 0) return;
//   if(List->root == NULL) {
//     List->root = newn;
//     List->root->next = NULL;
//     List->cur =  newn;
//   }else if(newn->element.price > List->root->element.price) {
//     newn->next = List->root;
//     List->root = newn;
//     List->cur = newn;
//   }else {
//     node *prev;
//     List->cur = List->root;
//     while(List->cur != NULL && newn->element.price <= List->cur->element.price){
//       prev = List->cur;
//       List->cur = List->cur->next;
//     }
//     prev->next= newn;
//     newn->next = List->cur;
//   }
// }