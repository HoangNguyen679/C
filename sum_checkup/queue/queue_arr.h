#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef int elementType;
typedef struct {
  elementType elements[MAX];
  int front;
  int rear;
} queue;

void queueConstruct(queue *q);

int isEmpty(queue q);

int isFull(queue q);

void enqueue(queue *q, elementType e);

void dequeue(queue *q);

void printQueue(queue q);

int sizeQueue(queue q);

void queueConstruct(queue *q){
  q->front = q->rear = -1;
}

int isEmpty(queue q){
  return (q.front == -1);
}

int isFull(queue q){
  return (q.rear - q.front +1 == MAX);
}

void enqueue(queue *q, elementType e){
  if(!isFull(*q)){
    if(isEmpty(*q)) q->front = 0;
    q->rear = q->rear +1;
    q->elements[q->rear] = e;
  } else printf("\n\nFULL QUEUE\n\n");
}

void dequeue(queue *q){
  if(!isEmpty(*q)){
    q->front = q->front +1;
    if(q->front > q->rear) queueConstruct(q);
  } else printf("\n\nEMPTY QUEUE\n\n");
}

void printQueue(queue q){
  int i=0;
  if(isEmpty(q)) 
  	printf("\n\nEMPTY QUEUE\n\n");
  else 
  	for(i = q.front; i <= q.rear; i++){
      printf("%d\n",q.elements[i]);
    }
    printf("\n\n");
}
