#include<stdio.h>
#include<stdlib.h>
#include"stackstruct.h"
#define MAX 50
void putInStack(stacktype *p,long n){
  long thuong;
  int i=0,sodu[MAX];
  for(i = 0 ; i < MAX ; i++) sodu[i] = 0;
  thuong = n;
  i=0;
  while(thuong > 0) {
    thuong = thuong / 10 ;
    sodu[i] = n - thuong * 10;
    n = n/10;
    i++;
  }
  i--;
  for(i ; i >= 0 ; i--) push(sodu[i],p);
}

main() {
  stacktype stack1,stack2,stackadd;
  Initialize(&stack1);
  Initialize(&stack2);
  Initialize(&stackadd);

  long num1,num2,sum=0;
  printf("Enter number 1: ");scanf("%ld",&num1);
  printf("Enter number 2: ");scanf("%ld",&num2);

  putInStack(&stack1,num1);
  putInStack(&stack2,num2);
  /*
   while(isEmpty(stack1) == 0) {
    printf("%d",pop(&stack1));
  }
   printf("\n");
    while(isEmpty(stack2) == 0) {
    printf("%d",pop(&stack2));
  }
   printf("\n");
  */
  int flag=0,a,b;
  while(isEmpty(stack1) == 0 || isEmpty(stack2) == 0) {
    a=b=0;
    a=pop(&stack1);
    b=pop(&stack2);
    if((a+b+flag) > 9) {
      push(a+b+flag-10,&stackadd);
      flag=1;
    }else {
      push(a+b+flag,&stackadd);
      flag=0;
    }
    while (isEmpty(stack1) != 0 && isEmpty(stack2) == 0) {
      push(pop(&stack2),&stackadd);
    }
    while (isEmpty(stack2) != 0 && isEmpty(stack1) == 0) {
      push(pop(&stack1),&stackadd);
    }
  }
  printf("Sum is: ");
  while(isEmpty(stackadd) == 0) {
    printf("%d",pop(&stackadd));
  }
  printf("\n");
}
