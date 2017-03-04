/*Yeu cau:
Viet 1 ham so sanh 2 mang (=1 giong nhau,=-1 nguoc nhau,=0 khac nhau)
Khong su dung kichthuoc mang trong lenh goi ham*/
#include<stdio.h>
int ss(int a[],int b[],int mark)
{
  int i,n=0,m=0;
  for(i=0;a[i]!=mark;i++)
    n++;
  for(i=0;b[i]!=mark;i++)
    m++;
  if (m!=n) return 0;
  for(i=0;a[i]!=mark;i++)
    if(a[i]!=b[i]) break;
  if(a[i]==b[i]) return 1;
  for(i=0;i<n-1;i++)
    if(a[i]!=b[n-i-1]) break;
  if(i==n-1) return -1;
  else return 0;
}
int main()
{
  int a[100],b[100];
  int i=0;
  printf("Nhap vao hai mang so nguyen (ket thuk nhap bang cach nhap 0\n");
  do{
    printf("A[%d]:",i+1);
    scanf("%d",&a[i]);i++;
  }while(a[i-1]!=0);
  i=0;
  do{
    printf("B[%d]:",i+1);
    scanf("%d",&b[i]);
    i++;
  }while(b[i-1]!=0);
    switch(ss(a,b,0))
      {case 1: printf("Hai mang giong nhau\n");break;
      case -1: printf("Hai mang nguoc nhau\n");break;
      case 0: printf("Hai mang khac nhau don thuan\n");break;
      }
  return 0;
}
