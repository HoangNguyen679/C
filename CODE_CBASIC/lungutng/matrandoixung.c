#include<stdio.h>
#define SIZE 8
void kiemtradx(int a[SIZE][SIZE], int hang,int cot)
{
	int i,j,t;
	for (i=0;i<hang;i++)
	for (j=0;j<cot;j++){
		if (i!=j && a[i][j]==a[j][i]) t=1;
		else if (i==j) t=1;
		else {
			t=0;
			break;
		}
	}
	if (t==0) printf("Ma tran khong doi xung\n");
	else printf("Ma tran doi xung\n");
}
void nhapMang(int a[SIZE][SIZE],int hang, int cot)
{
	int i,j;
	for (i=0;i<hang;i++)
	for (j=0;j<cot;j++){
		printf("Nhap vao phan tu hang %d cot %d: ",i+1,j+1);
		scanf("%d",&a[i][j]);
	}
}
void inMang(int a[SIZE][SIZE],int hang, int cot)
{
	int i,j;
	for (i=0;i<hang;i++){
		for (j=0;j<cot;j++)
			printf("%d\t",a[i][j]);
		printf("\n\n");
	}
}
int main()
{
	int a[SIZE][SIZE];
	int n;
	printf("Nhap kich co cua mang (n<=8): ");
	scanf("%d",&n);
	printf("Nhap vao mang A: \n");
	nhapMang(a,n,n);
	inMang(a,n,n);
	kiemtradx(a,n,n);
	return 0;
}

