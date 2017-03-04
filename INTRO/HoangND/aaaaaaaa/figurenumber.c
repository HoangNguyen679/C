#include<stdio.h>
void figurenum(int n)
{
	int t,i=1;
	t=n;
	if (t==0) printf("Hen gap lai ^^\n");
	else {
	if (t%2==0) {
		while (t>0) {
				t/=10;
				if (t%2!=0) {
					i=0;
					break;
				}
		}
	}
	if (t%2!=0) {
		while (t>0) {
				if (t%2==0) {
					i=0;
					break;
				}
				t/=10;
		} 	
	}
	if (i==1) printf("Thoa man!\n\n");
	else printf("Khong thoa man!\n\n");	
	}
}
int main()
{
	int n;
	printf("\n\n");
	do {
		printf("( Nhap 0 de thoat ) \n");
		printf("Nhap n: ");scanf("%d",&n);
		figurenum(n);
	}
	while (n!=0);
	return 0;
}