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
  printf("%15s\t%15s\n","TU","NGHIA");
  for(i=0; i<k; i++)
    printf("%15s\t%15s\n",a[i].tu,a[i].nghia);
  free(a);
  fclose(f);
  return 0;
}
