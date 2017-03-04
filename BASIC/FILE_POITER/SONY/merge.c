#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 81

typedef struct sony_data{
  char model[25];
  float rom;
  float screen;
  float price;
}sony_data;
sony_data *phone;

void mergeFile();
int size(FILE *f);

int main(int argc,char *argv[]){
  if(argc != 4){
    printf("Wrong argument!\n");
    printf("Struct: ./split file1 flie2 file\n");
    return 1;
  }
  FILE *f,*f1,*f2;
  char file[MAX],file1[MAX],file2[MAX];
  strcpy(file1,argv[1]);
  strcpy(file2,argv[2]);
  strcpy(file,argv[3]);
  f1=fopen(file1,"rb");
  f2=fopen(file2,"rb");
  f=fopen(file,"wb");
  mergeFile(f1,f2,f);
  free(phone);
  printf("\n\n>>>>>SUCCESS<<<<<\n\n");
  return 0;
}

int size(FILE *f){
  fseek(f,0,2);
  int k=ftell(f)/sizeof(sony_data);
  rewind(f);
  return k;
}

void mergeFile(FILE *f1,FILE *f2,FILE *f){
  int c1 = size(f1);
  int c2 = size(f2);
  phone = (sony_data *)malloc((c1+c2)*sizeof(sony_data));
  fread(phone,sizeof(sony_data),c1,f1);
  fread(phone+c1,sizeof(sony_data),c2,f2);
  fwrite(phone,sizeof(sony_data),c1+c2,f);
  fclose(f);
  fclose(f1);
  fclose(f2);
}
