#include<stdio.h>
#define CHINH 25000
#define PHU 40000
#define CHUAN 40 
int  main()
{
 unsigned  int hlam;
 printf("Nhap vao so gio lam : ");
 scanf("%d",&hlam);
 if (hlam<CHUAN) printf(" Tien luong la %d \n",hlam*CHINH);
 else printf(" Tien luong la %d \n",(hlam-CHUAN)*PHU+CHUAN*CHINH);
 return 0;
}
