#include<stdio.h>
void reverseInt(int *a)
{
	int s=0,t;
	t=*a;
	while (t>0) {
		s=s*10+t%10;
		t/=10;
	}
	*a=s;
}
int main(void)
{
	int a;
	do {
		printf("Nhap a: ");scanf("%d",&a);
		reverseInt(&a);
		printf("%d\n",a);
	}
	while (a!=0);
	return 0;
}
