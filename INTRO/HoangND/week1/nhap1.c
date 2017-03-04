#include<stdio.h>
int nhapdayso(int a[])
{
  int i,n;
  printf("nhap vao so phan tu cua day so\n");
  scanf("%d",&n);
  printf("nhap vao cac phan tu\n");
  for (i=0;i<n;i++)
    {
      printf("nhap vao phan tu thu %d\n",i+1);
      scanf("%d",&a[i]);
    }
  return n;
}
int main()
{
  int a[10];
  nhapdayso(a);
  return 0;
}
