#include<stdio.h>
#define CAUTHU 11
#define CHUYENGIA 5
int main()
{
    FILE *f=fopen("VD.txt","r");
	int soao[11];
	double tb[11], diem[5];
	for(int i = 0; i< 5; i++){
		diem[i]=0;
	}
	for (int i = 0; i < 11; i++)
	{
		tb[i]=0;
		printf("Nhap vao so ao :"); fscanf(f,"%d",&soao[i]);
		double t;
		printf("Nhap so diem: ");
		for (int j = 0; j < 5; j++)
		{
			fscanf(f,"%lf",&t);
			diem[j] += t;
			tb[i] += t;
		}
		tb[i]/=5;
	}
	double max=diem[0],min=diem[0];
	int maxi=0,mini=0;
	for(int i = 1;i < 5; i++){
		if(diem[i]>max){
			max = diem[i];
			maxi = i;
		}
		if(diem[i] < min){
			min = diem[i];
			mini = i;
		}
	}
	for(int i = 0; i < 11; i++){
		printf("\n Cau thu so %d: %.1lf",soao[i],tb[i]);
	}
	printf("\n Chuyen gia thu %d kho tinh vl!",mini+1);
	printf("\n Chuyen gia thu %d de tinh vai!",maxi+1);
}
