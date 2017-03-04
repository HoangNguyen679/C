#include<stdio.h>
#include<stdlib.h>
enum {SUCCESS,FAIL};
main(void){
  FILE *fptr;
  char filename[]="a.txt";
  int reval = SUCCESS;

  if ((fptr=fopen(filename,"r")) == NULL){
    printf("cannot open %s \n",filename);
    reval = FAIL;
  }
  else {
    printf("The value of fptr: 0x%p\n",fptr);
    printf("ready to close file\n");
    fclose(fptr);
  }

  return reval;
}
