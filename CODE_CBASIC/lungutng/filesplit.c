#include<stdio.h>
#include<string.h>
char filename1[10],filename2[10],filename[10];
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
  f=fopen(filename,"rb");
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
  strcpy(filename,argv[1]);
  int i=atoi(argv[2]);
  strcpy(filename1,argv[3]);
  strcpy(filename2,argv[4]);
  docFile();
  tachFile(i);
  free(sony);
  return 1;
}
