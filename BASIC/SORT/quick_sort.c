#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAX 2000000
typedef struct
{
  int key;
}elementtype;
void SWAP(elementtype *list1,elementtype *list2)
{
  elementtype temp=*list1;
  *list1 = *list2;
  *list2 = temp;
}
void quick_sort(elementtype list[], int left, int right)
{
  int pivot,i,j;///pivot la phan tu chot
  if(left < right)
    {
      i = left;
      j = right + 1;
      pivot = list[left].key;
      do
        {
          do i++;while(list[i].key < pivot);
          do j--;while(list[j].key > pivot);
          if(i<j) SWAP(&list[i],&list[j]);
        }
      while(i<j);
      SWAP(&list[left],&list[j]);
      quick_sort(list,left,j-1);
      quick_sort(list,j+1,right);
    }
}
int main()
{
  clock_t t1,t2;
  elementtype list[MAX];
  srand((unsigned)time(NULL));
  int i,a,n;
  printf("Kich thuoc mang = ");scanf("%d",&n);
  for(i=0; i<n; i++)
    list[i].key = rand() % n + 1;
   for(i=0; i<n; i++)
   printf("%d\t",list[i].key);
  printf("\n\n");
  t1=clock();
  quick_sort(list,0,n-1);
  t2=clock();
   for(i=0; i<n; i++)
   printf("%d\t",list[i].key);
  printf("\n\n");
  printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
  printf("\n\n");
  return 0;
}
