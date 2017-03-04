#include<stdio.h>
#include<string.h>
#define SIZE 30
void frac(double n,int *nguyen, double *thuc){
  *nguyen=(int)n;
  *thuc=n-(int)n;
}
int main() {
  double n,thuc;
  int nguyen;
  printf("Nhap vao so thuc: ");scanf("%f",&n);
  frac(n,&nguyen,&thuc);
  printf("Phan nguyen la: %d\n",nguyen);
  printf("Phan nguyen la: %g\n",thuc);
}
