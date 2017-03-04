#include<stdio.h>
#include<stdlib.h>
#include"queue_list.h"

int main(){
  queue q;
  queueConstruct(&q);
  int i=0,n=5;
  while(i<n){
    enqueue(&q,i);
    i++;
  }
  printQueue(q);printf("\n\n");
  dequeue(&q);
  printQueue(q);
  return 0;
}
