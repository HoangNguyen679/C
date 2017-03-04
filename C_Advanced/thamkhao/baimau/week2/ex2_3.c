/*Viet chuong trinh mycopy de  copy noi dung cua file1 sang file2
cu phap: ./mycopy <file1> <file2>				*/
#include<stdio.h>
enum {SUCCESS,FAIL};
void mcopy(FILE *f1,FILE *f2)
{
  char ch;
  while((ch=fgetc(f1))!=EOF)
    {fputc(ch,f2);printf("%c",ch);}
}
int main(int argc,char* argv[3])
{
  FILE *f1,*f2;
  int re=SUCCESS;
  if(argc!=3)
    {printf("cu phap: ./mycopy <file1> <file2>\n");
      re=FAIL;
    }
  else
    {
      if((f1=fopen(argv[1],"r"))==NULL)
        {printf("Cant open file %s\n",argv[1]);
          re=FAIL;
        }
      else
        if((f2=fopen(argv[2],"w"))==NULL)
          {printf("Cant open file %s\n",argv[2]);
            re=FAIL;
          }
        else
          {mcopy(f1,f2);
            fclose(f2);fclose(f1);}
    }
  return 0;
}

