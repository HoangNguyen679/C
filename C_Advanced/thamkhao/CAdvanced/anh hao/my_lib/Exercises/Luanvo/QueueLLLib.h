typedef struct SingleLL{
  ElementType element;
  struct SingleLL *next;
} node;

typedef struct Queue_t{
  node *front;
  node *rear;
} QueueType;

void InitQueue(QueueType *Q){
  Q->front = NULL;
  Q->rear = NULL;
}

int IsEmpty(QueueType *Q){
  return (Q->front == NULL);
}

void FreeQueue(QueueType *Q){
  node *toFree = Q->front;
  while(toFree != NULL) {
    Q->front = Q->front->next;
    free(toFree);
    toFree = Q->front;
  }
}

node *MakeNewNode(ElementType e){
  node *newn = (node*)malloc(sizeof(node));
  newn->element = e;
  newn->next = NULL;
  return newn;
}

void EnQueue(ElementType e, QueueType *Q){
  node *newn = MakeNewNode(e);
  if(IsEmpty(Q)) {
    Q->front = newn;
    Q->rear = newn;
  } else {
    Q->rear->next = newn;
    Q->rear = newn;
  }
}

ElementType DeQueue(QueueType *Q){
  if(IsEmpty(Q)) {
    printf("Queue Is Empty!\n");
    return;
  } else {
    node *temp = Q->front;
    ElementType e = temp->element;
    Q->front = Q->front->next;
    free(temp);
    return e;
  }
}
