#include<stdio.h>
#include<string.h>
typedef struct{
  char model[25];
  char rom[3];
  char screen[5];
  char price[8];
} smartPhone;
smartPhone *sony;
int main(int argv,char *argc[])
{
  int n;
  char filename[10];
  strcpy(filename,argc[1]);
  FILE *f=fopen(filename,"rb");
 fseek(f,0,2);
  n=ftell(f)/sizeof(smartPhone);
  sony=(smartPhone *)malloc(n*sizeof(smartPhone));
  rewind(f);
  fread(sony,sizeof(smartPhone),n,f);
  int i;
  for(i=0;i<n;i++)
    {printf("%s\t%s\t\%s\t%s\n",sony[i].model,sony[i].rom,sony[i].screen,sony[i].price);}
  free(sony);
  fclose(f);
  return 1;
}
