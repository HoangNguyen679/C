#include<stdio.h>
#include<stdlib.h>

typedef struct time
{
  int gio, phut;
}time;
typedef time elementtytpe;
typedef struct node
{
  elementtytpe data;
  struct node *next;
  struct node *prev;
}node;
typedef struct
{
  node *front;
  node *rear;
}queue;

void queueConstruct(queue *q);

int isEmpty_queue(queue q);

void *enqueue(queue *q,elementtytpe x);

time dequeue(queue *q);

//void printQueue(queue q);

int sizeQueue(queue q);

void queueConstruct(queue *q)
{
  q->front = (node *)malloc(sizeof(node));
  q->front->next = NULL;
  q->front->prev = NULL;
  q->rear = q->front;
}

int isEmpty_queue(queue q)
{
  return (q.front == q.rear);
}

void *enqueue(queue *q,elementtytpe x)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->prev=q->rear;
  new->next=NULL;
  q->rear->data=x;
  q->rear->next=new;
  q->rear=new;
}

time dequeue(queue *q)
{
  if(!isEmpty_queue(*q))
    {
      node *del;
      time temp;
      del = q->front;
      q->front = q->front->next;
      q->front->prev= NULL;
      temp = del->data;
      free(del);
      return temp;
    } else printf("\n\nEMPTY QUEUE\n\n");
}
/*
void printQueue(queue q)
{
  int i=0;
  if(isEmpty_queue(q)) printf("\n\nEMPTY QUEUE\n\n");
  else
    {
      node *temp;
      for(temp = q.front->next; temp != NULL; temp = temp->next)
        printf("%d\n",temp->data);
    }
}
*/
