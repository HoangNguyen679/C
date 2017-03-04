#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 81

typedef struct phone_address{
  char name[25];
  char tel[12];
  char email[25];
}phone_address;

char filename[MAX];
FILE *f_dat;

void printFile(phone_address *phone,FILE *f);

int main(int argc,char *argv[]){
  if(argc != 2){printf("Wrong choice\nStruct: ./r file");return 1;}
  strcpy(filename,argv[1]);
  phone_address *phone;int c;
  if((f_dat=fopen(filename,"rb")) == NULL){
    printf("Cannot open %s\n",filename);
    return 1;
  }
  printFile(phone,f_dat);
  fclose(f_dat);
  return 0;
}

void printFile(phone_address *phone,FILE *f){
  int a,i=0,n;
  fseek(f,0,2);
  n=ftell(f)/sizeof(phone_address);
  rewind(f);
  phone = (phone_address *)malloc(n*sizeof(phone_address));
  a=fread(phone,sizeof(phone_address),n,f);
  for(i=0;i<n;i++){
    printf("%-25s\t%-12s\t%-25s\n",(phone+i)->name,(phone+i)->tel,(phone+i)->email);
  }
 free(phone);
}
