#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 81
enum{SUCCESS,FAIL};

void LineReadWrite(FILE *fin,FILE *fout){
  char str[SIZE];
  while(fgets(str,SIZE,fin) != NULL) {
    fputs(str,fout);
    printf("%s",str);
  }
}
int main(int argc,char *argv[]){
  if(argc != 3){
    printf("Wrong number of argument\n");
    printf("Struct is ./filename filename1 filename2\n");
  }

  int reval = SUCCESS;
  char filenamecp[SIZE];
  char filenamepa[SIZE];
  strcpy(filenamecp,argv[1]);
  strcpy(filenamepa,argv[2]);


  FILE *fcp,*fpa;

  if((fcp=fopen(filenamecp,"r")) == NULL){
    printf("Cannot open %s\n",filenamecp);
    reval = FAIL;
  }
  else if((fpa=fopen(filenamepa,"w")) == NULL){
    printf("Cannot open %s\n",filenamepa);
    reval = FAIL;
  }
   else  LineReadWrite(fcp,fpa);

  fclose(fcp);
  fclose(fpa);
  return reval;
}

