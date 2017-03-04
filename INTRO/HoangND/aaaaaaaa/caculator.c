//Nguyen Duc Hoang
//Date created:10/4/15
/*Make caculator */
#include<stdio.h>
main()
{
  float n,s;
  char c;
  for(;;){
    printf("MENU\n");
    printf("N. Enter number\n");
    printf("S. Sin X\n");
    printf("C. Square root\n");
    printf("E. E ^ X\n");
    printf("T. Exit\n");
    printf("\n");
    printf("Enter your choose: ");
    scanf("%c",&c);
    if (c=='T') break;
    if (c=='N'){{
      do {
	printf("Enter a number: ");
	scanf("%f",&n);getchar();
	if (n<0) printf("Enter again (n>0): ");
      }
      while (n<0);
      do {
	printf("Enter measurement error: ");
	scanf("%f",&s);getchar();
	if (s<0||s>0.1) printf("Enter again\n");
      }
      while (s<0||s>0.1);
    }
       printf("MENU\n");
    printf("N. Enter number\n");
    printf("S. Sin X\n");
    printf("C. Square root\n");
    printf("E. E ^ X\n");
    printf("T. Exit\n");
    printf("\n");
    printf("Enter your choose: ");
    scanf("%c",&c);
    if (c=='T') break;
    if (c=='C'){
      float x0,x;
      x=n;
      for(;;) {
        x0=x;
        x = (x+n/x)/2;
        if ((x0-x)<s) break;
      }
      printf("Square root of %g is: %g\n",n,x);
      continue;
   }
   if (c=='E'){
      float e=1,e0,ni;
      int i=0,j;
      for(;;) {
        ++i;
        for(j=1;j<=i;j++) ni=n/j;
        e0=e;
        e+=ni;
        if ((e-e0)<s) break;
      }
      printf("E ^ %g is %g",n,e);
      continue;
   }
   if (c=='S'){
      int i=1,j=1,k;//j la bien danh dau;i,k la bien chay
      float sin,n0;
      sin=n;
      for(;;) {
        i=i+2;
        j=-j;
        for(k=1;k<=i;k++) n0=n/k;
        sin=sin+j*n0;
      }
      printf("SIN %g = %g",n,sin);
      continue;
   }
    }
  }
}
