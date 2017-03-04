#include<stdio.h>
main()
{
	float a1,a2,a3,a4,a5,max,min,tb;
	printf("Nhap diem cua tung giam khao\n");
	printf("Giam khao 1: ");scanf("%f",&a1);
	printf("Giam khao 2: ");scanf("%f",&a2);
	printf("Giam khao 3: ");scanf("%f",&a3);
	printf("Giam khao 4: ");scanf("%f",&a4);
	printf("Giam khao 5: ");scanf("%f",&a5);
	max=a1>a2?(a1>a3?(a1>a4?(a1>a5?a1:a5):(a4>a5?a4:a5)):(a3>a4?(a3>a5?a3:a5):(a4>a5?a4:a5))):(a2>a3?(a2>a4?(a2>a5?a2:a5):(a4>a5?a4:a5)):(a3>a4?(a3>a5?a3:a5):(a4>a5?a4:a5)));
	min=a1<a2?(a1<a3?(a1<a4?(a1<a5?a1:a5):(a4<a5?a4:a5)):(a3<a4?(a3<a5?a3:a5):(a4<a5?a4:a5))):(a2<a3?(a2<a4?(a2<a5?a2:a5):(a4<a5?a4:a5)):(a3<a4?(a3<a5?a3:a5):(a4<a5?a4:a5)));
	tb=(a1+a2+a3+a4+a5-max-min)/3;
	printf("Diem trung binh cua thi sinh la: %.1f \n",tb);
}