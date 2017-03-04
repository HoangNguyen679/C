#include <stdio.h>
#include <stdlib.h>

#define MAX 5


typedef int elementType;

typedef struct Queue_t{
    elementType element[MAX];
    int front, rear;
} Queue;

int IsFull(Queue *Q){
    return (((Q->rear-Q->front+1)%MAX) == 0);
}

int IsEmpty(Queue *Q){
    return (Q->front == -1);
}

int InitQueue(Queue *Q){
    Q->front = -1;
    Q->rear = -1;
}

void EnQueue(elementType e, Queue *Q){
    if(!IsFull(Q)){
        if(IsEmpty(Q)) Q->front = 0;
        Q->rear = (Q->rear+1)%MAX;
        Q->element[Q->rear] = e;
    } else printf("Queue is Full!\n");
}

elementType DeQueue(Queue *Q){
    if(!IsEmpty(Q)){
        elementType temp = Q->element[Q->front];
        Q->front = (Q->front+1)%MAX;
        return temp;
    } else printf("Queue is Empty!\n");
}


Queue Q;


int main(int argc, char const **argv){
    InitQueue(&Q);

    int temp;

    while(temp != -1){
        scanf("%d", &temp);
        if(temp != -1){
            if(IsFull(&Q)) printf("%d ", DeQueue(&Q));
            EnQueue(temp, &Q);
        }
        //printf("%d ", temp);
    }
    return 0;
}
