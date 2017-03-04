#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
  long key;
}element;

void SWAP(element *a,element *b){
  element  temp = *a;
  *a=*b;
  *b=temp;
}

void counting_sort(element list[], int n){
  element *out =  (element*)malloc(n*sizeof(element));;
  int count[n+1],i;
  
  memset(count, 0, sizeof(count)); 
  
  for(i = 0; i < n; i++)
    ++count[list[i].key];

  for(i = 1; i <= n; i++)
    count[i] += count[i-1];

  for(i = 0; i < n; i++){
    out[count[list[i].key] - 1] = list[i];
    --count[list[i].key];
  }

  for(i = 0; i < n; i++)
    list[i] = out[i];
}

int main(){
  int i,k;
  long n;
  
  printf("kich thuoc mang = ");scanf("%ld",&n);
  element *a = (element*)malloc(n*sizeof(element));

  printf("\n\n");
  
  for(i = 0; i < n; i++) {
    a[i].key = rand () % n + 1;
  }
  
  for(i = 0; i < n; i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");
  
  counting_sort(a,n);
  
  for(i = 0; i < n; i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");

  return 0;
}
