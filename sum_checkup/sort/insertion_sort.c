#include <stdio.h>
#include <stdlib.h>

typedef struct {
  long key;
} element;

void SWAP(element *a,element *b){
  element  temp = *a;
  *a=*b;
  *b=temp;
}

void insertion_sort(element list[], int n){
  int i,j;
  element next;
  for(i = 1; i < n; i++) {
      next = list[i];
      for(j = i-1; j >= 0 && next.key < list[j].key; j--)
        list[j+1] = list[j];
      list[j+1] = next;
    }
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
    printf("%ld\t",a[i].key);
  printf("\n\n");
  
  insertion_sort(a,n);

  for(i=0;i<n;i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");

  return 0;
}
