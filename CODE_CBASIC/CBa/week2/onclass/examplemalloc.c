#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 81
int main(void){
  int i,n,*p;
  printf("How many number do you want to enter?\n");
  scanf("%d",&n);
  p = (int *)malloc(n * sizeof(int));
  if(p == NULL){
    printf("Memory allocation failed!\n");
    return 1;
  }
  printf("Enter the numbers now\n");
  for(i=0;i<n;i++) scanf("%d",&p[i]);
  printf("Numbers in reserve order is \n");
  for(i=n-1;i>=0;i--) printf("%d ",p[i]);
  printf("\n");
  free(p);
  return 0;
}
