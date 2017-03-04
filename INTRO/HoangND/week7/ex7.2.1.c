/* Nguyen Duc Hoang - 9A */
// Date Create: 25/03/2015
#include<stdio.h>
main()
{
  int i,j,n;
  printf("Nhap n: ");
  scanf("%d",&n);
  for ( i=1;  i<=n; i++)
    {
      for (j=1;j<=i;j++)
	printf("*");printf("\n");
    }
}
