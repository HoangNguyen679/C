#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int ElementType;

#include "StackLinkList.h"

StackType *top = NULL;

char a[100];

int main(int argc, char **argv){
  int i;
  printf("Input: "); gets(a);
  int N = strlen(a);

  int b, c;
  for(i=0; i<N; i++){
    if((a[i]-'0')>=0 && ( a[i]-'0')<10)
      Push((a[i]-'0'), &top);
    if(a[i] == '+') Push(Pop(&top)+Pop(&top), &top);
    if(a[i] == '*') Push(Pop(&top)*Pop(&top), &top);
    if(a[i] == '/') {
      c = Pop(&top);
      b = Pop(&top);
      Push(b/c, &top);
    }
    if(a[i] == '-') {
      c = Pop(&top);
      b = Pop(&top);
      Push(b-c, &top);
    }

  }

  while(!IsEmpty(&top))
    printf("%d", Pop(&top));
  printf("\n");
  return 0;
}

