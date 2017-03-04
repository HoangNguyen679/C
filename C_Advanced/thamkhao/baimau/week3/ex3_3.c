#include<stdio.h>
enum {SUCCESS,FAIL,MAX=80};
void pick(FILE *f1,FILE *f2,FILE *f3)
{
  char buff1[MAX],buff2[MAX];
  int k1=1,k2=1;
  while(k1||k2)
    {
      if (k1)
        if(fgets(buff1,MAX,f1)!=NULL)
          {
            printf("%s",buff1);
            fputs(buff1,f3);
          }
        else k1=0;
      if(k2)
        if(fgets(buff2,MAX,f2)!=NULL)
          {
            printf("%s",buff2);
            fputs(buff2,f3);
          }
        else k2=0;
    }
}
int main(int argc,char* argv[4])
{
  FILE *f1,*f2,*f3;;
  int re=SUCCESS;
  if(argc!=4)
    {printf("Cu phap:./%s <file1> <file2> <file3>\n",argv[0]);re=FAIL;}
  else
    {
      if((f1=fopen(argv[1],"r"))==NULL)
        {printf("Cant open file %s\n",argv[1]);re=FAIL;}
      else
        {if((f2=fopen(argv[2],"r"))==NULL)
            {printf("Cant open file %s\n",argv[2]);re=FAIL;}
          else
            {if((f3=fopen(argv[3],"w"))==NULL)
                {printf("Cant open file %s\n",argv[3]);re=FAIL;}
              else
                {pick(f1,f2,f3);
                  fclose(f3);
                }
              fclose(f2);
            }
          fclose(f1);
        }
    }
  return 0;
}
