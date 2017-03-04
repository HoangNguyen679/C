#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 100
enum {SUCCESS,FAIL};
int main(){
  int reval=SUCCESS;
  FILE *fin,*fout;
  char filein[]="in.txt";
  char fileout[]="out.txt";
  if((fin=fopen(filein,"r")) == NULL){
    printf("Cannot open %s\n",filein);
    return FAIL;
  }
  if((fout=fopen(fileout,"w")) == NULL){
    printf("Cannot open %s\n",fileout);
    return FAIL;
  }
  int n;
  fscanf(fin,"%d",&n);
  rewind(fin);

