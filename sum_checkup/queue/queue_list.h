#include <stdio.h>
#include <stdlib.h>

typedef int elementType;
typedef struct node {
  elementType elements;
  struct node *next;
} node;

typedef struct {
  node *front;
  node *rear;
} queue;

void queueConstruct(queue *q);

int isEmpty(queue q);

void enqueue(queue *q, elementType e);

elementType dequeue(queue *q);

void printQueue(queue q);

int sizeQueue(queue q);

void queueConstruct(queue *q){
  q->rear = q->front = NULL;
}

int isEmpty(queue q){
  return (q.front == NULL);
}

void enqueue(queue *q, elementType e){
  node *new;
  new = (node *)malloc(sizeof(node));
  new->next = NULL;
  new->elements = e;
  if(q->rear == NULL) {
    q->front = q->rear = new;
    return;
  }
  q->rear->next = new;
  q->rear = new;
}

elementType dequeue(queue *q)
{
  if(!isEmpty(*q)) {
      node *del;
      elementType a;
      del = q->front;
      a = q->front->elements;
      q->front = q->front->next;
      free(del);
      return a;
  } else printf("\n\nEMPTY QUEUE\n\n");
}

void printQueue(queue q)
{
  int i=0;
  if(isEmpty(q)) 
    printf("\n\nEMPTY QUEUE\n\n");
  else {
      node *temp;
      for(temp = q.front; temp != NULL; temp = temp->next)
        printf("%d\n",temp->elements);
    }
    printf("\n\n");
}
