#include<stdio.h>
#include<stdlib.h>
#include"stackarray.h"
#define Max 50


void main() {
  stacktype stack;
  elementtype e;
  Initialize(stack);
  int i,x;
  for(i = 1 ; i <= 5 ; i++) {
    printf("Phan tu thu %d: ",i);
    scanf("%d",&e);
    push(e,stack);
  }
  for(i = 1 ; i <= 5 ; i++) {
    x = pop(stack);
    printf("%d\t",x);
  }
  printf("\n");
  return;
}
