#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 100
enum {SUCCESS,FAIL};
//them mot dong trang vao giua cac dong cua file van ban
void CharReadWriteChange(FILE *fin,FILE *fout){
  int c;
  while((c=fgetc(fin)) != EOF) {
    if(c == '\n'){
      fputc('\n',fout);
      fputc(c,fout);
    }
    else fputc(c,fout); 
  }
}
int main(int argc,char *argv[]){
  if(argc != 3){
    printf("Wrong number of argument\n");
    printf("Struct is ./filename file1 file2\n");
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
   else  CharReadWriteChange(fcp,fpa);

  fclose(fcp);
  fclose(fpa);
  return reval;
}
