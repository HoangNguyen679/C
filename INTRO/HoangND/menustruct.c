/* Nguyen Duc Hoang - 9A */
// Date Create:29/3/2015
#include<stdio.h>
#include<string.h>
#define MAX 100
void clear_buffer() {
  int ch;
  while ((ch=getchar()) != '\n' && ch != EOF );
}
typedef struct {
  char ten[30];
  int ngaynamvien;
  int tienthuoc;
  char baohiem;
  char phauthuat;
  int tienphauthuat;
  int tongtien;
  int tienduocgiam;
  int money;
}data;
main() {
  data benhnhan[MAX];
  int q,i,f,j;
  int tien=0;
  int g=0,s=0,c=0;
  while(1) {
      printf("Menu\n");
      printf("1. Nhap du lieu/phieu cho benh nhan moi\n");
      printf("2. In bao cao tong ket\n");
      printf("3. Thoat\n\n");
      printf("Nhap lua chon (1,2 hoac 3):");
      scanf("%d",&q);clear_buffer();
      if (q==1)
        {
          printf("Benh nhan %d \n",i+1);
           const int phi=15000;
           printf("Nhap ten benh nhan: ");
           gets(benhnhan[i].ten);
           printf("So ngay nam vien la: ");
           scanf("%d",&benhnhan[i].ngaynamvien);
           printf("Tien thuoc la: ");
           scanf("%d",&benhnhan[i].tienthuoc);clear_buffer();
           printf("Phau thuat (Neu co nhap C, neu khong nhap K): \n");
           benhnhan[i].phauthuat=getchar();
           switch(benhnhan[i].phauthuat){
           case 'C': printf("Nhap vao tien phau thuat: ");scanf("%d",&benhnhan[i].tienphauthuat);break;
           case 'K':benhnhan[i].tienphauthuat=0;clear_buffer();break;
  }
           printf("Nhap vao loai the bao hiem:\nG voi Gold || S voi Silver || C voi Citizen:");
           benhnhan[i].baohiem=getchar();
           switch(benhnhan[i].baohiem){
           case 'G': f=70;g++;break;
           case 'S': f=50;s++;break;
           case 'C': f=30;c++;break;
  }
           printf("HOA DON THANH TOAN VIEN PHI\n\n");
           printf("Benh nhan: %s\n",benhnhan[i].ten);
           printf("Phi noi tru: %d x %d = %d (VND)\n",benhnhan[i].ngaynamvien,phi,benhnhan[i].ngaynamvien*phi);
           printf("Tien thuoc: %d (VND)\n",benhnhan[i].tienthuoc);
           printf("Tien phau thuat: %d (VND)\n",benhnhan[i].tienphauthuat);
           printf("Loai the bao hiem: %c\n",benhnhan[i].baohiem);
           benhnhan[i].tongtien=benhnhan[i].ngaynamvien*phi + benhnhan[i].tienthuoc + benhnhan[i].tienphauthuat;
           printf("Tong tien: %d (VND)\n",benhnhan[i].tongtien);
           printf("Tien duoc bao hiem: %d x %d%% = %d (VND)\n",benhnhan[i].tongtien,f,benhnhan[i].tongtien*f/100);
           benhnhan[i].money = benhnhan[i].tongtien * (1 - f/100 );
           benhnhan[i].tienduocgiam = benhnhan[i].tongtien * f/100;
           printf("TIEN THANH TOAN (VND): %d (VND)\n",benhnhan[i].tongtien*(1-f/100));
           printf("\n\n");i++;
           continue;
        }
      if (q==2)
        {
          printf("BAO CAO TONG KET \n\n");
          printf("So benh nhan da thanh toan: %d\n",i);
          for(j=0;j<i;j++) tien+=benhnhan[j].money;
          printf("Muc phi trung binh phai thanh toan %d\n",tien/i);
          printf("So luong moi loai bao hiem:\n");
          printf("Loai Golden: %d\n",g);
          printf("Loai Silver: %d\n",s);
          printf("Loai Citizen: %d\n",c);printf("\n\n");
          continue;
        }
      if (q==3) break;
    }
  return 0;
}
