#include<stdio.h>
#include<stdlib.h>
#define SIZE 100
int main(int argc,char *argv[]){
  int times_loop;
  if(argc != 2){
    printf("Wrong number of argument\n");
    printf("Struct is ./filename times_loop\n");
    return 1;
  }
  times_loop = atof(argv[1]);
  char word[SIZE];
  printf("Enter a word\n");
  gets(word);
  int i;
  for(i=0;i<times_loop;i++) printf("%s",word);
  printf("\n");
  return 0;
}
