#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX  81
typedef struct{
  char *stt;
  char *name;
  char *MSSV;
  float diem;
}dulieu;
int main(){
  FILE *fin,*fout;
  char filein[]="bangdiem.txt";
  char fileout[]="grade.dat";
//mo file dat de doc
if((fin=fopen(filein,"r")) == NULL){
    printf("Cannot open %s",filein);
    return 1;
  }
else if((fout=fopen(fileout,"rb")) == NULL){
    printf("Cannot open %s",fileout);
    return 1;
  }
 char str[MAX];
  int sosv=0;
  int i; //i la bien dem
  while((fgets(str,MAX,fin)) != NULL) sosv++;rewind(fin);
  printf("%d\n",sosv);
dulieu * sinhvien;
  //cap phat moi
  sinhvien = (dulieu *)malloc(sosv * sizeof(dulieu));
  for(i=0;i<sosv;i++){
    (sinhvien+i)->name = (char*)malloc(25*sizeof(char));
    (sinhvien+i)->MSSV = (char*)malloc(9*sizeof(char));
    (sinhvien+i)->stt = (char*)malloc(3*sizeof(char));
  }

  //doc tu file dat
  for(i=0;i<sosv;i++){
    fread((sinhvien+i)->stt,sizeof((sinhvien+i)->stt),1,fout);
    fread((sinhvien+i)->MSSV,sizeof((sinhvien+i)->MSSV),1,fout);
    fread((sinhvien+i)->name,sizeof((sinhvien+i)->name),1,fout);
    fread(&(sinhvien+i)->diem,sizeof((sinhvien+i)->diem),1,fout);
  }
  for(i=0;i<sosv;i++){
    printf("%s\t%s\t%s\t%f\n",(sinhvien+i)->stt,(sinhvien+i)->name,(sinhvien+i)->MSSV,(sinhvien+i)->diem);
  }
  fclose(fin);
  //giai phong bo nho
  for(i=0;i<sosv;i++){
    free((sinhvien+i)->stt);
    free((sinhvien+i)->name);
    free((sinhvien+i)->MSSV);
   }
  free(sinhvien);
 return 0;
}
