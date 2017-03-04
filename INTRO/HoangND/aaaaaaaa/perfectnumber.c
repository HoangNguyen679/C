#include<stdio.h>
int main()
{
	int n,i,j,s=0;
	do {
	printf("Enter a number: ");
	scanf("%d",&n);
	if (n<=0) printf("Enter again:\n"); }
	while (n<=0);
	printf("All perfect number smaller than %d is:\n",n);
	for (i = 1; i < n; i++)
	{
		for (j = 1; j < i; j++)
			{
				if (i % j == 0) s+=j;
				if (i==s) printf("%d\n",i);
			}	s==0;
	}
	return 0;
}