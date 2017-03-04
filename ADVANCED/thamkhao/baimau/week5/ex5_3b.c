#include<stdio.h>
#include<stdlib.h>
enum{MAX=81};
void merge(FILE *f,FILE *f1,FILE *f2)
{
  char buff[MAX];
  while(fgets(buff,MAX,f1)!=NULL)
    {fputs(buff,f);printf("%s",buff);}
  while(fgets(buff,MAX,f2)!=NULL)
    {fputs(buff,f);printf("%s",buff);}
}
int main(int argc,char* argv[])
{
  FILE *f,*f1,*f2;
  if(argc!=4)
    {printf("Cu phap:%s <file1> <file2> <file hop>\n",argv[0]);exit(1);}
  else
    if((f1=fopen(argv[1],"r"))==NULL)
      {printf("Cant open file %s\n",argv[1]);exit(1);}
    else
      if((f2=fopen(argv[2],"r"))==NULL)
        {printf("Cant open file %s\n",argv[2]);exit(1);}
      else
        if((f=fopen(argv[3],"w"))==NULL)
          {printf("Cant open file %s\n",argv[4]);exit(1);}
        else
          {
            merge(f,f1,f2);
            fclose(f1);fclose(f2);
          }
  return 0;
}
