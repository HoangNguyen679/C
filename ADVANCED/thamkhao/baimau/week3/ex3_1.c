#include<stdio.h>
#include<ctype.h>
#include<string.h>
enum{SUCCESS,FAIL};
void mahoa(FILE *f1,FILE *f2,int sp)
{
  char ch;
  while((ch=fgetc(f1))!=EOF)
    {if (isalpha(ch)||isdigit(ch)) ch=ch+sp;
      fputc(ch,f2);
    }
}
void cp(FILE *f1,FILE *f2)
{
  char ch;
  while((ch=fgetc(f1))!=EOF)
    {fputc(ch,f2);printf("%c",ch);}
}
int main(int argc,char* argv[])
{
  FILE *f1,*f2;
  char bansao[]="ac.dc";
  int re=SUCCESS,space;
  if((argc!=3)&&(argc!=4||strcmp(argv[3],"-d")!=0))
    { printf("Cu phap:%s <file_ma_hoa> <do_lech> de ma hoa\nCu phap:%s <file_can giai_ma> <do_lech> -d de giai ma\n",argv[0],argv[0]);
      re=FAIL;}
  else
    { if((f1=fopen(argv[1],"r"))==NULL)
        {printf("Cant open file %s\n",argv[1]);re=FAIL;}
      else
        {if((f2=fopen(bansao,"w"))==NULL)
            {printf("Cant open file %s\n",bansao);re=FAIL;}
          else
            {
              space=atoi(argv[2]);
              if(argc==4) space=-space;
              mahoa(f1,f2,space);
              fclose(f2);fclose(f1);
            }
        }
      if((f2=fopen(bansao,"r"))==NULL)
        {printf("Cant open file %s\n",bansao);re=FAIL;}
      else
        if((f1=fopen(argv[1],"w"))==NULL)
          {printf("Cant open file %s\n",argv[1]);re=FAIL;}
        else
          {
            cp(f2,f1);
            fclose(f2);fclose(f1);
          }
    }
  return 0;
}
