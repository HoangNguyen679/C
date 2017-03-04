#include<stdio.h>
#include<stdlib.h>
enum{SUCCESS,FAIL};

void CharReadWrite(FILE *fin,FILE *fout){
  int c;
  while((c=fgetc(fin)) != EOF) {
    fputc(c,fout);
    putchar(c);
  }
}
main(void){
  FILE *f1,*f2;
  char filename1[]="lab1.txt";
  char filename2[]="lab1w.txt";
  int reval = SUCCESS;
  if ((f1=fopen(filename1,"r")) == NULL){
    printf("cannot open %s \n",filename1);
    reval = FAIL;
  }
  else if((f2=fopen(filename2,"w")) == NULL){
    printf("cannot open %s \n",filename2);
    reval = FAIL;
  } 
  else {
    CharReadWrite(f1,f2);
    fclose(f1);
    fclose(f2);
  }
  return reval;
}

