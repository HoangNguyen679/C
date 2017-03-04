#include<stdio.h>
void nhapMang(int a[5][3], int hang, int cot)
{
    int i, j;
    for (i=0;i<5;i++)
    for (j=0;j<3;j++){
        printf("Nhap phan tu hang %d cot %d: \n");
        scanf("%d", &a[i][j]);
    }
}
void inMang(int a[5][3], int hang,  int cot)
{
    int i, j;
    for (i=0;i<5;i++){
    for (j=0;j<3;j++)
        printf("%5d\t",a[i][j]);
    printf("\n\n");
        }
}
main()
{
    int n, i , j;
    int a[5][3];
    const int gia1=10;
    const int gia2=20;
	const int gia3=15;	
    for (i=0;i<5;i++)
    	for (j=0;j<3;j++)
    		a[i][j]=1;
    inMang(a,5,3);
    do {
    printf("MENU\n");
    printf("1. Bat - Tat den theo hang\n");
    printf("2. Bat - Tat den theo cot\n");
    printf("3. Bat - Tat den theo vi tri\n");
    printf("4. Dien nang tieu thu hien thoi\n");
    printf("5. Thoat\n");
    printf("Nhap vao lua chon: ");scanf("%d",&n);
    if (n==5) break;
	switch (n) {
    	case 1: {
    		int hang;
    		printf("Nhap vao hang can bat - tat: ");scanf("%d",&hang);
    		for (j=0;j<3;j++){
    			if (a[hang-1][j]==0) a[hang-1][j]=1;
    			else a[hang-1][j]=0;
    		}
    		inMang(a,5,3);
			break;
		}
		case 2: {
			int cot;
			printf("Nhap vao cot can bat - tat: ");scanf("%d",&cot);
			for (i=0;i<5;i++){
				if (a[i][cot-1]==0) a[i][cot-1]=1;
				else a[i][cot-1]=0;
			}
			inMang(a,5,3);
			break;
		}
		case 3: {
			int hang,cot;
			printf("Nhao vao hang, cot can bat - tat:\n");scanf("%d%d",&hang,&cot);
			if (a[hang-1][cot-1]==0) a[hang-1][cot-1]=1;
			else a[hang-1][cot-1]=0;
			inMang(a,5,3);
			break;
		}
		case 4: {
			int b[5][3];
			for (i=0;i<5;i++)
			for (j=0;j<3;j++){
				if  (a[i][j]==0) b[i][j]=0;
				else {
					if (i % 2 == 1 && j % 2 == 1 ) b[i][j]=gia2;
					else if (i%2==0 && j%2==0 ) b[i][j]=gia1;
					else b[i][j]=gia3;
				}
			}
			inMang(b,5,3);
			break;
		}
	}
}
while(1);
    return 0;
}
