#include <stdio.h>

int C(int n, int k){
  if(k == 0 || k == n) return 1;

  return C(n-1, k-1) + C(n-1,k);
}

int main(){
  int n = 5, k = 2;

  printf("%dC%d = %d\n",n,k,C(n,k));

  return 0;
}
