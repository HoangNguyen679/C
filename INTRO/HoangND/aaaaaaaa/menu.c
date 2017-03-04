/* Nguyen Duc Hoang - 9A */
// Date Create:29/3/2015
#include<stdio.h>
int main()
{
  int q,i,j,g=0,s=0,c=0,dem=0,money;
  for(;;)
    {
      printf("Menu\n");
      printf("1. Input data/Bill for new patient\n");
      printf("2. Printf the total report\n");
      printf("3. Quit\n\n");
      printf("Nhap lua chon (1,2 hoac 3):");
      scanf("%d",&q);getchar();
      if (q==1)
        {
          dem++;
  char na[20],b,p;
  int m,n,f,t,tp;
  const int phi=15000;
  printf("Nhap ten benh nhan: ");
  gets(na);
  printf("So ngay nam vien la: ");
  scanf("%d",&n);
  printf("Tien thuoc la: ");
  scanf("%d",&t);getchar();
  printf("Phau thuat (Neu co nhap C, neu khong nhap K): \n");
  p=getchar();
  switch(p){
  case 'C': printf("Nhap vao tien phau thuat: ");scanf("%d",&tp);getchar();break;
  case 'K':tp=0;getchar();break;
  }
  printf("Nhap vao loai the bao hiem:\nG voi Gold || S voi Silver || C voi Citizen:");
  b=getchar();
  switch(b){
  case 'G': f=70;g++;break;
  case 'S': f=50;s++;break;
  case 'C': f=30;c++;break;
  }
  printf("HOA DON THANH TOAN VIEN PHI\n\n");
  printf("Benh nhan: %s\n",na);
  printf("Phi noi tru: %d x %d = %d (VND)\n",n,phi,n*phi);
  printf("Tien thuoc: %d (VND)\n",t);
  printf("Tien phau thuat: %d (VND)\n",tp);
  printf("Loai the bao hiem: %c\n",b);
  m=n*phi+t+tp;
  printf("Tong tien: %d (VND)\n",m);
  printf("Tien duoc bao hiem: %d x %d%% = %d (VND)\n",m,f,m*f/100);
  printf("TIEN THANH TOAN (VND): %d (VND)\n",m-m*f/100);
  money+=(m-m*f/100);printf("\n\n");
  continue;
        }
      if (q==2)
        {
          printf("BAO CAO TONG KET \n\n");
          printf("So benh nhan da thanh toan: %d\n",dem);
          printf("Muc phi trung binh phai thanh toan %d\n",money/dem);
          printf("So luong mio loai bao hiem:\n");
          printf("Loai Golden: %d\n",g);
          printf("Loai Silver: %d\n",s);
          printf("Loai Citizen: %d\n",c);printf("\n\n");
          continue;
        }
      if (q==3) break;;
    }
  return 0;
}
