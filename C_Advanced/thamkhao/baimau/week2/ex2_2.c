/*Viet chuong trinh giai phuong trinh bac 2
cu phap: ./gpt <a> <b> <c>		   */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//Giai pt bac 2
int main(int argc,char* argv[4])
{
  float a,b,c,d;
  if(argc!=4) printf("cu phap: ./gpt <a> <b> <c>\n");
  else
    {
      a=atof(argv[1]);
      b=atof(argv[2]);
      c=atof(argv[3]);
      if(a==0)
        {if(b!=0) printf("Nghiem x= %g\n",-c/b);
        else
          if(c==0) printf("Vo so nghiem\n");
          else printf("Vo nghiem\n");}
      else
        {d=b*b-4*a*c;
          printf("Delta=%g\n",d);
          if(d==0) printf("Phuong trinh co nghiem duy nhat: x=%g\n",-b/(2*a));
          else if(d<0) printf("Phuong trinh vo nghiem\n");
          else if(d>0)
            {
              printf("Phuong trinh co 2 nghiem phan biet:\n");
              printf("x1= %g\n",(-sqrt(d)-b)/(2*a));
              printf("x2= %g\n",(sqrt(d)-b)/(2*a));
            }
        }
    }
  return 0;
}


