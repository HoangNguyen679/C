#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 81
enum {SUCCESS,FAIL};
void BinaryReadWrite(FILE *fin,FILE *fout){
  int num;
  char point[MAX];
  while(feof(fin) == 0){
    num = fread(point,sizeof(char),80,fin);
    point[num*sizeof(char)]='\0';
    printf("%s",point);
    fwrite(point,sizeof(char),num,fout);
  }
}
int main(){
  FILE *f1,*f2;
  char filename1[]="lab1a.txt";
  char filename2[]="lab1.txt";
  int reval = SUCCESS;
  if((f1=fopen(filename1,"w")) == NULL){
    printf("cannot open %s\n",filename1);
    reval = FAIL;
  } else if((f2=fopen(filename2,"r")) == NULL){
    printf("cannot open %s\n",filename2);
    reval = FAIL;
  } else {
    BinaryReadWrite(f2,f1);
    fclose(f1);
    fclose(f2);
  }
  return reval;
}
