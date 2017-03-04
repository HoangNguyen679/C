#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define MAX 8
typedef struct
{
  int key;
}elementtype;
void merge(elementtype list[],int first, int mid, int last)
{
  elementtype temp[MAX];
  int first1 = first, last1 = mid;
  int first2 = mid +1, last2 = last;
  int index = first;
  for(; (first1 <= last1) && (first2 <= last2); ++index)
    {
      if(list[first1].key < list[first2].key)
        {
          temp[index].key = list[first1].key;
          ++first1;
         }
      else
        {
          temp[index].key = list[first2].key;
          ++first2;
        }
    }
  for(;first1<=last1;++first1,++index)
    temp[index].key = list[first1].key;
  for(;first2<=last2;++first2,++index)
    temp[index].key = list[first2].key;
  for(index = first; index <=last; ++index)
    list[index].key = temp[index].key;
}
void merge_sort(elementtype list[],int first, int last)
{
  if(first<last)
    {
      int mid = (first + last)/2;
      merge_sort(list,first,mid);
      merge_sort(list,mid+1,last);
      merge(list,first,mid,last);
    }
}
int main()
{
  elementtype list[MAX];
  int i;
  clock_t t1,t2;
  srand(time(NULL));
  for(i=0; i<MAX; i++)
    list[i].key = rand() % MAX + 1;
   for(i=0; i<MAX; i++)
   printf("%d\t",list[i].key);
  printf("\n\n");
  t1=clock();
  merge_sort(list,0,MAX-1);
  t2=clock();
  for(i=0; i<MAX; i++)
   printf("%d\t",list[i].key);
  printf("\n\n");
  printf("%lf",(double)(t2-t1)/CLOCKS_PER_SEC);
  printf("\n\n");
  return 0;
}
