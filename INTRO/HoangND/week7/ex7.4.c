/* Nguyen Duc Hoang - 9A */
// Date Create: 25/03/2015
#include<stdio.h>
#include<math.h>
main()
{
  int n,i,k=0;
  printf("Nhung so nguyen to nho hon 100 la:\n");
  printf("%d\n%d\n",2,3);
  for (n=5;n<=100;n++)
    {
      for (i=2;i<=sqrt(n);i++)
	{
	  if (n%i==0) {k++;break;}
	}
      if (k==0) printf("%d\n",n);k=0;
    } 

}
