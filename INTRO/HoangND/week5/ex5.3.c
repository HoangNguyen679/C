/* Nguyen Duc Hoang - 9A */
// Date Create:9/3/2015
#include<stdio.h>
int main()
{
  int a,b,c,max,avg;
  printf("enter 3 integers:\n");
  printf("First number:");
  scanf("%d",&a);
  printf("Second number:");
  scanf("%d",&b);
  printf("Third number:");
  scanf("%d",&c);
  max=b>c ? (b>a?b:a) : (c>a?c:a);
  printf("The biggest number is %d \n",max);
  avg=max/3>10 ? (a+b) : (b-c);
  printf("%d\n",avg);
  return 0;
}


