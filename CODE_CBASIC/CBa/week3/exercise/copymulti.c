/* Nguyen Duc Hoang - 9A */
// Date Create: 29/8/2015
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#define MAX 81
enum {SUCCESS,FAIL};
void CharReadWrite(FILE *fin,FILE *fout){
  int c;
  while((c=fgetc(fin)) != EOF){
    fputc(c,fout);
  }
}
void LineReadWrite(FILE *fin,FILE *fout){
  char str[MAX];
  while(fgets(str,MAX,fin) != NULL)
    fputs(str,fout);
}
void BlockReadWrite(FILE *fin,FILE *fout){
  int num;
  char point[MAX];
  while(feof(fin) == 0){
    num=fread(point,sizeof(char),80,fin);
    point[num*sizeof(char)] = '\0';
    fwrite(point,sizeof(char),num,fout);
  }
}
int main(int agrc,char *argv[]){
  int reval=SUCCESS;
  if(agrc != 3){
    printf("Argument failed!\n");
    printf("Struct: ./filename filein fileout\n");
    reval = FAIL;
    return reval;
  }
  int chon;
  FILE *fin,*fout;
  char filenamein[MAX],filenameout[MAX];
  strcpy(filenamein,argv[1]);
  strcpy(filenameout,argv[2]);
  if((fin=fopen(filenamein,"r")) == NULL){
    printf("Cannot open %s\n",filenamein);
    reval = FAIL;
  }
  if((fout=fopen(filenameout,"w")) == NULL){
    printf("Cannot open %s\n",filenameout);
    reval = FAIL;
  }
  time_t time1,time2;
  do{
    printf("MENU\n");
    printf("1.Sao chep theo ki tu\n");
    printf("2.Sao chep thep dong\n");
    printf("3.Sao chep theo block - kich thuoc tuy y\n");
    printf("4.Thoat\n\n");
    scanf("%d",&chon);
    switch(chon){
    case 1:{
      clock_t start =clock();
      //CharReadWrite(fin,fout);
      int c;
      while((c=fgetc(fin)) != EOF){
        fputc(c,fout);
      }
      clock_t finish=clock();
      printf("%lf\n",(double)(finish-start)/CLOCKS_PER_SEC);
    }break;
    case 2:{
      clock_t start =clock();
      LineReadWrite(fin,fout);
      clock_t finish=clock();
      printf("%f\n",(double)(finish-start)/CLOCKS_PER_SEC);

    }break;
    case 3: {
      clock_t start =clock();
      BlockReadWrite(fin,fout);
      clock_t finish=clock();
      printf("%f\n",(double)(finish-start)/CLOCKS_PER_SEC);
    }break;
    }

  } while(chon != 4);
  fclose(fin);
  fclose(fout);
  return reval;
}
