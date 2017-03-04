#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 2000000
typedef struct {
  int key;
}element;

void SWAP(element *list1, element *list2){
  element temp=*list1;
  *list1 = *list2;
  *list2 = temp;
}

void quick_sort(element list[], int left, int right) {
  int pivot,i,j; ///pivot la phan tu chot
  if(left < right) {
    i = left;
    j = right + 1;
    pivot = list[left].key;
    do {
      do i++;while(list[i].key < pivot);
      do j--;while(list[j].key > pivot);
      if(i < j) SWAP(&list[i],&list[j]);
    } while(i < j);
    SWAP(&list[left],&list[j]);

    quick_sort(list,left,j-1);
    quick_sort(list,j+1,right);
  }
}

void quick_sort_3partition(element list[], int left, int right){
  if(left >= right) return;
  int i = left-1, j = right;
  int p = left-1, q = right;

  while(1){
    while(list[++i].key < list[right].key);
    while(list[right].key < list[--j].key) if(j == left) break;
    if(i >= j) break;
    SWAP(&list[i],&list[j]);
    if(list[i].key == list[right].key) SWAP(&list[++p],&list[i]);
    if(list[j].key == list[right].key) SWAP(&list[--q],&list[j]);
  }
  SWAP(&list[i],&list[right]);
  j = i-1;
  i = i+1;
  int k;
  for(k = left; k <= p; k++) SWAP(&list[k],&list[j--]);
  for(k = right-1; k >= q; k--) SWAP(&list[k],&list[i++]);

  quick_sort_3partition(list,left,j);
  quick_sort_3partition(list,i,right);
}

int main() {
  int i,k;
  long n;
  
  printf("kich thuoc mang = ");scanf("%ld",&n);
  element *a = (element*)malloc(n*sizeof(element));

  for(i = 0; i < n; i++) {
    a[i].key = rand () % n + 1;
  }
  
  for(i = 0; i < n; i++)
    printf("%d\t",a[i].key);
  printf("\n\n");
  
  quick_sort_3partition(a,0,n-1);
  
  for(i = 0; i < n; i++)
    printf("%d\t",a[i].key);
  printf("\n\n");

  return 0;
}
