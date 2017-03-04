#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 80
typedef int add;
typedef struct so
{add data[MAX];int top;}so;
void init(so *n)
{n->top=0;}
void push(so *n,add data)
{
  if(n->top<MAX-1)
    {n->data[n->top]=data;n->top++;}
  else printf("Stack over\n");
}
add pop(so *n)
{
  if(n->top==0) printf("Stack is empty\n");
  else {n->top--;return (n->data[n->top]);}
}
int solve(int s1,int s2,char symbol)
{
  switch (symbol)
    {
    case '+':return(s1+s2);
    case '-':return(s1-s2);
    case '*':return(s1*s2);
    }
}
int main()
{
  so t_hang;
  char str[MAX];
  int i,n;
  init(&t_hang);
  printf("Nhap vao bieu thu hau to:(khong chua dau cach) ");
  scanf("%s",str);
  for(i=0;str[i]!='\0';i++)
    if(isdigit(str[i])) push(&t_hang,str[i]-'0');
    else
      push(&t_hang,solve(pop(&t_hang),pop(&t_hang),str[i]));
  printf("Ket qua=%d\n",t_hang.data[t_hang.top-1]);
  return 1;
}


