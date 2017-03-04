#include "queue_arr_circle.h"

int main(){
  queue q;
  queueConstruct(&q);
  int i = 0, n = 5;
  while(i < n){
    enqueue(&q,i);
    i++;
  }
  printQueue(q);
  dequeue(&q);
  printQueue(q);
  return 0;
}
