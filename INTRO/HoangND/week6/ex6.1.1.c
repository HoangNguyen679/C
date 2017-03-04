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
  if ((64<a)&&(a<91))
    {
      a=a+32;
      if ((64<b)&&(b<91)) b=b+32;
      if (a>b) f=b;
      if ((64<c)&&(c<91)) c=c+32;
      if (f>c) f=c;
    }
  else 
    {
      if ((64<b)&&(b<91)) b=b+32;
      if (a>b) f=b;
      if ((64<c)&&(c<91)) c=c+32;
      if (f>c) f=c;
    }
  printf("The first character is %c\n",f);
  return 0;
}
