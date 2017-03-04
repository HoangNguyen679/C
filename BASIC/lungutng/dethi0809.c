/* Nguyen Duc Hoang - 9A */
// Date Create: 26/5/15
#include<stdio.h>
#include<string.h>
char* chinhten(char s[]) {
	int i=0;
	if(s[0] >=97 && s[0] <= 122) s[0]-=32;
	while (s[i] != '\0'){
		i++;
		if(s[i] == ' ') {
			if(s[i+1] >=97 && s[i+1] <= 122) s[i+1]-=32;
		}
	}
	return s;
}
void clear_buffer() {
	int ch;
	while ((ch=getchar()) != '\n' && ch != EOF);
}
main() {
	int t;
	int i,j; //case1
	int c,b,mau; //case2
    int *k;//case2
	char ten[4][30];//
	int chonmau[4];//
	int diem[4];//
	int o;//
	int dem=0;//case3
    int a[5][3]={{0,1,2},
				     {1,2,0},
				     {2,1,0},
				     {0,2,1},
				     {1,2,0}};
	do {
		printf("MENU\n");
		printf("1.Tao ma tran o mau\n");
		printf("2.Thay doi ma tran\n");
		printf("3.Thuc hien choi\n");
		printf("4.Ket qua\n\n");
		printf("5.Thoat\n");
		printf("Nhap vao lua chon: ");scanf("%d",&t);clear_buffer();
		switch(t){
		case 1: {
			for (i=0;i<5;i++) {
				for(j=0;j<3;j++) {
					switch(a[i][j] ){
					case 0: printf("%-10s\t","Xanh");break;
					case 1: printf("%-10s\t","Vang");break;
					case 2: printf("%-10s\t","Do");break;
					}
				}
				printf("\n\n");
			}
				 } break;
		case 2: {
			do{
				printf("Nhap hang cua o can doi mau (1 <= hang <= 5): ");
				scanf("%d",&c);clear_buffer();
				if (c<1 || c>5) printf("Nhap sai, nhap lai!\n");
			} while (c<1 || c>5);
			do {
				printf("Nhap vao cot can doi mau(1 <= cot <=3): ");
				scanf("%d",&b);clear_buffer();
				if (b<1 || b>3) printf("Nhap sai,nhap lai! \n");
			}while (b<1 || b>3);
			do {
				printf("Nhap mau moi cho o [%d][%d]: ",c,b);
				scanf("%d",&mau);
				if( mau<0 || mau >2 || mau == a[c-1][b-1])
					printf("Khong hop le, nhap lai!\n");
			}while ( mau<0 || mau >2 || mau == a[c-1][b-1]);
			for(j=0;j<3;j++) {
				if (a[c-1][j] == mau) {
                  a[c-1][j]=a[c-1][b-1];
                  a[c-1][b-1]=mau;
					break;
				}
			}
			for (i=0;i<5;i++) {
				for(j=0;j<3;j++) {
					switch(a[i][j] ){
					case 0: printf("%-10s\t","Xanh");break;
					case 1: printf("%-10s\t","Vang");break;
					case 2: printf("%-10s\t","Do");break;
					}
				}
				printf("\n\n");
			}
		} break;
		case 3: {
          for(i=0;i<5;i++) {
            for(j=0;j<3;j++) printf("%d\t",a[i][j]);
            printf("\n\n");
          }
			while(dem<4){
			printf("Nhap ten nguoi choi: ");gets(ten[dem]);
			chinhten(ten[dem]);
			do {
			printf("Ban chon mau: 0-xanh 1-vang 2-do: ");
			scanf("%d",&chonmau[dem]);clear_buffer();
			if(chonmau[dem]<0 || chonmau[dem]>2) printf("Nhap lai mau!\n");
			}while (chonmau[dem] <0 || chonmau[dem]>2);
			for (i=0;i<5;i++){
				printf("Hang %d :",i+1);
				do{
					printf("Nhap vao so o:");
					scanf("%d",&o);clear_buffer();
					if(o<1 || o>3) printf("Nhap lai!\n");
				}while(o<1 || o>3);
				if (chonmau[dem] == a[i][o-1]) continue;
				else break;
			}
			diem[dem]=i;
			dem++;
			}
            dem=0;
		} break;
		case 4: {
			for(dem =0;dem<4;dem++)
				printf("%d\t%30s\t%d\t%d\n",dem+1,ten[dem],chonmau[dem],diem[dem]);
		}break;
		}
		if (t==5) break;
	} while (1);
}
