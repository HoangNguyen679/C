#include<stdio.h>
#include<math.h>
#define MAX 10
int main() {
  int mang[MAX],i,n,j;
  double average=0,did;
  printf("Nhap so phan tu cua mang: ");scanf("%d",&n);
  printf("Nhap mang a[]\n");
  for(i=0;i<n;i++){
    printf("Nhap phan tu a[%d]: ",i);scanf("%d",&mang[i]);
    average += mang[i];
  }
  average /= n;
  did = fabs(mang[0]-average);
  for(i=1;i<n;i++)
    if (fabs(mang[i]-average) < did ) {
      did = fabs(mang[i]-average);
      j=i;
    }
  printf("So trung vi la %d \n",mang[j]);
}

