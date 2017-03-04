/*Viet chuong trinh stasfile doc vao 1 file thong ke tan suat xuat hien cua 1 ki tu (khong phan biet hoa thuong) -> ghi ket qua vao 1 file  sourcestats.txt
cu phap : ./stasfile <ten file>					 */
#include<stdio.h>
enum {SUCCESS,FAIL,MAX=81};
int check(int ch)
{
  if(ch<='z'&&ch>='a') return 1;
  if(ch>='A'&&ch<='Z') return 1;
  else return 0;
}
void stats(FILE *f1,FILE *f2)
{
  int dem[26],i,k;
  char ch;
  for(i=0;i<26;i++) dem[i]=0;
  while((ch=fgetc(f1))!=EOF)
    {
      if(check(ch))  dem[(ch-'A')%32]++;
    }
  for(i=0;i<26;i++)
    if(dem[i]!=0)
      {fprintf(f2,"%c-%d\n",i+'a',dem[i]);
        printf("%c-%d\n",i+'a',dem[i]);}
}
int main(int argc,char* argv[2])
{
  FILE *f1,*f2;
  int re=SUCCESS;
  char result[]="/home/swallow/sourcestats.txt";
    if(argc!=2)
      {printf("./stats <file name>\n");re=FAIL;}
    else
      if((f1=fopen(argv[1],"r"))==NULL)
        {printf("Cant open file: %s\n",argv[1]);
          re=FAIL;
        }
      else
        if((f2=fopen(result,"w"))==NULL)
          {printf("Cant open file: %s\n",result);
            re=FAIL;
          }
        else
          {
            printf("start\n");
            stats(f1,f2);
            fclose(f1);
            fclose(f2);
          }
  return 0;
}
