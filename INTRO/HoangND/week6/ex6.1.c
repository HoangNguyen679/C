/* Nguyen Duc Hoang - 9A */
// Date Create: 15/3/2015
#include<stdio.h>
int main()
{
  char a,b,c,f;
  printf("Enter 3 characters:");
  a=getchar();
  b=getchar();
  c=getchar();
  f=a;
  if (f>b) f=b;
  if (f>c) f=c;
  printf("The first character is %c\n",f);
  return 0;
}
