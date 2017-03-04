#include <stdio.h>
#define MAX(a,b) ((a >b) ? a: b)

int maxLeft(int list[], int i, int j){
  int maxSum = -999;
  int sum = 0;
  int k;

  for(k = j; k >= i; k--){
    sum += list[k];
    maxSum = (maxSum > sum) ? maxSum : sum;
  }
  return maxSum;
}

int maxRight(int list[], int i, int j){
  int maxSum = -999;
  int sum = 0;
  int k;

  for(k = i; k <= j; k++){
    sum += list[k];
    maxSum = (maxSum > sum) ? maxSum : sum;
  }
  return maxSum;
}

int maxSub(int list[], int i, int j){
  if(i == j) return list[i];
  int m,wL,wR,wM;

  m = (i + j)/2;
  wL = maxSub(list, i, m);
  wR = maxSub(list, m+ 1, j);
  wM = maxLeft(list, i, m) + maxRight(list, m+1, j);

  return MAX(MAX(wL,wR),wM);
  
}

int main(){
  int list[5]={-2,11,-4,13,-5};
  int x = maxSub(list,0,4);

  printf("%d\n",x);
}

// O = nlogn
