#include<stdio.h>
#define MAX 40
#define TIEN 750
main()
{


	int may[MAX],phu[MAX],DIEN=400;
	int chon,i,somay,tongtien,tongdien,tiendien;
	for (i=0;i<40;i++){
		may[i]=0;
		phu[i]=0;
	}
	do {
		printf("MENU\n");
		printf("1. Dung may\n");
		printf("2. Roi may\n");
		printf("3. Trang thai may\n");
		printf("4. Dien nang tieu thu tich luy\n");
		printf("5. Tong dien nang - Tien thanh toan\n");
		printf("6. May dung nhieu nhat, it nhat\n");
		printf("7. Thoat\n\n");
		printf("Nhap vao lua chon cua ban: ");scanf("%d",&chon);
		switch (chon) {
			case 1: {
				printf("Nhap vao so hieu may muon dung: ");
				scanf("%d",&somay);
				if (may[somay-1]==0) {
					printf("Ban duoc su dung may %d\n",somay);
					may[somay-1]=1;
					phu[somay-1]+=1;
				}
				else printf("May %d da duoc chon, moi ban chon may khac.\n\n",somay);
			} break;
			case 2: {
				printf("Nhap vao so hieu may dung xong: ");
				scanf("%d",&somay);
				may[somay-1]=0;
			} break;
			case 3: {
				printf("Trang thai cac may:\n");
				for (i=1;i<=40;i++) {
						if (may[i-1]==0) printf("May %d - tat \n",i);
						else printf("May %d - dang hoat dong \n",i);
				}
			} break;
			case 4: {
				//printf("Dien nag tieu thu tich luy tren cac may:\n");
				for (i=0;i<40;i++) {
					tiendien=DIEN*phu[i];
					printf("May %d - %d \n",i+1,tiendien);
				}
			} break;
			case 5:{
				for (i=0;i<40;i++)
					tongdien+=DIEN*phu[i];
				tongtien=TIEN*tongdien;
				printf("Tong dien nang la %d \n",tongdien);
				printf("Tongso tien phai thanh toan la %d \n",tongtien);
			} break;
			case 6: {
				int max,min,xmax,xmin;
				max=min=phu[0];
				for (i=1;i<40;i++){
					if (phu[i]>max) {max=phu[i];xmax=i;}
					if (phu[i]<min) {min=phu[i];xmin=i;}
				}
	
				printf("May %d duoc dung nhieu nhat \n",xmax+1);
				printf("May %d duoc dung it nhat \n",xmin+1);
			} break;
			case 7: printf("Hen gap lai !\n"); break;
		}
		if (chon==7) break;
	}
	while (1);
	return 0;
}