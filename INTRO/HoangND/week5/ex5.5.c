/* Nguyen Duc Hoang - 9A */
// Date Create:11/3/2015
#include<stdio.h>
int main()
{
  int n,max;
  printf("Enter the student:");
  scanf("%d",&n);
  printf("The number of students in the smallest class is %d\n",n/7);
  max=((n%7)==0)?(n/7):(n/7+1);
  printf("The number of students in the largest class is %d\n",max);
  return 0;
}


