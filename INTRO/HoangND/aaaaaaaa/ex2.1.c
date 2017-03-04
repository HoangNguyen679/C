#include<stdio.h>
double dongnang(double a, double b);
int main()
{
  float m,v;
  printf("Nhap vao khoi luong: ");
  scanf("%f",&m);
  printf("Nhap vao van toc: ");
  scanf("%f",&v);
  printf("Dong nang cua vat la: %g (J)\n",dongnang(m,v));
  return 0;
}
double dongnang(double a, double b)
{
  return a*b*b/2;
}
