#include<stdio.h>
main()
{
  char ch;
  char s[15];
  printf("nhap mot ki tu : ");
  ch=getchar();getchar();
  printf("nhap xau ki tu :");
  gets(s);
  printf("ki tu la '%c' va xau la '%s'\n ",ch,s);
}
