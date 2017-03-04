#include<stdio.h>
#include<stdlib.h>

typedef int elementtytpe;
typedef struct node
{
  elementtytpe data;
  struct node *next;
}node;
typedef struct
{
  node *front;
  node *rear;
}queue;

void queueConstruct(queue *q);

int isEmpty_queue(queue q);

void enqueue(queue *q,elementtytpe x);

elementtytpe dequeue(queue *q);

void printQueue(queue q);

int sizeQueue(queue q);

void queueConstruct(queue *q)
{
  q->rear = q->front=NULL;
}

int isEmpty_queue(queue q)
{
  return (q.front == NULL);
}

void enqueue(queue *q,elementtytpe x)
{
  node *new;
  new=(node *)malloc(sizeof(node));
  new->next=NULL;
  new->data=x;
  if(q->rear == NULL)
    {q->front=q->rear=new;return;}
  q->rear->next = new;
  q->rear = new;
}

elementtytpe dequeue(queue *q)
{
  if(!isEmpty_queue(*q))
    {
      node *del;
      elementtytpe a;
      del = q->front;
      a=q->front->data;
      q->front = q->front->next;
      free(del);
      return a;
    }
  printf("\n\nEMPTY QUEUE\n\n");
}

void printQueue(queue q)
{
  int i=0;
  if(isEmpty_queue(q)) printf("\n\nEMPTY QUEUE\n\n");
  else
    {
      node *temp;
      for(temp = q.front; temp != NULL; temp = temp->next)
        printf("%d\n",temp->data);
    }
}
