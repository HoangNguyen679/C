#include<stdio.h>
#include<stdlib.h>
#include"stack_struct.h"

int main(){
  int ch; float m;
  stack s;
  while(1){
    printf("\n\n=================\n\n");
    printf("CHUONG TRINH THU STACK\n\n");
    printf("=================\n");
    printf("1. Creat\n2. Push\n3. Pop\n4. Display\n5. Exit\n");
    printf("Chon chuc nang: ");
    scanf("%d",&ch);printf("\n");
    switch(ch){
    case 1:
      printf("Da khoi tao STACK\n");
      s = stackConstruct(&s);
      break;
    case 2:{
      int j=0;
      do{
        printf("Nhap vao gia tri phan tu: ");scanf("%f",&m);
        push(&s,m);
        j++;
      }while(j<5);}
      break;
    case 3:
      m = pop(&s);
      printf("Gia tri cua phan tu lay ra: %8.3f\n",m);
      //else printf("\n\n >>> EMPTY STACK <<<\n");
      break;
    case 4:
      printStack(s); break;
    case 5:
      printf("\nBye bye! \n");return;break;
    default:
      printf("Wrong choice\n");
    }
  }
}
