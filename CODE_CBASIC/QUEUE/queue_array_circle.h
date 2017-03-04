#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef int elementtytpe;
typedef struct {
  elementtytpe e[MAX];
  int front;
  int rear;
}queue;

void queueConstruct(queue *q);

int isEmpty_queue(queue q);

int isFull_queue(queue q);

void enqueue(queue *q,elementtytpe x);

void dequeue(queue *q);

void printQueue(queue q);

int sizeQueue(queue q);

void queueConstruct(queue *q){
  q->front = q->rear = -1;
}

int isEmpty_queue(queue q){
  return (q.front == -1);
}

int isFull_queue(queue q){
  return ((q.rear - q.front +1) %  MAX == 0);
}

void enqueue(queue *q,elementtytpe x){
  if(!isFull_queue(*q)){
    if(isEmpty_queue(*q)) q->front = 0;
    q->rear = (q->rear +1) % MAX;
    q->e[q->rear] =x;
  } else printf("\n\nFULL QUEUE\n\n");
}

void dequeue(queue *q){
  if(!isEmpty_queue(*q)){
    if(q->front == q->rear) queueConstruct(q);
    else q->front = (q->front+1) % MAX;
  } else printf("\n\nEMPTY QUEUE\n\n");
}

void printQueue(queue q){
  int i=0;
  if(isEmpty_queue(q)) printf("\n\nEMPTY QUEUE\n\n");
  else for(i=q.front; i<=q.rear; i++){
      printf("%d\n",q.e[i]);
    }
}
