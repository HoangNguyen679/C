#include<stdio.h>
#include<stdlib.h>
enum{MAX=81};
void split(FILE *f,FILE *f1,FILE *f2,int x)
{
  char buff[MAX];
  int dem=0;
  while((fgets(buff,MAX,f)!=NULL)&&(dem!=x))
    {fputs(buff,f1);dem++;}
  if(dem<x) {printf("Loi:So dong vuot qua\n");exit(1);}
  do{
    fputs(buff,f2);
  }while(fgets(buff,MAX,f)!=NULL);
}
int main(int argc,char* argv[])
{
  FILE *f,*f1,*f2;
  if(argc!=5)
    {printf("Cu phap:%s <file tach> <so dong file1> <file1> <file2>\n",argv[0]);exit(1);}
  else
    if((f=fopen(argv[1],"r"))==NULL)
      {printf("Cant open file %s\n",argv[1]);exit(1);}
    else
      if((f1=fopen(argv[3],"w"))==NULL)
        {printf("Cant open file %s\n",argv[3]);exit(1);}
      else
        if((f2=fopen(argv[4],"w"))==NULL)
          {printf("Cant open file %s\n",argv[4]);exit(1);}
        else
          {int x=atoi(argv[2]);
            split(f,f1,f2,x);
            fclose(f1);fclose(f2);
          }
  return 0;
}
