#include<stdio.h>
#include<stdlib.h>
#include"element.h"
typedef struct node
{elementtype data;struct node *next;struct node *prev;}node;
typedef struct queue
{node *front,*rear;}queue;
//==========================================================
void make(queue *q);
void enq(queue *q,elementtype data);
elementtype deq(queue *q);
int isempty(queue q);
//==========================================================
//Make =====================================================
void make(queue *q)
{
  node *tmp;
  tmp=(node*)malloc(sizeof(node));
  tmp->next=NULL;tmp->prev=NULL;
  q->front=q->rear=tmp;
}
//is empty =================================================
int isempty(queue q)
{return q.front==q.rear;}
//enqueue ==================================================
void enq(queue *q,elementtype data)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->prev=q->rear;
  new->next=NULL;
  q->rear->data=data;
  q->rear->next=new;
  q->rear=new;
}
//dequeue ==================================================
elementtype deq(queue *q)
{
  node *tmp;
  elementtype data;
  if(q->front!=q->rear)
    {tmp=q->front;
      q->front=q->front->next;q->front->prev=NULL;
      data=tmp->data;
      free(tmp);
      return (data);
    }
  else
    printf("Queue is empty\n");
}
