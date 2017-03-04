#include<stdio.h>
#include<string.h>
enum{MAX=80,Page=30};
void cat(FILE *f,int thamso)
{
  char buff[MAX+1],ch;
  long num=0,kt=1,dem=0;
  while(kt)
    {
      num=fread(buff,sizeof(char),MAX,f);
      if(num==0) {kt=0;break;}
      else
        {buff[num*sizeof(char)]='\0';
          printf("%s",buff);
          dem=(dem+1);
          if(dem%Page==0&&thamso==1) {printf("\nPress anykey to continue\n");getchar();}
        }
    }
}
int main(int argc,char *argv[])
{
  FILE *f;
  int thamso=0;
  if(argc!=2&&(argc!=3||(argc==3&&strcmp("-p",argv[1])!=0)))
      { printf("Cu phap:%s <tham_so_dk> <file>\n",argv[0]);
        exit(1);
        }
  else
    {
      if(argc==3) {thamso=1;f=fopen(argv[2],"r");}
      else f=fopen(argv[1],"r");
      if(f==NULL)
        {printf("Cant open file \n");
          exit(1);
        }
      else
        {cat(f,thamso);
          fclose(f);
        }
    }
  return 0;
}
