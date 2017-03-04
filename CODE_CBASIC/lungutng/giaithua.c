/* Nguyen Duc Hoang - 9A */
// Date Create:
#include<stdio.h>

int tgt(int n)
{
	if (n <= 1) return 1;
	else
		return n*tgt(n-1);
}
int main()
{
	int n,b;
	scanf("%d",&n);
	b = tgt(n);
	printf("%d\n",b);
	return 0;
}
