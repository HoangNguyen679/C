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
    for(j=0; j<i; j++ )
      if(list[j+1].key < list[j].key)
        SWAP(&list[j+1],&list[j]);
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
void quick_sort(element list[], int left, int right)
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

void merge(element array[], int first, int middle, int last) {
    element temp[last];
    int first1, last1, first2, last2;
    int index = first;
    first1 = first;
    last1 = middle;
    first2 = middle+1;
    last2 = last;
    while((first1 <= last1) && (first2 <= last2))
      {
        if(array[first1].key < array[first2].key)
          {
            temp[index].key = array[first1].key;
            index ++;
            first1 ++;
          }
        else
          {
            temp[index].key = array[first2].key;
            index ++;
            first2 ++;
          }
      }
    if(first2 > last2)
      {
        while(first1 <= last1)
          {
            temp[index].key = array[first1].key;
            index ++;
            first1 ++;
          }
      }
    if(first1 > last1)
      {
        while(first2 <= last2)
          {
            temp[index].key = array[first2].key;
             index ++;
             first2 ++;
          }
      }
    for(index = first; index <= last; index ++)
      {
        array[index].key = temp[index].key;
      }
    return;
}

void merge_sort(element array[], int first, int last) {
    if(first < last) {
        int middle = ((first + last) / 2);
        merge_sort(array, first, middle);
        merge_sort(array, middle + 1, last);
        merge(array, first, middle, last);
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
  printf("6. Sap xep nhanh\n");
  printf("7. Sap xep tron\n");
  printf("8. Thoat\n");
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
        case 6:
          t1=clock();
          quick_sort(a,0,n-1);
          t2 = clock();
          printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
          break;
        case 7:
          t1=clock();
          merge_sort(a,0,n-1);
          t2 = clock();
          printf("%f\n",(double)(t2-t1)/CLOCKS_PER_SEC);
          break;
        case 8: return 0;
        default: printf("Wrong choice\n");
        }
    }
  while(1);
}
