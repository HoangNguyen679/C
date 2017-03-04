#include <stdio.h>
#include <stdlib.h>

#define MAX 5


typedef int ElementType;

#include "QueueLLLib.h"

QueueType Q;

int main(int argc, char const **argv){
    InitQueue(&Q);

    int temp;

    while(temp != -1){
        scanf("%d", &temp);
        if(temp != -1){
            EnQueue(temp, &Q);
        }
        //printf("%d ", temp);
        while(!IsEmpty(&Q)) printf("%d ", DeQueue(&Q));
    }
    FreeQueue(Q);
    return 0;
}
