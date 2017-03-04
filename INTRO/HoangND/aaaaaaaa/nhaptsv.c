/* Nguyen Duc Hoang - 9A */
// Date Create:9/3/2015
#include<stdio.h>
main()
{
  int mssv,d,m,y;
  char name[20],sex[5],home[100];
  printf("Nhap ten sinh vien: ");
  gets(name);
  printf("Nhap ngay sinh: ");
  scanf("%d%*c%d%*c%d",&d,&m,&y);
  printf("Nhap ma so sinh vien: ");
  scanf("%d",&mssv);getchar();
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
	printf("|  |''''''''| MSSV: %-8d      Lop: Viet Nhat A       |\n",mssv);
	printf("|  |        | Ho ten: %-20s               |\n",name);
	printf("|  |        | Ngay sinh: %-2d/%-2d/%-2d        %-3s           |\n",d,m,y,sex);
	printf("|  |        | Ho khau: %-30s    |\n",home);
	printf("|  |        | Nhom nganh: Cong nghe thong tin            |\n");
	printf("|  '''''''''' Khoa hoc: K59   Co gia tri den: 30/05/2019 |\n");
    printf("|                                                        |\n");
	printf("|  NPH: 01/10/2014                                       |\n");
	printf("|________________________________________________________|\n");
}
