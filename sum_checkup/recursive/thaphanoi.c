#include <stdio.h>

int i = 0;

void move(int n, char start, char finish, char spare){
  if(n == 1){
    printf("Move from %c to %c\n",start,finish);
    i++;
    return;
  }

  move(n-1,start,spare,finish);
  move(1,start,finish,spare);
  move(n-1,spare,finish,start);
}

int main(){
  int disk;
  printf("Input : ");scanf("%d",&disk);
  move(disk,'1','3','2');
  printf("Total moves: %d\n",i);

  return 0;
}
