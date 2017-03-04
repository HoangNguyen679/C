/* Nguyen Duc Hoang - 9A */
// Date Create:
#include <stdio.h>
#include <string.h>
struct{
char ht[30];
int mau, cot,diem;
}nguoichoi[4];
int b,a[5][3]={{0,1,2},
               {2,1,0},
               {1,2,0},
                {0,2,1},
                {2,1,0}
                };
int i,j;
void hoanvi(int *a,int *b)
{
    int k;
    k=*a;
    *a=*b;
    *b=k;
}
void in()
{
    for(i=0;i<5;i++)
        for(j=0;j<3;j++)
    {
        if(a[i][j]==0) printf("xanh ");
        else if(a[i][j]==1) printf("do   ");
        else if(a[i][j]==2) printf("vang ");
        if(j==2) printf("\n");
    }
}
void doi()
{
int mau;
int *w,*u,*k;
do{
printf("nhap toa do can doi(hang cot): ");
scanf("%d %d",&i,&j);
}while(i<0 || i>5 || j<0|| j>3);
w=&a[i-1][j-1];
if(j-1==0) {u=&a[i-1][j];k=&a[i-1][j+1];}
else if(j-1==1){u=&a[i-1][j-2];k=&a[i-1][j];}
else{u=&a[i-1][j-3];k=&a[i-1][j-2];}
printf("nhap mau:"); scanf("%d",&mau);
if(*u==mau) hoanvi(u,w);
else if(*k==mau) hoanvi(k,w);
in();
}
void choi()
{
    int luot;
    for(i=0;i<5;i++)
    {
        getchar();
        nguoichoi[i].diem=0;
        printf("nhap hoc ten nguoi choi thu %d:",i+1); gets(nguoichoi[i].ht);
        for(j=0;j<strlen(nguoichoi[i].ht);j++)
        {
            if(nguoichoi[i].ht[0]<=122 && nguoichoi[i].ht[0]>=97)
                        nguoichoi[i].ht[0]-=32;
            if(nguoichoi[i].ht[j]==' ')
                {
                    if(nguoichoi[i].ht[j+1]<=122 && nguoichoi[i].ht[j+1]>=97)
                        nguoichoi[i].ht[j+1]-=32;

                }
        }
        printf("lua chon mau:"); scanf("%d",&nguoichoi[i].mau);
        for(luot=0;luot<5;luot++)
        {
            printf("luot %d chon o:",luot+1);scanf("%d",&nguoichoi[i].cot);
            if(a[luot][nguoichoi[i].cot-1]==nguoichoi[i].mau) nguoichoi[i].diem+=1;
            else break;
        }

    }

}
void ketqua()
{
    printf("luot Ho va Ten                      Diem\n");
for(i=0;i<5;i++)
    printf("%d   %-30s  %d\n",i,nguoichoi[i].ht,nguoichoi[i].diem);
    int max=1,min=1;
    for(i=0;i<5;i++)
    {
        if(nguoichoi[max].diem<nguoichoi[i].diem)
            max=i;
        if(nguoichoi[min].diem>nguoichoi[i].diem)
            min=i;
    }
    printf("\nnguoi choi tot nhat la:%s, nguoi choi cui nhat la %s",nguoichoi[max].ht,nguoichoi[min].ht);

}
int main()
{
    char ch,a;
    printf("----------MENU------------");
    while(1){
    printf("\n1.in o mau \n 2.doi o mau \n 3. bat dau choi \n 4. ket qua \n");
    ch=getchar();
    if (ch=='1') in();
    else if(ch=='2') doi();
    else if(ch=='3') choi();
    else if(ch=='4') ketqua();
    else {
        getchar();
        printf("thoat? Y/N?");
        a=getchar();
        if(a=='y'||a=='Y') break;
    }
    getchar();
    }
    return 0;
}
