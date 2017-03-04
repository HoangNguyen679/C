#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX  81
typedef struct{
  char stt[3];
  char name[35];
  char MSSV[9];
  float diem;
}dulieu;
int main(){
  FILE *fin,*fout;
  char filein[]="bangdiem.txt";
  char fileout[]="grade.dat";
  if((fin=fopen(filein,"r")) == NULL){
    printf("Cannot open %s",filein);
    return 1;
  }//het fopen filein
  else if((fout=fopen(fileout,"wb")) == NULL){
    printf("Cannot open %s",fileout);
    return 1;
  }//het fopen fileout
  char str[MAX];
  int sosv=0;
  int i; //i la bien dem
  while((fgets(str,MAX,fin)) != NULL) sosv++;rewind(fin);
  printf("%d\n",sosv);
  dulieu *sinhvien;
  sinhvien = (dulieu *)malloc(sosv * sizeof(dulieu));
  for(i=0;i<sosv;i++){

    fscanf(fin,"%s",(sinhvien+i)->stt);
    fscanf(fin,"%s",(sinhvien+i)->name);
    fscanf(fin,"%s",(sinhvien+i)->MSSV);
    fscanf(fin,"%f",&(sinhvien+i)->diem);
  }

  //ghi diem ra file dat

  for(i=0;i<sosv;i++){
    fwrite((sinhvien+i)->stt,2*sizeof((sinhvien+i)->stt),1,fout);
    fwrite((sinhvien+i)->name,2*sizeof((sinhvien+i)->name),1,fout);
    fwrite((sinhvien+i)->MSSV,2*sizeof((sinhvien+i)->MSSV),1,fout);
    fwrite(&(sinhvien+i)->diem,sizeof((sinhvien+i)->diem),1,fout);
  }

  //giai phong bo nho
  for(i=0;i<sosv;i++){

  }
  free(sinhvien);
  rewind(fin);
  fclose(fout);
  FILE *f;
  //mo file dat de doc
   if((f=fopen(fileout,"rb")) == NULL){
    printf("Cannot open %s",fileout);
    return 1;
  }
  //cap phat moi
  sinhvien = (dulieu *)malloc(sosv * sizeof(dulieu));
  for(i=0;i<sosv;i++){

  }

  //doc tu file dat
  for(i=0;i<sosv;i++){
    fread((sinhvien+i)->stt,sizeof((sinhvien+i)->stt),1,f);
    fread((sinhvien+i)->name,sizeof((sinhvien+i)->name),1,f);
    fread((sinhvien+i)->MSSV,sizeof((sinhvien+i)->MSSV),1,f);
    fread(&(sinhvien+i)->diem,sizeof((sinhvien+i)->diem),1,f);
  }
  for(i=0;i<sosv;i++){
    printf("%s\t%s\t%s\t%f\n",(sinhvien+i)->stt,(sinhvien+i)->name,(sinhvien+i)->MSSV,(sinhvien+i)->diem);
  }
  //giai phong bo nho lan nua
  fclose(fin);
  fclose(f);
  return 0;
}
