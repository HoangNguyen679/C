#include<stdio.h>
#include<string.h>
#define MAX 100
char filename1[MAX],filename2[MAX];
FILE *f,*f1,*f2;
int n;
typedef struct{
  char model[25];
  char rom[3];
  char screen[5];
  char price[8];
} smartPhone;
smartPhone *sony;
void docFile()
{
  f=fopen("sony.dat","rb");
  fseek(f,0,2);
  n=ftell(f)/sizeof(smartPhone);
  rewind(f);
  sony=(smartPhone *)malloc(n*sizeof(smartPhone));
  fread(sony,sizeof(smartPhone),n,f);
  fclose(f);
}
void tachFile(int i)
{
  f1=fopen(filename1,"wb");
  f2=fopen(filename2,"wb");
  fwrite(sony,sizeof(smartPhone),i,f1);
  fwrite(sony+i,sizeof(smartPhone),n-i,f2);
  fclose(f1);
  fclose(f2);
}
int main(int argc,char* argv[])
{
  if(argc != 5){
  printf("Wrong argumnet\n");
  printf("Struct: ./filename grade.dat 10 grade1.dat grade2.dat");
}
  int i=atoi(argv[2]);
  strcpy(filename,argv[2]);
  strcpy(filename1,argv[3]);
  strcpy(filename2,argv[4]);
  docFile();
  tachFile(i);
  free(sony);
  return 1;
}
