#include <stdio.h>

int maxSub(int list[], int n){
  int sumMax = list[0];
  int maxEndHere = list[0];
  int imax = 0;
  int i,u,v;

  for(i = 1; i < n; i++){
    u = maxEndHere + list[i];
    v = list[i];
    maxEndHere = (u > v) ? u : v;
    if(maxEndHere > sumMax){
      sumMax = maxEndHere;
      imax = i;
    }
  }

  return sumMax;
}

int main(){
  int list[5]={-2,11,-4,13,-5};
  int x = maxSub(list,5);

  printf("%d\n",x);
}

// O = n
