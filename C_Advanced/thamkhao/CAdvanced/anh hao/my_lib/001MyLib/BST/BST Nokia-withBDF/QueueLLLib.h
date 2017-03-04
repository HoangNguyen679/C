typedef struct SingleLL{
	nodeTree *element;
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

int IsEmptyQueue(QueueType *Q){
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

node *MakeNewNode(nodeTree * e){
	node *newn = (node*)malloc(sizeof(node));
	newn->element = e;
	newn->next = NULL;
	return newn;
}

void EnQueue(nodeTree * e, QueueType *Q){
	node *newn = MakeNewNode(e);
	if(IsEmptyQueue(Q)) {
		Q->front = newn;
		Q->rear = newn;
	} else {
		Q->rear->next = newn;
		Q->rear = newn;
	}
}

nodeTree * DeQueue(QueueType *Q){
	if(IsEmptyQueue(Q)) {
		printf("Queue Is Empty!\n");
		return;
	} else {
		node *temp = Q->front;
		nodeTree * e = temp->element;
		Q->front = Q->front->next;
		free(temp);
		return e;
	}
}