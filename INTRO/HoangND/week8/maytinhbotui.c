//Nguyen Duc Hoang
//Date created:10/4/15
/*Lam may tinh don gian*/
#include<stdio.h>
int main()
{
  float n,s;
  char c;
  do {
    printf("MENU\n");
    printf("N. Nhap so va sai so\n");
    printf("S. Sin X\n");
    printf("C. Tinh can bac 2\n");
    printf("E. Tinh e mu x\n");
    printf("T. Thoat\n");
    printf("\n");
    printf("Nhap vao lua chon: ");
    scanf("%c",&c);getchar();
    switch (c) {
      case 'N':   do {
      	               printf("Nhap vao mot so duong: ");
	                     scanf("%f",&n);getchar();
	                     if (n<0) printf("Nhap lai (n>0): ");
                      }
                  while (n<0);
                  do {
	                     printf("Nhap vao sai so: ");
	                     scanf("%f",&s);getchar();
	                     if (s<0||s>0.1) printf("Nhap lai\n");
                      }
                  while (s<0||s>0.1);break;
      case 'C':   {float x0,x;
                  x=n;
                  for(;;) {
                            x0=x;
                            x = (x+n/x)/2;
                            if ((x0-x)<s) break;
                          }
                  printf("Can bac hai cua %g is: %g\n\n",n,x);}
                  break;
      case 'E':   {float e=1,y=1;
                  int i;
                  i=1;
                  do {
                        y*=n/i;
                        e=e+y;
                        i++;
                      }
                  while (y>s);
                  printf("e^%g = %g\n\n",n,e);}
                  break;
      case 'S':
                {int i=1,j=1;
                float sin,n0,t;
                sin=t=n;
                do {
                i=i+2;
                j=-j;
                t*=n*n/(i*(i-1));
                sin+=j*t;
                   }
                while (t>s);
                printf("sin %g = %g\n\n",n,sin);}
                break;
   }
  }
  while (c!='T');
  return 0;
}