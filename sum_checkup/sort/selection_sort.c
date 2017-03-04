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

void selection_sort(element list[],int n){
  int i,j,min;
  element tmp;
  for(i = 0; i < n-1; i++){
      min = i;
      for(j = i+1; j < n; j++)
        if(list[j].key < list[min].key) 
          min = j;
      SWAP(&list[i],&list[min]);
  }
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
  
  selection_sort(a,n);
  
  for(i = 0; i < n; i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");

  return 0;
}
