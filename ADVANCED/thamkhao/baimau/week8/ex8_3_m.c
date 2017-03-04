#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 80
typedef int add;
typedef struct so
{add data[MAX];int top;}so;
char dau[]=")+-*(";
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
  if(n->top==0) {printf("Stack is empty\n");}
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
int cmp(char s1,char s2)
{
  if(s1=='(') return 0;
  if(s2==')') return 1;
  if(s2==s1) return 1;
  else if(s2==dau[3]) return 0;
  else return 1;
}
void calc(so *t_tu,so *t_hang,char s)
{
  char ch;
  so dem;
  init(&dem);
  if(isdigit(s)) push(t_hang,s-'0');
    else
      if(t_tu->top==0||s=='(') push(t_tu,s);
      else
        {
          if(cmp(t_tu->data[t_tu->top-1],s)==1)
            while(t_tu->top!=0&&t_tu->data[t_tu->top-1]!='(')
              {
                ch=pop(t_tu);
                push(t_hang,solve(pop(t_hang),pop(t_hang),ch));
              }
          if(s==')') pop(t_tu);
          else push(t_tu,s);
        }
}
int main()
{
  so t_hang,t_tu;
  char str[MAX],ch;
  int i,n;
  init(&t_hang);init(&t_tu);
  printf("Nhap vao bieu thu trung to:(khong chua dau cach) ");
  scanf("%s",str);
  for(i=0;str[i]!='\0';i++)
    calc(&t_tu,&t_hang,str[i]);
  while(t_tu.top!=0)
    {
      ch=pop(&t_tu);
      push(&t_hang,solve(pop(&t_hang),pop(&t_hang),ch));
    }
  push(&t_tu,str[i]);
  printf("Ket qua=%d\n",t_hang.data[t_hang.top-1]);
  return 1;
}


