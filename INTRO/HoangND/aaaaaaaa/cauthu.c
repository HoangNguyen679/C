#include<stdio.h>
#define CAUTHU 11
#define CHUYENGIA 5
int main()
{
	int soao[11],chuyengia[5];
	float diem[11][5],tb[11];
	int i,j,k;
	for (i = 0;i < CAUTHU;i++) {
		printf("So ao: ");scanf("%d",&soao[i]);
		printf("Diem cua moi chuyen gia\n");
		for ( j = 0 ; j < 5 ; j++ ) {
			printf("Chuyen gia %d:", j+1);scanf("%f",&diem[i][j]);
			tb[i]+=diem[i][j];
		}
		tb[i] = tb[i]/5;
	}
	for (i = 0;i < CAUTHU; i++) {
		printf("So ao: %d\tDiem: %.0f \n",soao[i],tb[i]);
	}
	for (j=0;j<5;j++) {
		for (i=0;i<11;i++) {
			chuyengia[j]+=diem[i][j];
		}
		chuyengia[j]/=11;
	}
	int max,min,maxi=0,mini=0;
	max=min=chuyengia[0];
	for (i=1;i<5;i++) {
		if (chuyengia[i]>max) {
			max=chuyengia[i];
			maxi=i;
		}
		if (chuyengia[i]<min) {
			min=chuyengia[i];
			mini=i;
		}
	}
	printf("Chuyen gia %d kho tinh vai! \n",mini+1);
	printf("Chuyen gia %d rat tot bung :v\n",maxi+1);
}