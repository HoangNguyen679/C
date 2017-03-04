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
void selection_sort(element list[],int n)
{
  int i,j,min;
  element tmp;
  for(i=0; i<n-1;i++)
    {
      min = i;
      for(j=i+1; j<n; j++)
        if(list[j].key < list[min].key) min = j;
      SWAP(&list[i],&list[min]);
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
  selection_sort(a,n);
  t2 = clock();
  for(i=0;i<n;i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");
  printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
}
