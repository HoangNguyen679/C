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
  }// ktra argument
  char filein[MAX];
  strcpy(filein,argv[1]);
  FILE *f;
  if((f=fopen(filein,"r+")) == NULL || (f=fopen(filein,"r+b")) == NULL ){
    printf("Cannot open %s\n",filein);
    return 1;
  }//ket thuc mo file
  dataheader *header;
  long size1,size2,size,size0;
  fseek(f,sizeof(dataheader),SEEK_SET);
  size1=ftell(f);
  rewind(f);
  fseek(f,0,SEEK_END);
  size=ftell(f);
  rewind(f);
  size2=size-size1;printf("%ld\n",size2);
  fread(header,sizeof(dataheader),1,f);
  size0=header->dungluong;printf("%ld\n",size0);
  if(size2==size0) printf("%ld\n%s\n%s\n",size0,header->name,header->date);
  else printf("Chua ghi header nhe :3\n");
  fclose(f);
} // HET MAIN
