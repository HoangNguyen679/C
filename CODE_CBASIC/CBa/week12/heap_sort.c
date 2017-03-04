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
void adjust(element list[], int root, int n)
{
  int child;
  element rootkey;
  rootkey=list[root];
  while(root< n/2)
    {
      child = 2* root +1;
      if((child < n-1 ) && list[child].key < list[child+1].key) child ++;
      if (rootkey.key >= list[child+1].key) break;
      else
        {
          list[root] = list[child];
          root=child;
        }
    }
  list[root] = rootkey;
}
void heap_sort(element list[], int n)
{
  int i,j;
  element temp;
  for(i=n/2-1; i>=0; i--) adjust(list,i,n);
  for(i=n-1;i>=0;i--)
    {
      SWAP(&list[0],&list[i]);
      adjust(list, 0, i);
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
  //for(i=0;i<n; i++)
  //  printf("%d\t",a[i].key);
  printf("\n\n");
  t1=clock();
  heap_sort(a,n);
  t2 = clock();
  // for(i=0;i<n; i++)
  // printf("%d\t",a[i].key);
  printf("\n\n");
  printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
  printf("\n\n");
}
