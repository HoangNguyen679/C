#include<stdio.h>
typedef int add;
int compare(add data1,add data2);
void insertSort(add mang[],int n)
{
  int i,j;
  add m;
  for(i=1;i<n;i++)
    {
      j=i-1;
      m=mang[i];
      while(j>=0&&compare(mang[j],m)==1)
        {
          mang[j+1]=mang[j];
          j--;
        }
      mang[j+1]=m;
    }
}
void selectSort(add a[],int n)
{
  int i,j,min;
  add tmp;
  for(i=0;i<n;i++)
    {
      min=i;
      for(j=i+1;j<n;j++) if(compare(a[j],a[min])==-1) min=j;
      if(compare(a[j],a[min])!=0)
        {tmp=a[i];a[i]=a[min];a[min]=tmp;}
    }
}
void adjust(add list[], int root, int n)
{
  int child, rootkey; int temp;
  rootkey=list[root-1];
  child=2*root;
  while (child <= n) {
    if ((child < n) && (compare(list[child-1],list[child])==-1))
      child++;
    if (compare(rootkey,list[child-1])>=0) break;
    else {
      list[child/2-1] = list[child-1];
      child *= 2;
    }
  }
  list[child/2-1] = rootkey;
}
void SWAP(int *a,int *b)
{
  int t=*a;
  *a=*b;*b=t;
}
void heapSort(int list[], int n)
{
  int i, j;
  int temp,t;
  for (i=n/2; i>0; i--) adjust(list, i, n);
  for (i=n-1; i>0; i--)
    {
      SWAP(&list[0], &list[i]);
      adjust(list, 1, i);
    }
}
