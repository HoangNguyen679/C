/* Nguyen Duc Hoang - 9A */
// Date Create: 2/6/15
#include<stdio.h>
#include<string.h>
#define MAX 10
void clear_buffer() {
	int ch;
	while((ch=getchar()) != '\n' && ch != EOF);
}
typedef struct {
	char  hoten[30];
	int diem[5];
} ketquathidau;
main() {
	ketquathidau vdv[MAX];
	int t,n; //t la lua chon, n la so van dong vien
	int i,j;
	while (1) {
		printf("MENU\n");
		printf("1.Dang ki van dong vien\n");
		printf("2.Thi dau\n");
		printf("3.Xep hang\n");
		printf("4.Sieu xa thu\n");
		printf("5.Thoat\n");
		printf("Nhap vao lua chon: ");scanf("%d",&t);clear_buffer;
		switch(t){
		case 1: {
			do {
				printf("Nhap vao so van dong vien(>0 va <11): ");
				scanf("%d",&n);clear_buffer();
				if (n < 1 || n>10 ) printf("Nhap loi, nhap lai\n");
			} while (n < 1 || n>10 );
			for(i=0;i<n;i++) {

					printf("Nhap ho ten: ");
					gets(vdv[i].hoten);

			}
			printf("STT\t Ho ten\n");
			for(i=0;i<n;i++)
				printf("%3d\t%s \n ",i,vdv[i].hoten);
		}break;
		case 2: {
			for(i=0;i<n;i++) {
				printf("Van dong vien \"%s\"",vdv[i].hoten);
				printf("Diem moi luot ban\n");
				for(j=0;j<5;j++){
					printf("Luot %d:",j+1);
					do {
						scanf("%d",&vdv[i].diem[j]);clear_buffer();
						if (vdv[i].diem[j] <0 || vdv[i].diem[j] >10)
							printf("Nhap lai\n");
					}while (vdv[i].diem[j] <0 || vdv[i].diem[j] >10);
				}
			}
			printf("%30s\t%d\t%d\t%d\t%d\t%d\n","hoten",1,2,3,4,5);
			for(i=0;i<n;i++) {
			printf("%30s\t%d\t%d\t%d\t%d\t%d\n",vdv[i].hoten,vdv[i].diem[0],vdv[i].diem[1],vdv[i].diem[2],vdv[i].diem[3],vdv[i].diem[4]);
			}
		}break;
		case 3: {
			int tongdiem[n];
			int max=0,imax=0,max1=0,max2=0,imax1=0,imax2=0;
			for(i=0;i<n;i++)
				for(j=0;j<5;j++){
					tongdiem[i]+=vdv[i].diem[j];
			}
			for (i=0;i<n;i++) {
				if (tongdiem[i]>max) {max=tongdiem[i];imax=i;}
			}
			printf("%s\t%s\t%d",vdv[imax].hoten,"GOLD",tongdiem[imax]);
			for (i=0;i<n;i++) {
				if (tongdiem[i]<max && tongdiem[i] >max1) {max1=tongdiem[i];imax1=i;}
			}
			printf("%s\t%s\t%d",vdv[imax1].hoten,"GOLD",tongdiem[imax1]);
			for (i=0;i<n;i++) {
				if (tongdiem[i]<max1 && tongdiem[i]>max2) {max2=tongdiem[i];imax2=i;}
			}
			printf("%s\t%s\t%d",vdv[imax2].hoten,"GOLD",tongdiem[imax2]);
		}break;
		case 4:{}break;
	     }
		if (t==5 ) break;
	}
}
