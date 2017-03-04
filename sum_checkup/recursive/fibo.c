#include <stdio.h>

int fiboRec(int n){
  if(n <= 1) return n;

  return fiboRec(n-1) + fiboRec(n-2);
}

int fiboIter(int n){
  if(n <= 1) return n;
  int f1,f2,f3,k;
  f1 = 0; f2 = 1;
  for(k =2; k <= n; k ++){
    f3 = f1 + f2; f1 = f2; f2 = f3;
  }

  return f3;
}

// de quy kh hieu qua nen ta co the khu de quy 

int main(){
  int n = 10;

  printf("Fibo of %d : %d\n",n,fiboRec(n));
  printf("Fibo of %d : %d\n",n,fiboIter(n));
  
  return 0;
}
