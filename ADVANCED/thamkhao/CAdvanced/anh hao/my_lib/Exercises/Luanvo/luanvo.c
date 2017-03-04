#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

typedef struct Dausi_t{
  char biethieu[MAX];
  int mau;
  int tancong;
  int nhanhnhen;
  int phongthu;
  int diemso;
} ElementType;

#include "QueueLLLib.h"
#include "SortAlgo.c"

QueueType MonPhai1; int sodausi1 = 0;
QueueType MonPhai2; int sodausi2 = 0;
ElementType dsachDauSi[100]; int tongsodausi=0;

int GetMenu(void);
int ImportFile(char *fileName, QueueType *Q);
int Thidau(ElementType *dausi1, ElementType *dausi2);
void XepHang();

int main() {
  int menu, sotrandau=1;
  ElementType *dausi1, *dausi2;
  dausi1 = (ElementType*)malloc(sizeof(ElementType));
  dausi2 = (ElementType*)malloc(sizeof(ElementType));
  dausi1->mau =0; dausi2->mau = 0;

  do{
    switch(menu = GetMenu()){
    case 1: 
      printf("Mon Phai 1:\n"); 
      sodausi1 = ImportFile("monphai1.txt", &MonPhai1);
      if (sodausi1 == 0) break;
      printf("Mon Phai 2:\n");
      sodausi2 = ImportFile("monphai2.txt", &MonPhai2);
      if (sodausi2 == 0) break;
      if (sodausi1 != sodausi2) {
        printf("Luc luong khong can bang. Yeu cau sua lai file\n");
        return 0;
      }
      break;

    case 2: 
      while (!IsEmpty(&MonPhai1) && !IsEmpty(&MonPhai2)){
        printf("Tran %d: \n", sotrandau);
        dausi1 = &(MonPhai1.front->element);
        dausi2 = &(MonPhai2.front->element);
        int isKnockout = Thidau(dausi1, dausi2);
        if (dausi1->mau <= 0) {
          if (isKnockout == 1 || isKnockout == 2) {
            printf("%s ha knock out %s\n", dausi2->biethieu, dausi1->biethieu);       
            dausi2->diemso += 2;
          }
          dsachDauSi[tongsodausi++] = *dausi1;
          *dausi1 = DeQueue(&MonPhai1);
        }
        if (dausi2->mau <= 0) {
          if (isKnockout == 1 || isKnockout == 2) {
            printf("%s ha knock out %s\n", dausi1->biethieu, dausi2->biethieu);  
            dausi1->diemso += 2;
          }
          dsachDauSi[tongsodausi++] = *dausi2;
          *dausi2 = DeQueue(&MonPhai2);
        }
        sotrandau++;
        printf("\n");
      }
      if (dausi1->mau <= 0) {dsachDauSi[tongsodausi++] = *dausi2;}
      if (dausi2->mau <= 0) {dsachDauSi[tongsodausi++] = *dausi1;}
      break;
    case 3: XepHang(); break;
    case 0: break;
    default: printf("Invalid Option\n"); break;
    }
  } while (menu != 0);
  return 0;
}

int GetMenu(void){
  int menuOption = 0;
  //do {
  printf("\n\n---GAME MENU---\n");
  printf("1. Import File\n");
  printf("2. Thi dau\n");
  printf("3. Xep Hang\n");
  printf("0. Exit\n");
  printf("Your Choice: ");
  scanf("%d", &menuOption);
  //} while(menuOption < 0 || menuOption > 3);
  return menuOption;
}

int ImportFile(char *fileName, QueueType *Q){
  FILE *f;
  f = fopen(fileName, "r");
  if (f == NULL) {
    printf("Khong tim thay file\n");
    return 0;
  }

  int sodausi = 0;
  ElementType temp;
  InitQueue(Q);
  while (!feof(f)){
    fscanf(f, "%s", temp.biethieu); if(temp.biethieu[0] == '\0') break;
    if (fscanf(f, "%d", &temp.mau) == 0) break;;
    fscanf(f, "%d", &temp.tancong);
    fscanf(f, "%d", &temp.nhanhnhen);
    fscanf(f, "%d", &temp.phongthu);
    printf("%2d | %-10s%-5d%-5d%-5d%-5d\n",sodausi+1, temp.biethieu, temp.mau, temp.tancong, temp.nhanhnhen, temp.phongthu);
    if (temp.mau < 0 || temp.tancong < 0 || temp.nhanhnhen <0 || temp.phongthu < 0) {
      printf("So lieu khong hop le\n");
      return 0;
    }
    temp.diemso = 0;
    EnQueue(temp, Q);
    sodausi++;
    temp.biethieu[0] = '\0';
  }
  return sodausi;
}

int Thidau(ElementType *dausi1, ElementType *dausi2){
  int trumau, count = 0;
  if (dausi1->nhanhnhen >= dausi2->nhanhnhen){
    while (1) {
      if(dausi1->mau <= 0) {
        printf("===> %s bi loai\n", dausi1->biethieu);
        dausi2->diemso++;
        return count;
      }
      trumau = dausi1->tancong - dausi2->phongthu;
      count++;
      if (trumau > 0){
        dausi2->mau -= trumau;
      } else trumau = 0;
      printf("\t%s(%d) - %s(%d) mat %d mau\n", dausi1->biethieu, dausi1->mau, dausi2->biethieu, dausi2->mau+trumau, trumau); 

      if(dausi2->mau <= 0) {
        printf("===> %s bi loai\n", dausi2->biethieu);
        dausi1->diemso++;
        return count;
      }
      trumau = dausi2->tancong - dausi1->phongthu;
      count++;
      if (trumau > 0){
        dausi1->mau -= trumau;
      } else trumau = 0;
      printf("\t%s(%d) - %s(%d) mat %d mau\n", dausi2->biethieu, dausi2->mau, dausi1->biethieu, dausi1->mau+trumau, trumau); 
    }
  }

  else {
    while (1) {    
      if(dausi2->mau <= 0) {
        printf("===> %s bi loai\n", dausi2->biethieu);
        dausi1->diemso++;
        return count;
      }
      trumau = dausi2->tancong - dausi1->phongthu;
      count++;
      if (trumau > 0){
        dausi1->mau -= trumau;
      } else trumau = 0;
      printf("\t%s(%d) - %s(%d) mat %d mau\n", dausi2->biethieu, dausi2->mau, dausi1->biethieu, dausi1->mau+trumau, trumau); 


      if(dausi1->mau <= 0) {
        printf("===> %s bi loai\n", dausi1->biethieu);
        dausi2->diemso++;
        return count;
      }
      trumau = dausi1->tancong - dausi2->phongthu;
      count++;
      if (trumau > 0){
        dausi2->mau -= trumau;
      } else trumau = 0;
      printf("\t%s(%d) - %s(%d) mat %d mau\n", dausi1->biethieu, dausi1->mau, dausi2->biethieu, dausi2->mau+trumau, trumau); 

    }
  }
}

void XepHang() { 
  int i;
  MergeSort(dsachDauSi, 0, tongsodausi-1);
  for(i = 0; i < tongsodausi; i++){
    printf("%2d | %-10s%-5d\n", i+1, dsachDauSi[i].biethieu, dsachDauSi[i].diemso);
  }
}