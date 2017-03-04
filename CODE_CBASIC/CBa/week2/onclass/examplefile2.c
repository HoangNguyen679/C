#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define SIZE 100
enum {SUCCESS,FAIL};
// doi chu hoa thanh chu thuong va nguoc lai
void CharReadWriteChange(FILE *fin,FILE *fout){
  int c;
  while((c=fgetc(fin)) != EOF){
    if (islower(c)) fputc(toupper(c),fout);
    else if (isupper(c)) fputc(tolower(c),fout);
    else fputc(c,fout);
  }
}

main(){
  FILE *f1,*f2;
  char filename1[]="a1.txt";
  char filename2[]="a2.txt";
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
    CharReadWriteChange(f1,f2);
    fclose(f1);
    fclose(f2);
  }
  return reval;
}
