/* Nguyen Duc Hoang - 9A */
// Date Create:9/3/2015
#include<stdio.h>
main()
{
  char name[20],birth[10],MSSV[8],sex[5],home[100];
  printf("Nhap ten sinh vien: ");
  gets(name);
  printf("Nhap ngay sinh: ");
  gets(birth);
  printf("Nhap ma so sinh vien: ");
  gets(MSSV);
  printf("Nhap gioi tinh: ");
  gets(sex);
  printf("Nhap ho khau: ");
  gets(home);
  	printf("__________________________________________________________\n");
	printf("|                                                        |\n");
	printf("|           TRUONG DAI HOC BACH KHOA HA NOI              |\n");
	printf("|                  THE SINH VIEN                         |\n");
	printf("|________________________________________________________|\n");
	printf("|                                                        |\n");
	printf("|  |''''''''| MSSV: %-8s      Lop: Viet Nhat A       |\n",MSSV);
	printf("|  |        | Ho ten: %-20s               |\n",name);
	printf("|  |        | Ngay sinh: %-8s        %-3s           |\n",birth,sex);
	printf("|  |        | Ho khau: %-30s    |\n",home);
	printf("|  |        | Nhom nganh: Cong nghe thong tin            |\n");
	printf("|  '''''''''' Khoa hoc: K59   Co gia tri den: 30/05/2019 |\n");
    printf("|                                                        |\n");
	printf("|  NPH: 01/10/2014                                       |\n");
	printf("|________________________________________________________|\n");
}
