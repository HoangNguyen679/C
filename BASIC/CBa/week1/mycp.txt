#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 100

void CharReadWrite(FILE *fin,FILE *fout){
  int c;
  while((c=fgetc(fin)) != EOF) fputc(c,fout);
}

int main(int argc,char *argv[]){
  if(argc != 3){
    printf("Wrong number of argument\n");
    printf("Struct : ./mycp a1.txt a2.txt\n");
  }

  char filenamecp[SIZE];
  char filenamepa[SIZE];
  strcpy(filenamecp,argv[1]);
  strcpy(filenamepa,argv[2]);

  FILE *fcp,*fpa;

  if((fcp=fopen(filenamecp,"r")) == NULL){
    printf("Cannot open %s\n",filenamecp);
    return 1;
  }
  else if((fpa=fopen(filenamepa,"w")) == NULL){
    printf("Cannot open %s\n",filenamepa);
    return 1;
  }
   else  CharReadWrite(fcp,fpa);

  fclose(fcp);
  fclose(fpa);
  return 0;
}
