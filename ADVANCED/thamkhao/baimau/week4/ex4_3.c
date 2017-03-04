#include<stdio.h>
#include<time.h>
enum{MAX=80};
void block(FILE *f1,FILE *f2)
{
  int num;
  char buff[MAX+1];
  do
    {num=fread(buff,sizeof(char),MAX,f1);
      buff[num*sizeof(char)]='\0';
      fprintf(f2,"%s",buff);
    }while(num!=0);
}
void line(FILE *f1,FILE *f2)
{
  char buff[MAX+1];
  while(fgets(buff,MAX+1,f1)!=NULL)
    fputs(buff,f2);
}
void ch(FILE *f1,FILE *f2)
{
  char c;
  while((c=fgetc(f1))!=EOF)
    fputc(c,f2);
}
int main(int argc,char* argv[])
{
  FILE *f1,*f2;
  int chon,t;
  time_t t1,t2;
  if(argc!=3)
    {printf("Loi cu phap\n");exit(1);}
  else
    if((f1=fopen(argv[1],"r"))==NULL)
      {printf("Cant open file %s\n",argv[1]);exit(1);}
    else
      if((f2=fopen(argv[2],"w"))==NULL)
        {printf("Cant open file %s\n",argv[2]);exit(1);}
      else
        {
          do{
            printf("Chon:\n1.Copy theo block\n2.Copy theo dong\n3.Copy tung ki tu\n");
            scanf("%d",&chon);
            switch(chon)
              {
              case 1:time(&t1);block(f1,f2);time(&t2);
                t=t2-t1;printf("Time= %d\n",t);break;
              case 2:time(&t1);line(f1,f2);time(&t2);
                t=t2-t1;printf("Time= %d\n",t);break;
              case 3:time(&t1);ch(f1,f2);time(&t2);
                t=t2-t1;printf("Time= %d\n",t);break;
              }
          }while(chon!=0);
          fclose(f1); fclose(f2);
        }
  return 0;
}

