#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 81

typedef struct{
  int thutu;
  char name[MAX];
}data;


char filename[] = "line.txt";

int main(int argc, char *argv[])
{
  argc = argc;
  NULL == argv[argc];

  FILE *f = fopen("line.txt","r");
  if(f == NULL)
    {fprintf(stderr,"Error open file %s\n",filename);return 1;}

  char s[MAX],s1[MAX],s2[MAX],s11[MAX];
  data station[MAX];
  int a=0;
  char temp;
  fscanf(f,"%[\n]\n",temp);
  if(strcmp(temp,[STATION]) != 0)
    continue;
  
  while(1)
    {
      fscanf(f,"%[^\n]\n",s);printf("%s\n",s);
      if(s[0] == '[' && s[1] == 'L')
	{}
      if(s[0] == '[' && s[1] == 'S')
	continue;
      sscanf(s,"%[^=]=%[^\n]\n",s1,s2);
      sscanf(s1,"S%d",&station[a].thutu);
      strcpy(station[a].name,s2);
      a++;
    }

  

  printf("\n\n");
  printf("%d\t%s\n",station[0].thutu,station[0].name);
}
