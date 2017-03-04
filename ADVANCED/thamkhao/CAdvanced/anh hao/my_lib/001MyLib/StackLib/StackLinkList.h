typedef struct StackType_t{
  ElementType element;
  struct StackType_t *next;
} StackType;

int IsEmpty(StackType **top){
  return (*top == NULL);
}

void FreeStack(StackType **top){
  StackType *toFree = *top;
  while(toFree != NULL) {
    *top = (*top)->next;
    free(toFree);
    toFree = *top;
  }
}


void Push(ElementType element, StackType **top){
  StackType *p;
  p = (StackType*)malloc(sizeof(StackType));
  if(p == NULL) {
    printf("MAlloc Error!\n");
    return;
  }
  else{
    p->element = element;
    p->next = *top;
    *top = p;
  }
}

ElementType Pop(StackType **top){
  if(*top == NULL) {
    //printf("Stack Empty!\n");
    return;
  }
  else{
    ElementType temp;
    StackType *p;
    temp = (*top)->element;
    p = *top;
    *top = (*top)->next;
    free(p);
    return temp;
  }
}
