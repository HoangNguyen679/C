/* Nguyen Duc Hoang - 9A */
// Date Create:9/3/2015
#include<stdio.h>
main()
{
  char stt[3],date[10],lop[4],sub[30],start[6],end[6];
  printf("Nhap so thu tu: ");
  gets(stt);
  printf("Nhap ngay thang: ");
  gets(date);
  printf("Nhap ten lop: ");
  gets(lop);
  printf("Nhap ten mon hoc: ");
  gets(sub);
  printf("Nhap thoi gian bat dau muon: ");
  gets(start);
  printf("Nhap thoi gian ket thuc: ");
  gets(end);
  printf(" STT\tNgay thang\tTen lop\t\t %-20s\tBat dau\t Ket thuc\n","Ten mon hoc");
  printf(" %-3s\t%-10s\t%-3s\t\t %-20s\t%-5s\t %-5s \n ",stt,date,lop,sub,start,end);
}
