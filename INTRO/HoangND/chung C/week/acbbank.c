/* Nguyen Duc Hoang - 9A */
// Date Create:29/3/2015
#include<stdio.h>
int main()
{
	char na[20];
	int a,i,a0;
	float f;
	printf("Nhap vao ten khach hang: ");
	gets(na);
	printf("Nhap vao so tien gui: ");
	scanf("%d",&a);a0=a;
	printf("Nhap vao lai suat (%%) : ");
	scanf("%f",&f);
    printf("Tai khoan khach hang: %s\n",na);
	printf("Thang\tTien dau ki\t\tTien lai\tSodu\t\n");
	for(i=1;i<=12;i++)
	{
		printf("%-5d\t%-15d\t%-10.0f\t%.0f\t\n",i,a,a*f/100,a+a*f/100);
		a=a+a*f/100;
	}
    printf("Tong lai la: %.0f\n",a-a0);
	return 0;

}
