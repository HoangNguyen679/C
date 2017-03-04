#include <stdio.h>

int fact(int n){
  if(n < 0) return 0;
  if(n <= 1) return n;

  return n*fact(n-1);
}

int main(){
  int n = 5;
  printf("%d! = %d\n",n,fact(n));

  return 0;
}
