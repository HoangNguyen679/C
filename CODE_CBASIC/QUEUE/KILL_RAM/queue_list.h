#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct inf
{
  char ID[MAX];
  long memory;
}inf;
typedef inf elementtytpe;
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

void *enqueue(queue *q,inf x);

inf dequeue(queue *q);

void printQueue(queue q);

int sizeQueue(queue q);

void printList(node *root);

node *insert(node **root,inf x);

node *delete(node **root);

int size(node *root);

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

void *enqueue(queue *q,inf x)
{
  node *new;
  new=(node*)malloc(sizeof(node));
  new->prev=q->rear;
  new->next=NULL;
  q->rear->data=x;
  q->rear->next=new;
  q->rear=new;
}

inf dequeue(queue *q)
{
  node *tmp;
  inf temp;
  if(q->front!=q->rear)
    {
      tmp=q->front;
      q->front=q->front->next;
      q->front->prev=NULL;
      temp=tmp->data;
      free(tmp);
      return (temp);
    }
  else
    printf("Queue is empty\n");
}

void printQueue(queue q)
{
  int i=0;
  if(isEmpty_queue(q)) printf("\nEMPTY QUEUE\n");
  else
    {
      node *temp;
      for(temp = q.front; temp->next != NULL; temp = temp->next)
        printf("%-25s\t%ld\n",temp->data.ID,temp->data.memory);
    }
}

void printList(node *root)
{
  node *p = NULL;
  if(root == NULL)
    {printf("Empty list\n");return;}
  for(p = root; p != NULL; p = p->next)
    printf("%-30s\t%ld\n",p->data.ID,p->data.memory);
  return;
}

int size(node *root)
{
  int n=0;
  node *temp=root;
  if(root != NULL)
    for(temp = root; temp != NULL; temp = temp->next) n++;
    return n;
}

node *insert(node **root,inf x)
{
  if(*root == NULL)
    {
      node *new;
      new = (node *)malloc(sizeof(node));
      new->data = x;
      new->next = *root;
      new->prev = NULL;
      *root = new;
    }
  else
    {
      node *new;
      new = (node *)malloc(sizeof(node));
      new->data = x;
      new->next = NULL;
      if((*root)->next == NULL) 
	{
	  new->prev = (*root);
	  (*root)->next = new;
	  return *root;
	}
      node *temp;
      for(temp = *root; temp->next != NULL; temp = temp->next);      
      new->prev = temp;
      temp->next = new;
    }
  return *root;
}
