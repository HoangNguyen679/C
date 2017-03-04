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
      for(j=i+1; j>=0 && next.key < list[j].key; j--)
        list[j+1] = list[j];
      list[j+1] = next;
    }
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
void bubble_sort(element list[], int n)
{
  int i,j;
  for(i = n; i>0; i--)
    for(j=0; i<i; j++ )
      if(list[j+1].key > list[j].key)
        SWAP(&list[j+1],&list[j]);
}

void adjust(element list[], int root, int n)
{
  int child;
  element rootkey;
  rootkey=list[root-1];
  child = 2* root;
  while(child <= n)
    {
      if((child < n ) && list[child].key < list[child+1].key) child ++;
      if (rootkey.key > list[child].key) break;
      else {
        list[child/2-1] = list[child-1];
        child *= 2;
      }
    }
  list[child/2-1] = rootkey;
}
void heap_sort(element list[], int n)
{
  int i,j;
  element temp;
  for(i=n/2; i>0; i--) adjust(list,i,n);
  for(i=n-1;i>0;i--)
    {
      SWAP(&list[0],&list[i]);
      adjust(list, 1, i);
    }
}
void menu()
{
  printf("MENU\n\n");
  printf("1. Tao lai du lieu\n");
  printf("2. Sap xep chen\n");
  printf("3. Sap xep chon\n");
  printf("4. Sap xep noi bot\n");
  printf("5. Sap xep vun dong\n");
  printf("6. Thoat\n");
  printf("Select: ");
}
int main()
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
  do
    {
      menu();
      scanf("%d",&k);
      switch(k)
        {
        case 1:
          for(i=0; i<n; i++)
            {
              a[i].key = rand () % n + 1;
            }
          break;
        case 2:
          t1=clock();
          insertion_sort(a,n);
          t2 = clock();
          printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
          break;
        case 3:
          t1=clock();
          selection_sort(a,n);
          t2 = clock();
          printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
          break;
        case 4:
          t1=clock();
          bubble_sort(a,n);
          t2 = clock();
          printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
          break;
        case 5:
          t1=clock();
          heap_sort(a,n);
          t2 = clock();
          printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
          break;
        case 6: return 0;
        default: printf("Wrong choice\n");
        }
    }
  while(1);
}
