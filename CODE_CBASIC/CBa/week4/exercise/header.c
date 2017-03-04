/* Nguyen Duc Hoang - 9A */
// Date Create: 13/9/2015
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 100
typedef struct{
  long dungluong;
  char name[25];
  char date[50];
}dataheader;
int main(int argc, char *argv[]){
  if(argc != 2){
    printf("Wrong argument!\n");
    printf("Struct: ./filename filename\n");
    return 1;
  }
  char filein[MAX];
  strcpy(filein,argv[1]);
  FILE *f;
  if((f=fopen(filein,"r+")) == NULL || (f=fopen(filein,"r+b")) == NULL ){
    printf("Cannot open %s\n",filein);
    return 1;
  }
  long size;
  fseek(f,0,SEEK_END);
  size = ftell(f);
  fseek(f,0,SEEK_SET);
  dataheader *header,*header1;
  struct tm *local;
  time_t t;
  t = time(NULL);
  local = localtime(&t);
  header->dungluong=size;
  strcpy(header->name,"Nguyen Duc Hoang");
  strcpy(header->date,asctime(local));
  fwrite(header,sizeof(dataheader),1,f);
  rewind(f);

  fclose(f);
  return 0;
}
