#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct SanPham {
  int maSP;
  char ten[30];
  int gia;
  int soluong;
} elementType;

#include "SLLLib.h"

node *root;


void Import(void);
int Input();
int TinhTongTien(void);
void SortList();
int DemCungGia(void);
int DemCungTen(void);

int main(int argc, char **argv) {
  Input();
  Import();
  TraverseList();
  printf("Sort:\n");
  SortList();
  TraverseList();
  printf("\nTong So Tien: %d\n", TinhTongTien());
  printf("So nhom cung gia: %d\n", DemCungGia());
  printf("So SP cung ten:\n");
  DemCungTen();
  FreeAllList();
  return 0;
}

int Input(){
  FILE *f = fopen("sanpham.txt", "a+");
  if (f == NULL) {perror("ERROR"); return 0;}
  elementType temp;
  printf("MaSP: "); scanf("%d", &temp.maSP);
  int pre = temp.maSP-1;
  while(temp.maSP != 0) {
    while(temp.maSP <= pre) {
      printf("MaSP: "); scanf("%d", &temp.maSP); 
      if(temp.maSP == 0) return;
    } 
    pre = temp.maSP;
    printf("TenSP: "); clrBuff(); gets(temp.ten);
    do {printf("GiaSP: "); scanf("%d", &temp.gia);} while(temp.gia <= 0);
    do {printf("Soluong: "); scanf("%d", &temp.soluong);} while(temp.soluong < 0);
    printf("\n");
    fprintf(f, "<%d> <%d> <%d> <%s>\n", temp.maSP, temp.gia, temp.soluong, temp.ten);
  }  
  fclose(f);
}

void Import(void){
  FILE *f = fopen("sanpham.txt", "r");
  if (f == NULL) {perror("ERROR"); return;}
  elementType temp;
  while (fscanf(f, "<%d> <%d> <%d> <%[A-Za-z0-9 ]s", &temp.maSP, &temp.gia, &temp.soluong, temp.ten) == 4) {
    InsertAfterCurrent(temp);
    fscanf(f, ">\n");
  }
  fclose(f);
}

void PrintData(elementType *e){
  printf("<%p> <%d> <%d> <%d> <%s>\n", e, e->maSP, e->gia, e->soluong, e->ten);
}


int TinhTongTien(void){
  node *p;
  int tong = 0;
  if (root == NULL){ printf("List is empty!\n"); return 0;}
  for(p = root; p != NULL; p = p->next){
    tong += p->element.gia * p->element.soluong;
  }
  return tong;
}

void SortList() {
  node *p, *q;
  elementType temp;
  for(p = root; p != NULL; p = p->next){
    for(q = p->next; q != NULL; q = q->next){
      if (p->element.gia > q->element.gia) {
	temp = q->element;
	q->element = p->element;
	p->element = temp;
      }
    }
  }
}


int DemCungGia(void) {
  node *p, *q;
  int count = 0, nhomcunggia = 0;
  elementType temp;
  if (root == NULL) return 0;
  for(p = root; p->next != NULL; p = p->next){
    while (p->element.gia == p->next->element.gia) {
      p = p->next;
      count++;
    }
    if(count > 0) nhomcunggia++;
    count = 0;
  }
  return nhomcunggia;
}

int DemCungTen(void) {
  node *p, *q;
  int count = 0, nhomcungten = 0;
  elementType temp;
  if (root == NULL) return 0;
  for(p = root; p != NULL; p = p->next){
    while (p->next!= NULL&& strcmp(p->element.ten,p->next->element.ten)==0) {
      PrintData(&(p->element));
      if (p->next != NULL)p = p->next;
      count++;
    }
    if(count > 0) PrintData(&(p->element));
    count = 0;
  }
}

