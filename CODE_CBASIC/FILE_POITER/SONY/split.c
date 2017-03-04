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

void readFile();
void splitFile(int n);

FILE *f,*f1,*f2;
char file[MAX],file1[MAX],file2[MAX];
sony_data *phone;
int c; //so phan tu cua file

int main(int argc,char *argv[]){
  if(argc != 5){
    printf("Wrong argument!\n");
    printf("Struct: ./split file file1 flie2 n\n");
    return 1;
  }
  strcpy(file,argv[1]);
  strcpy(file1,argv[2]);
  strcpy(file2,argv[3]);
  int n=atoi(argv[4]);
  readFile();
  splitFile(n);
  free(phone);
  printf("\n\n>>>>>SUCCESS<<<<<\n\n");
  return 0;
}

void readFile(){
  f=fopen(file,"rb");
  fseek(f,0,2);
  c=ftell(f)/sizeof(sony_data);
  rewind(f);
  phone = (sony_data *)malloc(c*sizeof(sony_data));
  fread(phone,sizeof(sony_data),c,f);
  fclose(f);
}

void splitFile(int n){
  f1=fopen(file1,"wb");
  f2=fopen(file2,"wb");
  fwrite(phone,sizeof(sony_data),n,f1);
  fwrite(phone+n,sizeof(sony_data),c-n,f2);
  fclose(f1);
  fclose(f2);
}
