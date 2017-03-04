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

void bubble_sort(element list[], int n){
  int i,j;
  for(i = n; i > 0; i--)
    for(j = 0; j < i; j++ )
      if(list[j+1].key < list[j].key)
        SWAP(&list[j+1],&list[j]);
}

int main(){
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
  
  bubble_sort(a,n);
  
  for(i = 0; i < n; i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");

  return 0;
}
