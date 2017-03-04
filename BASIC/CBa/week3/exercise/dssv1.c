/* Nguyen Duc Hoang - 9A */
// Date Create: 29/8/2015
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 81
enum {SUCCESS,FAIL};
typedef struct {
  char *STT;
  char *MSSV;
  char *hoTen;
  char *SDT;
  float diem;
} dulieu;
int main(){
  dulieu *sinhvien;
  int n=0;
  int reval=SUCCESS;
  FILE *fin;
  char *filename="dslop.txt";
  if((fin=fopen(filename,"r")) == NULL){
    printf("Cannot open %s\n",filename);
    reval = FAIL;
  }
  char *str;
  while((fgets(str,MAX,fin)) != NULL) ++n;n--;
  printf("%d\n",n);rewind(fin);
  sinhvien = (dulieu *)malloc(n * sizeof(dulieu));
  if(sinhvien == NULL){
    printf("Memory allocation failed\n");
    return 1;
  }
   int i;
   for(i=0;i<n;i++ ){
     (sinhvien+i)->STT = (char *)malloc(3);
     (sinhvien+i)->MSSV = (char *)malloc(9);
     (sinhvien+i)->hoTen = (char *)malloc(25);

     fscanf(fin,"%s%s%s",(sinhvien+i)->STT,(sinhvien+i)->MSSV,(sinhvien+i)->hoTen);
     (sinhvien+i)->diem=-0;
   }
   for(i=0;i<n;i++){
     printf("%s ",(sinhvien+i)->STT);
     printf("%s ",(sinhvien+i)->MSSV);
     printf("%s ",(sinhvien+i)->hoTen);
     printf("\n");
   }
   FILE *fout;
   char *filenameout="bangdiem.txt";
   if((fout=fopen(filenameout,"w")) == NULL){
    printf("Cannot open %s\n",filename);
    reval = FAIL;
  }
   printf("Nhap diem\n");
   for(i=0;i<n;i++){
     printf("%s %s %s :",(sinhvien+i)->STT,(sinhvien+i)->MSSV,(sinhvien+i)->hoTen);
     scanf("%f",&(sinhvien+i)->diem);
   }
   for(i=0;i<n;i++) fprintf(fout,"%s %s %s %3f\n",(sinhvien+i)->STT,(sinhvien+i)->MSSV,(sinhvien+i)->hoTen,(sinhvien+i)->diem);

   /*
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
         if(strcmp(stt,(sinhvien+i)->STT) == 0){
     printf("%s %s %s :",(sinhvien+i)->STT,(sinhvien+i)->MSSV,(sinhvien+i)->hoTen);
     scanf("%g",&(sinhvien+i)->diem);
         }
       }
     }
   }while(1);
   for(i=0;i<41;i++) fprintf(fout,"%s %s %s %g\n",(sinhvien+i)->STT,(sinhvien+i)->MSSV,(sinhvien+i)->hoTen,(sinhvien+i)->diem);
*/

    for(i=0;i<n;i++ ){
      free((sinhvien+i)->STT);
      free((sinhvien+i)->MSSV);
      free((sinhvien+i)->hoTen);

    }
    free(sinhvien);
   fclose(fin);
   fclose(fout);
   return reval;
}
