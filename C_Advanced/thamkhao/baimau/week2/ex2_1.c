/*Viet chuong trinh theo cong thuc tinh e^x test vs e^50
Cu phap: ./e <mu> <so lan lap>         			*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char* argv[3])
{
  int p,i;
  double x,sum=1.0,gt=1.0,lt=1.0;
  if(argc!=3) {printf("Cu phap: ./e <mu> <so lan lap>\n");exit(0);}
  else
    {
      if(strcmp(argv[1],"0")==0) {printf("E^0=0\n");exit(1);}
      p=atoi(argv[2]);
      if(p<=0) {printf("Error!\n");exit(0);}
      x=atof(argv[1]);
      for(i=1;i<=p;i++)
        {
          lt=lt*x;
          gt=gt*i;
          sum=sum+lt/gt;
        }
      printf("e mu %g = %g\n",x,sum);
    }
  return 0;
}


