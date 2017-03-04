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

char filename[MAX];
FILE *f_dat;

void printFile(sony_data *phone,FILE *f);

int main(int argc,char *argv[]){
  if(argc != 2) {
    printf("Wrong argument\nStruct: ./r filename\n");
    return 1;
  }
  strcpy(filename,argv[1]);
  sony_data *phone;int c;
  if((f_dat=fopen(filename,"r+b")) == NULL){
    printf("Cannot open %s\n",filename);
    return 1;
  }
  printFile(phone,f_dat);
  fclose(f_dat);
  return 0;
}

void printFile(sony_data *phone,FILE *f){
  int c,i=0,n;
  fseek(f,0,2);
  n=ftell(f)/sizeof(sony_data);
  rewind(f);
  phone = (sony_data *)malloc(n*sizeof(sony_data));
  c=fread(phone,sizeof(sony_data),n,f);
  printf("\n\n>>>>>>>>>> DATABASE <<<<<<<<<<\n\n");
  printf("\n\n%-25s\t%-8s\t%-8s\t%-8s\n\n","MODEL","ROM","SCREEN","PRICE");
  for(i=0; i<n; i++){
    printf("%-25s\t%-8.1f\t%-8.1f\t%-8.1f\n",(phone+i)->model,(phone+i)->rom,(phone+i)->screen,(phone+i)->price);
  }
  free(phone);
}
