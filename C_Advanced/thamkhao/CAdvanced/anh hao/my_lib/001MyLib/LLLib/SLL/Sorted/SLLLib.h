typedef struct My_Node{
  elementType element;
  struct My_Node *next;
} node;

node *root = NULL;
node *cur = NULL;

////LINK LIST's PROTOTYPE DECLATION
void clrBuff();
node *MakeNewNode(elementType);
void InsertAfterCurrent(elementType);
void TraverseList();
void ImportFile(char *filename);
void ImportFileSorted(char* filename);
//elementType ReadFile(FILE *fileIn);
void InsertBeforeCurrent(elementType);
void DeleteCurrent();
void DeleteFirst();
node *FindPre();
void FreeAllList();
void DeleteAtPosition(int);
void InsertAtPosition(elementType, int);
void ListReverse();
////////////////////////////////////


void clrBuff(){
  while(getchar()!='\n');
}

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

void TraverseList(){
  node *p;
  if (root == NULL){ printf("List is empty!\n"); return;}
  for(p = root; p != NULL; p = p->next){
    PrintData(p->element);
  }
}

void ImportFile(char* filename){
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
    InsertAfterCurrent(temp);
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


/*elementType ReadFile(FILE *fileIn){
  elementType temp;
  fread(&temp, sizeof(elementType), 1, fileIn);
  return temp;
}*/


/*void ImportFileSorted(char* filename){
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
}*/
/*
void InsertSorted(elementType e){
  node *new = MakeNewNode(e);
  //if(e.price == 0) return;
  if(root == NULL) {
    root = new;
    root->next = NULL;
    cur =  new;
  }else if(strcmp(new->element.eng,root->element.eng) > 0) {
    new->next = root;
    root = new;
    cur = new;
  }else {
    node *prev;
    cur = root;
    while(cur != NULL && strcmp(new->element.eng,root->element.eng) <= 0){
      prev = cur;
      cur = cur->next;
    }
    prev->next= new;
    new->next = cur;
  }
}

void SortList() {
  node *p, *q;
  elementType temp;
  for(p = root; p != NULL; p = p->next){
    for(q = p->next; q != NULL; q = q->next){
      if (strcmp(p->element.eng,q->element.eng)>0) {
  temp = q->element;
  q->element = p->element;
  p->element = temp;
      }
    }
  }
}
*/