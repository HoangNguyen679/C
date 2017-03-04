#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef int ElementType;

#include "StackLinkList.h"

StackType *a = NULL;
StackType *b = NULL;
StackType *sum = NULL;

char numA[MAX]; int nA;
char numB[MAX]; int nB;

int main(int argc, char **argv){
  char c;
  printf("Input num A: ");
  gets(numA);

  printf("Input num B: ");
  gets(numB);

  nA = strlen(numA);
  nB = strlen(numB);

  int i;
  for(i=0; i<nA; i++) Push(numA[i]-'0', &a);
  for(i=0; i<nB; i++) Push(numB[i]-'0', &b);


  int temp;
  int carry = 0;
  while(!IsEmpty(&a) || !IsEmpty(&b)){
    temp = Pop(&a) + Pop(&b) + carry;
    if(temp >=10){
      Push(temp-10, &sum);
      carry = 1;
    }
    else {
      Push(temp, &sum);
      carry = 0;
    }
  }

  if(carry) Push(1, &sum);

  printf("\nSUM        = ");


  while(!IsEmpty(&sum))
    printf("%d", Pop(&sum));
  printf("\n");

  free(a);free(b);free(sum);
  return 0;
}
