/* Nguyen Duc Hoang - 9A */
// Date Create: 29/8/2015
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#define MAX 81
enum {SUCCESS,FAIL};
int main(int argc,char*argv[]){
  int reval= SUCCESS;
  if(argc != 3 || argc !=2){
    printf("Argument wrong\n");
    printf("Struct: ./filename filein \n");
    printf("Or: ./filename -p filein\n");
    reval = FAIL;
  }
  if(argc == 3){
  FILE *fin;
  char filein[MAX];
  char command[MAX];
  strcpy(command,argv[1]);
  strcpy(filein,argv[2]);
  if((fin=fopen(filein,"r"))==NULL){
    printf("Cannot open %s\n",filein);
    reval=FAIL;
  }
  else if(strcmp(command,"-p") != 0){
    printf("Sai cu phap\n");
    reval=FAIL;
  }
  else {
    int c;
    int i=0;
    printf("Che do in ra theo trang\n");
    printf("Nhan Enter de in\n");
    char str[MAX];
    do{

        while(fgets(str,MAX,fin) != NULL){
          printf("%s",str);
          i++;
          if(i==30)break;
        }
        i=0;
    }while((c=getchar()) =='\n');
  }
  fclose(fin);
  }
  if(argc==2){
    FILE *fin;
    char filein[MAX];
    strcpy(filein,argv[1]);
    if((fin=fopen(filein,"r"))==NULL){
      printf("Cannot open %s\n",filein);
      reval=FAIL;
    }
    else {
      int c;
      int i=0;
      printf("Che do in binh thuong\n");
      char str[MAX];
      while(fgets(str,MAX,fin) != NULL){
        printf("%s",str);
      }
      fclose(fin);
    }
  }
  return reval;
}
