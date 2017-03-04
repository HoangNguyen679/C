/* Nguyen Duc Hoang - 9A */
// Date Create:9/3/2015
#include<stdio.h>
main()
{
  int d,m,y,stt;
  char lop[4],sub[30],start[6],end[6];
  printf("Nhap so thu tu: ");
  scanf("%d",&stt);
  printf("Nhap ngay thang: ");
  scanf("%d%*c%d%*c%d",&d,&m,&y);
  printf("Nhap ten lop: ");
  getchar(); 
  gets(lop);
  printf("Nhap ten mon hoc: "); 
  gets(sub);
  printf("Nhap thoi gian bat dau muon: ");
  gets(start);
  printf("Nhap thoi gian ket thuc: ");
  gets(end);
  printf(" STT\tNgay thang\tTen lop\t\t %-20s\tBat dau\t Ket thuc\n","Ten mon hoc");
  printf(" %-3d\t%-2d\%-2d\%-2d\t%-3s\t\t %-20s\t%-5s\t %-5s \n ",stt,d,m,y,lop,sub,start,end);
}
