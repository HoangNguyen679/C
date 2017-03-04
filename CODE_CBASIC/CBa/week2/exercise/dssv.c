/* Nguyen Duc Hoang - 9A */
// Date Create: 29/8/2015
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 81
enum {SUCCESS,FAIL};
typedef struct {
  char STT[3];
  char MSSV[10];
  char hoTen[30];
  char SDT[13];
  float diem;
} dulieu;
int main(){
  dulieu sinhVien[45];
  int reval=SUCCESS;
  FILE *fin;
  char filename[]="dslop.txt";
  if((fin=fopen(filename,"r")) == NULL){
    printf("Cannot open %s\n",filename);
    reval = FAIL;
  }
   int i;
   for(i=0;i<41;i++ ){
     fscanf(fin,"%s%s%s",&sinhVien[i].STT,&sinhVien[i].MSSV,&sinhVien[i].hoTen);
     sinhVien[i].diem=-0;
   }
   for(i=0;i<10;i++){
     printf("%s ",sinhVien[i].STT);
     printf("%s ",sinhVien[i].MSSV);
     printf("%s ",sinhVien[i].hoTen);
     printf("\n");
   }
   FILE *fout;
   char filenameout[]="bangdiem.txt";
   if((fout=fopen(filenameout,"w")) == NULL){
    printf("Cannot open %s\n",filename);
    reval = FAIL;
  }

   int chon;
   char stt[3];
   do{
     printf("MENU\n");
     printf("1.Nhap diem tung sinh vien\n");
     printf("2.Exit\n");
     scanf("%d",&chon);getchar();
     if(chon==2) break;
     if(chon==1){
       printf("Nhap so thu tu sinh vien:");
       gets(stt);
       for(i=0;i<41;i++){
         if(strcmp(stt,sinhVien[i].STT) == 0){
     printf("%s %s %s :",sinhVien[i].STT,sinhVien[i].MSSV,sinhVien[i].hoTen);
     scanf("%g",&sinhVien[i].diem);
         }
       }
     }
   }while(1);
   for(i=0;i<41;i++) fprintf(fout,"%s %s %s %g\n",sinhVien[i].STT,sinhVien[i].MSSV,sinhVien[i].hoTen,sinhVien[i].diem);

   /*
   printf("Nhap diem\n");
   for(i=0;i<3;i++){
     printf("%s %s %s :",sinhVien[i].STT,sinhVien[i].MSSV,sinhVien[i].hoTen);
     scanf("%f",&sinhVien[i].diem);
   }
    for(i=0;i<41;i++) fprintf(fout,"%s %s %s %3f\n",sinhVien[i].STT,sinhVien[i].MSSV,sinhVien[i].hoTen,sinhVien[i].diem);
    */
   fclose(fin);
   fclose(fout);
   return reval;
}
