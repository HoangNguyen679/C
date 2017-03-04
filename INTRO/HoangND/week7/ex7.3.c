/* Nguyen Duc Hoang - 9A */
// Date Create: 25/03/2015
#include<stdio.h>
main()
{
  int i,j,k,n;
  printf("Nhap n: ");
  scanf("%d",&n);
  printf("Nhung so lon hon %d la :\n",n);
  for ( i=1;  i<=100; i++)
    { if (i>n && (i%2 !=0)) printf("%d\n",i); }
}
