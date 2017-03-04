#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX  81
typedef struct{
  char stt[3];
  char MSSV[9];
  char name[25];
  float diem;
}dulieu;
int main(){
  FILE *fin,*f;
  char filein[]="bangdiem.txt";
  char fileout[]="grade.dat";
  if((fin=fopen(filein,"r")) == NULL){
    printf("Cannot open %s",filein);
    return 1;
  }//het fopen filein
  else if((f=fopen(fileout,"w+b")) == NULL){
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
  //quet du lieu vao mang dong
  for(i=0;i<sosv;i++){
    fscanf(fin,"%s",(sinhvien+i)->stt);
    fscanf(fin,"%s",(sinhvien+i)->MSSV);
    fscanf(fin,"%s",(sinhvien+i)->name);
    fscanf(fin,"%f",&(sinhvien+i)->diem);
  }
  //ghi diem ra file dat
   fwrite(sinhvien,sizeof(dulieu),sosv,f);
  //giai phong bo nho
  free(sinhvien);
  rewind(fin);
  rewind(f);
    //cap phat moi
   sinhvien = (dulieu *)malloc(sosv * sizeof(dulieu));
   //doc tu file dat
   fread(sinhvien,sizeof(dulieu),sosv,f);
   for(i=0;i<sosv;i++){
     printf("%s\t%s\t%-25s\t%f\n",(sinhvien+i)->stt,(sinhvien+i)->MSSV,(sinhvien+i)->name,(sinhvien+i)->diem);
  }
  //giai phong bo nho lan nua
   free(sinhvien);
   //dong file
   fclose(f);
   fclose(fin);
   return 0;
}
