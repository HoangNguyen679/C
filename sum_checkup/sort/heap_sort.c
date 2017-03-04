#include <stdio.h>
#include <stdlib.h>

typedef struct {
  long key;
}element;

void SWAP(element *a,element *b){
  element  temp = *a;
  *a=*b;
  *b=temp;
}

void adjust(element list[], int root, int n){
  int child,rootkey;  
  element temp = list[root-1];
  rootkey = list[root-1].key;
  child = 2*root;
  while(child <= n){
    if((child < n ) && list[child-1].key < list[child].key) child ++;
    if (rootkey >= list[child-1].key) break;
    else {
          list[child/2-1] = list[child-1];
          child*=2;
    }
  }
  list[child/2-1] = temp;
}

void heap_sort(element list[], int n){
  int i,j;
  element temp;
  for(i = n/2-1; i >= 0; i--) adjust(list,i,n);
  for(i = n-1; i > 0; i--) {
    SWAP(&list[0],&list[i]);
    adjust(list, 1, i);
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
  
  heap_sort(a,n);
  
  for(i = 0; i < n; i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");

  return 0;
}
