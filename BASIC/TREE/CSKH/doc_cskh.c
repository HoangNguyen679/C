#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"tree.h"
int main(int argc, char *argv[])
{
  if(argc != 2)
    {printf("Wrong argument\n");return 1;}
  FILE *f;
  char file[MAX];
  strcpy(file,argv[1]);
  int k,i;
  if((f=fopen(file,"rb")) == NULL)
    {printf("Cannot open %s\n",file);return -1;}
  node *tree;
  elementtype *a;
  fseek(f,0,2);
  k=ftell(f)/sizeof(elementtype);
  rewind(f);
  a=(elementtype *)malloc(k*sizeof(elementtype));
  fread(a,k,sizeof(elementtype),f);
  printf("%8s%20s%8s\t%5s\t%10s\t%6s\n","mskh","ten","tien","food","electronic","cloth");
  for(i=0; i<k; i++)
    printf("%8s%20s%8.1f\t%5d\t%10d\t%6d\n",a[i].mskh,a[i].ten,a[i].tien,a[i].food,a[i].electronic,a[i].cloth);
  free(a);
  fclose(f);
  return 0;
}
