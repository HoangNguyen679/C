#include <stdio.h>

int main(){
  int maxSum = 0;
  int n = 5;
  int i,j,k;
  int list[5]={-2,11,-4,13,-5};
  
  for(i = 0; i < n; i++){
    for(j = i; j < n; j++){
      int sum = 0;

      for(k = i; k <= j; k++)
	sum += list[k];

      if(sum > maxSum) maxSum = sum;
      
    }
  }

  printf("%d\n",maxSum);
}
