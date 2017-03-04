/* Nguyen Duc Hoang - 9A */
// Date Create: 18/3/2015
#include<stdio.h>
int main()
{
	int n;
	printf("Enter the number of student:");
	scanf("%d",&n);
	printf("The number of students in the smallest class is:%d\n",n/7);
	printf("The number of students in the largest class is:%d\n",(n+6)/7);
	printf("The average number of students per class is:%g\n",n/7.0);
	printf("The number of classes of above average size is:%d\n",n%7);
	printf("The number of classes of at most average size is:%d\n",7-n%7);
	printf("The number of students in the classes of larger than average size is:%d\n",(n%7)*(n+6)/7);
	printf("The number of classes of exactly average size is:%d\n",!(n%7)*7);
	return 0;
}
