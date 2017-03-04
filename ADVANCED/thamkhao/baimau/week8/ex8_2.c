#include<stdio.h>
#include<stdlib.h>
#define MAX 80
typedef struct so
{int data[MAX];int top;}so;
void init(so *n)
{n->top=0;}
void view(so n)
{
  if(n.top==0) printf("Stack is empty\n");
  else  printf("Top=%d\n",n.data[n.top-1]);
}
void push(so *n,int data)
{
  if(n->top<MAX-1)
    {n->data[n->top]=data;n->top++;}
  else printf("Stack over\n");
}
int pop(so *n)
{
  if(n->top==0) printf("Stack is empty\n");
  else {n->top--;return (n->data[n->top]);}
}
int main()
{
  so n,n1,s;
  int i,ch,j;
  init(&n);init(&n1);init(&s);
  printf("1-Push 1 so nguyen vao stack\n");
  printf("2-Pop 1 so nguyen ra khoi stack\n");
  printf("3-In phan tu top\n");
  printf("4-Undo\n");
  printf("5-Thoat\n");
  do{
    printf("Chon:");
    scanf("%d",&ch);
    switch(ch)
      {
      case 1:
        printf("Nhap so ban muon push:");scanf("%d",&i);
        push(&n,i);push(&s,1);
        break;
      case 2:
        push(&n1,pop(&n));push(&s,0);
        break;
      case 3:
        view(n);
        break;
      case 4:
        i=pop(&s);
        if(i==0)
          push(&n,pop(&n1));
        else
          pop(&n);
        break;
      case 5:break;
      }
  }while(ch!=5);
  return 0;
}
