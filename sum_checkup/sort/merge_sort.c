#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 2000000

typedef struct{
  int key;
}element;

void merge(element array[], int first, int middle, int last) {
    element temp[last];
    int first1, last1, first2, last2;
    int index = first;

    first1 = first;
    last1 = middle;
    first2 = middle+1;
    last2 = last;

    while((first1 <= last1) && (first2 <= last2)) {
        if(array[first1].key < array[first2].key) {
            temp[index].key = array[first1].key;
            index ++;
            first1 ++;
        } else {
            temp[index].key = array[first2].key;
            index ++;
            first2 ++;
        }
    }

    if(first2 > last2) {
        while(first1 <= last1) {
            temp[index].key = array[first1].key;
            index ++;
            first1 ++;
        }
    }

    if(first1 > last1) {
        while(first2 <= last2) {
            temp[index].key = array[first2].key;
            index ++;
            first2 ++;
        }
    }

    for(index = first; index <= last; index ++) {
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
  
  merge_sort(a,0,n-1);
  
  for(i = 0; i < n; i++)
    printf("%ld\t",a[i].key);
  printf("\n\n");

  return 0;
}
