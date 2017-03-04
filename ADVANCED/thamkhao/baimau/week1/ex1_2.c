#include<stdio.h>
int check(char ch)
{
  if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')) return 1;
  return 0;
}
int main()
{
  char str[100];
  int i=0;
  printf("Nhap vao 1 cau:");
  scanf("%[^'\n']",str);
  while(str[i]!='\0')
    {
      while(check(str[i])&&str[i]!='\0')
        {printf("%c",str[i]);i++;}
      while(!check(str[i])&&str[i]!='\0')
        i++;
      printf("\n");
    }
  return 0;
}
