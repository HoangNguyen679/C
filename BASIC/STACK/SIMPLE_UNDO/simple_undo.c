#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stack_list.h"

int main(){
  stack *s1=stackConstruct(),*s2=stackConstruct();
  do{
    printf("\n\n>>>>>>>>>>MENU<<<<<<<<<<\n\n");
    printf("1. PUSH AN INTEGER\n");
    printf("2. PRINT TOP\n");
    printf("3. POP\n");
    printf("4. UNDO\n");
    printf("5. EXIT\n\n");
    printf("Please select: ");
    int ch; scanf("%d",&ch);printf("\n");
    switch(ch)
      {
      case 1:
        {
          printf("Enter an integer: ");
          dl a; scanf("%d",&(a.n));
          dl b; strcpy(b.str,"PUSH");b.n = 0;
          push(s1,a);push(s2,b);
        }break;
      case 2:
        {
          if(isEmpty_stack(s1))
            {printf("EMPTY\n\n");}
          else
            {
              dl c= top(*s1);
              printf("---------> TOP: %d",c.n);
            }
        }break;
      case 3:
        {
          dl d = pop(s1);
          strcpy(d.str,"POP");
          push(s2,d);
        }break;
      case 4:
        {
          if(isEmpty_stack(s2))
            printf("NOTHING TO UNDO\n\n");
          else
            {
              dl e = pop(s2);
              if (strcmp(e.str,"PUSH") == 0)
                pop(s1);
              if (strcmp(e.str,"POP") ==0)
                push(s1,e);
              printf("UNDO SUCCESS\n\n");
            }
        }break;
      case 5: return;
      default: printf("Wrong choice!\n\n");
      }
  }while(1);
  return 0;
}
