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
void bubble_sort(element list[], int n)
{
  int i,j;
  for(i = n; i>0; i--)
    for(j=0; i<i; j++ )
      if(list[j+1].key > list[j].key)
        SWAP(&list[j+1],&list[j]);
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
  t1=clock();
  bubble_sort(a,n);
  t2 = clock();
  printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
}
