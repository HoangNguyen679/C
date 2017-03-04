#include<stdio.h>
#include"element.h"
//==========================================================
int cmp(elementtype data1,elementtype data2);
void SWAP(elementtype *a,elementtype *b);
void adjust(elementtype list[],int root,int n);
void quick(elementtype list[],int left,int right);
void show(elementtype list[],int n);
void insertSort(elementtype list[],int n);
void selectSort(elementtype list[],int n);
void heapSort(elementtype list[],int n);
void quickSort(elementtype list[],int n);
//==========================================================
//Insert Sort ==============================================
void insertSort(elementtype list[],int n)
{
  int i,j;
  elementtype m;
  for(i=1;i<n;i++)
    {
      j=i-1;
      m=list[i];
      while(j>=0&&cmp(list[j],m)==1)
        {
          list[j+1]=list[j];
          j--;
        }
      list[j+1]=m;
    }
}
//Select Sort ==============================================
void selectSort(elementtype list[],int n)
{
  int i,j,min;
  elementtype tmp;
  for(i=0;i<n;i++)
    {
      min=i;
      for(j=i+1;j<n;j++) if(cmp(list[j],list[min])==-1) min=j;
      if(cmp(list[i],list[min])!=0)
        SWAP(&list[i],&list[min]);
    }
}
//Ajust ====================================================
void adjust(elementtype list[], int root, int n)
{
  int child;
  elementtype rootkey;
  rootkey=list[root-1];
  child=2*root;
  while (child <= n) {
    if ((child < n) && (cmp(list[child-1],list[child])==-1))
      child++;
    if (cmp(rootkey,list[child-1])>=0) break;
    else {
      list[child/2-1] = list[child-1];
      child *= 2;
    }
  }
  list[child/2-1] = rootkey;
}
//SWAP =====================================================
void SWAP(elementtype *a,elementtype *b)
{
  elementtype t=*a;
  *a=*b;*b=t;
}
//Heap Sort ================================================
void heapSort(elementtype list[], int n)
{
  int i;
  for (i=n/2; i>0; i--) adjust(list, i, n);
  for (i=n-1; i>0; i--)
    {
      SWAP(&list[0], &list[i]);
      adjust(list, 1, i);
    }
}
//Quick  ===================================================
void quick(elementtype list[],int left,int right)
{
  elementtype first=list[left];
  int i=left,j=right+1;
  if(left<right)
    {
      do
        {
          do i++; while(cmp(list[i],first)<0);
          do j--; while(cmp(list[j],first)>0);
          if(i<j) SWAP(&list[j],&list[i]);
        }while(i<j);
      SWAP(&list[left],&list[j]);
      quick(list,left,j-1);
      quick(list,j+1,right);
    }
}
//Quick Sort ===============================================
void quickSort(elementtype list[],int n)
{
  quick(list,0,n-1);
}
