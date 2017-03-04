#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
  FILE *f;
  char file[]="text.txt";
  int i,num;
  long dem=0,so;
  srand(time(NULL));
  printf("Nhap vao so dong");
  scanf("%ld",&so);
  if((f=fopen(file,"w"))==NULL)
    {printf("cant onen file %s to write\n",file);
      exit(1);
    }
  else
    do
      {
        for(i=0;i<80;i++)
          {num=rand()%(127-' ');
            char ch=num+' ';
            fputc(ch,f);}
        dem++;fputc('\n',f);
      }while(dem!=so);
  return 0;
}
