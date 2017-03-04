#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"stack_list.h"
#define MAX 10000

void sum(char num1[],char num2[]);
void minus(char num1[],char num2[]);
int check(char num[]);

int main(){
  char num1[MAX],num2[MAX];
  int ch;
  do{printf("\nNhap vao so nguyen duong thu nhat: ");scanf("%s",num1);} while(check(num1));
  do{printf("\nNhap vao so nguyen duong thu hai: ");scanf("%s",num2);} while(check(num2));
  do{
    printf("\n\n>>>>>>>>>>MENU<<<<<<<<<<\n\n");
    printf("1. Cong hai so\n");
    printf("2. Tru so thu nhat cho so thu hai\n");
    printf("3. Thoat\n");
    printf("\nNhap lua chon: ");scanf("%d",&ch);
    switch(ch){
    case 1: sum(num1,num2);break;
    case 2: minus(num1,num2);break;
    case 3: return;break;
    default: printf("Wrong choice\n");
    }

  }while(1);
  return 0;
}

int check(char num[]){
  int i;
  for(i=0; num[i] != '\0'; i++)
    if(num[i] < '0' || num[i] > '9') return 1;
  return 0;
}

void sum(char num1[],char num2[]){
  stack *a1=stackConstruct(),*a2=stackConstruct(),*a=stackConstruct();
  int i;int s1,s2,r=0,s;
  for(i=0; num1[i] != '\0'; i++) push(a1,num1[i] - '0');
  for(i=0; num2[i] != '\0'; i++) push(a2,num2[i] - '0');
  while(!isEmpty(a1) && !isEmpty(a2)){
    s1=pop(a1);s2=pop(a2); s=s1+s2+r;
    if(s<10) {push(a,s);r=0;}
    else {r=1;push(a,s-10);}
  }
  while(!isEmpty(a1)){ push(a,pop(a1)+r); r=0; }
  while(!isEmpty(a2)){ push(a,pop(a2)+r); r=0; }
  printStack(a);
}

void minus(char num1[],char num2[]){
  stack *a1=stackConstruct(),*a2=stackConstruct(),*a=stackConstruct();
  if(strlen(num2)<strlen(num1)||(strlen(num1)==strlen(num2)&&strcmp(num1,num2)==1))
  {
    int i;int s1,s2,r=0,s;
    for(i=0; num1[i] != '\0'; i++) push(a1,num1[i] - '0');
    for(i=0; num2[i] != '\0'; i++) push(a2,num2[i] - '0');
    while(!isEmpty(a1) && !isEmpty(a2)){
      s1=pop(a1);s2=pop(a2); s = s1 - s2 - r;
      if(s>=0){push(a,s);r=0;}
      else {push(a,s+10);r=1;}
    }
    while(!isEmpty(a1)){
      s1=pop(a1); s=s1-r;
      if(s>=0){push(a,s);r=0;}
      else {push(a,s+10);r=1;}
    }
    while(!isEmpty(a2)){
      s2=pop(a1); s=s2-r;
      if(s>=0){push(a,s);r=0;}
      else {push(a,s+10);r=1;}
    }
  printStackMinus(a);
  }
  else {printf("-");minus(num2,num1);}
}
