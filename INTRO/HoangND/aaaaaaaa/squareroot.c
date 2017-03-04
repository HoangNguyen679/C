//Nguyen Duc Hoang
//Date created:10/4/15
/*Caculate squareroot by using newton method */
#include<stdio.h>
main()
{
  float n,x,s,x0;
  do {
    printf("Enter a number: ");
    scanf("%f",&n);
    if (n<0) printf("Enter again (n>0): ");
  }
  while (n<0);
  do {
    printf("Enter measurement error: ");
    scanf("%f",&s);
    if (s<0||s>0.1) printf("Enter again\n");
  }
  while (s<0||s>0.1);
  x=n;
  for(;;)
    {
      x0=x;
      x = (x+n/x)/2;
      if ((x0-x)<s) break;
    }
  printf("Square root of %g is: %g\n",n,x);
}

