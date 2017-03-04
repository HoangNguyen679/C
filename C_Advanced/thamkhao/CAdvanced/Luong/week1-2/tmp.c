#include<stdio.h>
#include<stdlib.h>

void printMe(int a)
{
  printf("a = %d\n", a);
}

int main()
{
  int A[] = {1, 2, 3, 4};
  int a = 6;
  int *p = A+1;
  printf("%d\n", *p);
  printf("size of int = %ld\n", sizeof(int));
  printMe(a--);
  printf("a = %d\n", a);
}
