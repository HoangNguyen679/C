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

int compare(char *numA, char *numB){
  nA = strlen(numA);
  nB = strlen(numB);
  if(nA > nB) return 1;
  else if (nA == nB){
    int i = nA-1;
    while(numA[i] == numB[i]) i--;
    if(i < 0 || numA[i] > numB[i]) return 1;
    else return 0;
  }
  else return 0;
}

int main(int argc, char **argv){
  char c; int i;
  printf("Input num A: ");
  gets(numA);

  printf("Input num B: ");
  gets(numB);

  nA = strlen(numA);
  nB = strlen(numB);

  int m_Compare = compare(numA, numB);
  if(m_Compare) {
    for(i=0; i<nA; i++) Push(numA[i]-'0', &a);
    for(i=0; i<nB; i++) Push(numB[i]-'0', &b);
  } else {
    for(i=0; i<nA; i++) Push(numA[i]-'0', &b);
    for(i=0; i<nB; i++) Push(numB[i]-'0', &a);
  }


  int temp;
  int carry = 0;
  while(!IsEmpty(&a) || !IsEmpty(&b)){
    temp = Pop(&a) - Pop(&b) - carry;

    if (temp >= 0){
      Push(temp%10, &sum);
      carry = 0;
    }
    else {
      Push((10+ temp)%10, &sum);
      carry = 1;
    }
  }

  printf("\nRES       = ");
  if(!m_Compare) printf("-");
  while(!IsEmpty(&sum))
    printf("%d", Pop(&sum));
  printf("\n");
  return 0;
}
