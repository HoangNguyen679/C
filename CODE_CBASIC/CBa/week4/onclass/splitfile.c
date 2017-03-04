#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 100
enum {SUCCESS,FAIL};
int main(int arhc,char *argv){
  int reval = SUCCESS;
  if(argc != 4){
    printf("Wrong argument!\n");
    printf("Struct: ./splitfile phone.dat 10 phone1.dat phone2.dat\n");
    return FAIL;
  }
  char sourcefile[MAX];
  char fileout1[MAX];
  char fileout2[MAX];
  int wheresplit;
  strcpy(sourcefile,agrv[1]);
  strcpy(fileout1,argv[3]);
  strcpy(fileout2,argv[4]);
  wheresplit=atoi(argv[2]);
  FILE *f,*fout1,*fout2;
  if((f=fopen(sourcefile,"rb")) == NULL){
    printf("Cannot open %s\n",sourcefile);
    return FAIL;
  }
  else if((fout1=fopen(fileout1,"wb")) == NULL){
    printf("Cannot open %s\n",fileout1);
    return FAIL;
  }
  else if((fout2=fopen(fileout2,"wb")) == NULL){
    printf("Cannot open %s\n",fileout2);
    return FAIL;
  }


