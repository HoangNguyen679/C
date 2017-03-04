#include<stdio.h>
#include<string.h>
char *substr(char *str,int offset,int number)
{
  int i;
  char *tmp;
  if(offset<=0||offset>strlen(str)||number<=0) return NULL;
  else
    if(offset+number-1>strlen(str)) return NULL;
    else
      {
        tmp=(char *)malloc(sizeof(char)*strlen(str-offset+number));
        strcpy(tmp,str+offset-1);
        *(tmp+number)='\0';
      }
  return tmp;
}
main()
{
  char str[100];
  int off,num;
  printf("Nhap vao xau s:");
  scanf("%[^'\n']",str);
  printf("Vi tri bat dau:");
  scanf("%d",&off);
  printf("So ki tu:");
  scanf("%d",&num);
  printf("Substr(%s,%d,%d):%s\n",str,off,num,substr(str,off,num));
  return 0;
}
