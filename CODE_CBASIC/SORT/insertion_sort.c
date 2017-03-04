#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct {
  long key;
}element;
void SWAP(element *a,element *b)
{
  element  temp = *a;
  *a=*b;
  *b=temp;
}
void insertion_sort(element list[], int n)
{
  int i,j;
  element next;
  for(i=1; i<n; i++)
    {
      next = list[i];
      for(j=i-1; j>=0 && next.key < list[j].key; j--)
        list[j+1] = list[j];
      list[j+1] = next;
    }
}
main()
{
  int i,k;
  long n;
  element *a;
  clock_t t1,t2;
  printf("kich thuoc mang = ");scanf("%ld",&n);
  a=(element*)malloc(n*sizeof(element));
  srand ((unsigned)time(NULL));
  for(i=0; i<n; i++)
    {
      a[i].key = rand () % n + 1;
    }
  for(i=0;i<n;i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");
  t1=clock();
  insertion_sort(a,n);
  t2 = clock();
  for(i=0;i<n;i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");
  printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
}
