#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define max 500000

int a[max];
int i;

int search(int a[],int n,int x)
{
	for(i = 0; i < n; i++)
		if(a[i] == x) return i;
	return -1;
}

int senitelSearch(int a[],int n,int x)
{
	a[n]=x;
	for(i = 0;  ; i++)
		if(a[i] == x) return i;
	return -1;
}

int binarySearch(int a[],int low,int high,int x)
{
  if (low >  high) return -1;
  int mid;
  mid = (low + high)/2;
  if(a[mid] < x) return binarySearch(a,mid+1,high,x);
  else if(a[mid] > x) return binarySearch(a,low,mid-1,x);
  else return mid;
  return -1;
}

int main()
{

  clock_t begin,end;
  int ch,n,x,kq;
  double t;
  printf("\n\nNhap du lieu vao\n");
  printf("Nhap so phan tu cua mang: ");scanf("%d",&n);
  for(i = 0; i<n; i++) a[i] = 2*i;
  printf("Nhap so can tim kiem: ");scanf("%d",&x);
  printf("\n\n");
  {
            begin = clock();
            kq = search(a,n,x);
            end = clock();
            t = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Gia tri tra ve: %d\n",kq);
            printf("Thoi gian tinh: %f\n\n",t);
  }
  {
    begin = clock();
    kq = senitelSearch(a,n,x);
    end = clock();
    t = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Gia tri tra ve: %d\n",kq);
    printf("Thoi gian tinh: %f\n\n",t);
  }
  {
    begin = clock();
    kq = binarySearch(a,0,n-1,x);
    end = clock();
    t = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Gia tri tra ve: %d\n",kq);
    printf("Thoi gian tinh: %f\n\n",t);
  }
  /*
  do
    {
      printf("\n\nMENU\n\n");
      printf("1. Tim kiem tuan tu\n");
      printf("2. Tim kiem linh gac\n");
      printf("3. Tim kiem nhi phan\n");
      printf("4. Thoat\n\n");
      printf("Please select: ");
      scanf("%d",&ch);
      switch(ch)
        {
        case 1:
          {
            begin = clock();
            kq = search(a,n,x);
            end = clock();
            t = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Gia tri tra ve: %d\n",kq);
            printf("Thoi gian tinh: %f",t);
          }break;
        case 2:
          {
            begin = clock();
            kq = senitelSearch(a,n,x);
            end = clock();
            t = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Gia tri tra ve: %d\n",kq);
            printf("Thoi gian tinh: %f",t);
          }break;
        case 3:
          {
            begin = clock();
            kq = binarySearch(a,0,n-1,x);
            end = clock();
            t = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("Gia tri tra ve: %d\n",kq);
            printf("Thoi gian tinh: %f",t);
          }break;
        case 4: return;
        default: printf("Wrong choice\n");
        }
    }
  while(1);
  */
}
