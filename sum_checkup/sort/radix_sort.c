/* 
Xet so nguyen kh am 32 bit nhu vay ta se chuyen no thanh so co 4 chu so 
trong he co so 256 vs phep & va phep dich bit >> voi thanh ghhi shift = 8
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 256

typedef struct {
  long key;
}element;

void SWAP(element *a,element *b){
  element  temp = *a;
  *a=*b;
  *b=temp;
}

void radix_sort(element list[], int n){
  element *out =  (element*)malloc(n*sizeof(element));;

  // tinh kich thuoc moi cum va sao chep phan tu vao mang out
  int i,j, shift;
  int bin_size[MAX], first_ind[MAX];
  for(shift = 0; shift < 32; shift += 8){
    for(i = 0; i < MAX; i++)
      bin_size[i] = 0;
    for(j = 0; j < n; j ++){
      i = (list[j].key >> shift) & (MAX - 1);
      bin_size[i]++;
      out[j] = list[j];
    }
    
    // tinh chi so bat dau moi cum
    first_ind[0] = 0;
    for(i = 1; i < 256; i++)
      first_ind[i] = first_ind[i-1] + bin_size[i-1];

    // sao chep phan tu mang out vao cum cua no trong mang list
    for(j = 0; j < n; j++){
      i = (out[j].key >> shift) & (MAX - 1);
      list[first_ind[i]] = out[j];
      first_ind[i]++;
    }
  }
  
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
  
  radix_sort(a,n);
  
  for(i = 0; i < n; i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");

  return 0;
}
