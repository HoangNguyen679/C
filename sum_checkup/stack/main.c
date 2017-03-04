//#include "stack_arr.h"
#include "stack_list.h"

int main(){
  /* stack array
  int ch; int m;
  stack s; 
  while(1){
    printf("\n\n===========================\n\n");
    printf("CHUONG TRINH THU STACK");
    printf("\n\n===========================\n\n");
    printf("1. Creat\n2. Push\n3. Pop\n4. Display\n5. Exit\n");
    printf("Chon chuc nang: ");
    scanf("%d",&ch);printf("\n");
    switch(ch){
    case 1:
      stackConstruct(&s);
      printf("Da khoi tao STACK \n");
      break;
    case 2:
        printf("Nhap vao gia tri phan tu: ");scanf("%d",&m);
        push(&s,m);
        break;
    case 3: printf("Gia tri cua phan tu lay ra: %d\n",pop(&s)); break;
    case 4: printStack(s); break;
    case 5: printf("Bye bye! \n");return 0;
    default: printf("Wrong choice\n");
    }
  }
  */
	int ch; int m;
  	stack *s;
  	while(1){
    printf("\n\n=================\n\n");
    printf("CHUONG TRINH THU STACK\n\n");
    printf("=================\n");
    printf("1. Creat\n2. Push\n3. Pop\n4. Display\n5. Exit\n");
    printf("Chon chuc nang: ");
    scanf("%d",&ch);printf("\n");
    switch(ch){
    case 1:
      s = stackConstruct();
 	  printf("Da khoi tao STACK\n");
      break;
    case 2:
      printf("Nhap vao gia tri phan tu: ");scanf("%d",&m);
      push(s,m);  
      break;
    case 3: printf("Gia tri cua phan tu lay ra: %d\n",pop(s)); break;
    case 4: printStack(s); break;
    case 5: printf("Bye bye! \n");return 0;
    default: printf("Wrong choice\n");
    }
  }
}
