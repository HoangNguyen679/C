/* Nguyen Duc Hoang - 9A */
// Date Create:29/3/2015
#include<stdio.h>
int main()
{
	char na[20];
	int a,i;
	float f;
	printf("Nhap vao ten khach hang: ");
	gets(na);
	printf("Nhap vao so tien gui: ");
	scanf("%d",&a);
	printf("Nhap vao lai suat (%%) : ");
	scanf("%f",&f);
	printf("Thang\tTien dau ki\t\tTien lai\tSodu\t\n");
	for(i=1;i<=12;i++)
	{
		printf("%d\t\t%d\t\t%.0f\t\t%.0f\t\n",i,a,a*f/100,a+a*f/100);
		a=a+a*f/100;
	}
	return 0;

}
