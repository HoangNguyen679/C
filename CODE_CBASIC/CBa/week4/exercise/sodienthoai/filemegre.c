#include<stdio.h>
#include<string.h>
char filename[10],filename1[10],filename2[10];
int n,n1,n2;
FILE *f,*f1,*f2;
typedef struct{
  char model[25];
  char rom[3];
  char screen[5];
  char price[8];
} smartPhone;
smartPhone *sony;
int soluong(FILE *f)
{ 
  int k;
  fseek(f,0,2);
  k=ftell(f)/sizeof(smartPhone);
  rewind(f);
  return k;
}
void docFile()
{
  f1=fopen(filename1,"rb");
  f2=fopen(filename2,"rb");
  n1=soluong(f1);
  n2=soluong(f2);
  n=n1+n2;
  sony=(smartPhone *)malloc(n*sizeof(smartPhone));
  fread(sony,sizeof(smartPhone),n1,f1);
  fread(sony+n1,sizeof(smartPhone),n2,f2);
  fclose(f1);
  fclose(f2);
}
void ghepFile()
{
  f=fopen(filename,"wb");
  fwrite(sony,sizeof(smartPhone),n,f);
  fclose(f);
}
int main(int argv,char* argc[])
{
  strcpy(filename1,argc[1]);
  strcpy(filename2,argc[2]);
  strcpy(filename,argc[3]);
  docFile();
  ghepFile();
}
