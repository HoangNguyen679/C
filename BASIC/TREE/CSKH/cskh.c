#include<stdio.h>
#include<stdlib.h>
#include "tree.h"
#define PRICE1 100
#define PRICE2 200
#define PRICE3 300
void menu()
{
  printf("MENU\n\n");
  printf("1. Doc tu file\n");
  printf("2. Them khach hang\n");
  printf("3. In thong tin theo thu tu truoc\n");
  printf("4. In thong tin theo thu tu giua\n");
  printf("5. In thong tin theo thu tu sau\n");
  printf("6. Xoa thong tin khach hang\n");
  printf("7. Tim kiem thong tin theo ID\n");
  printf("8. Ghi ra file\n");
  printf("9. Thoat\n");
  printf("Please select: ");
}
void docfile(node **tree, FILE *f)
{
  int i,num=0;
  customer_info *a;
   char str[MAX];
  while(fgets(str,MAX,f) != NULL) num++;
  rewind(f);
  a=(customer_info *)malloc(num*sizeof(customer_info));
  for(i=0;i<num;i++)
    {
      fscanf(f,"%s%s%d%d%d",a[i].mskh,a[i].ten,&a[i].food,&a[i].electronic,&a[i].cloth);
      a[i].tien =a[i].food*PRICE1 + a[i].electronic*PRICE2 + a[i].cloth*PRICE3;
     *tree = insert(*tree,a[i]);
    }
}
void themkh(node **tree)
{
  customer_info x;
  printf("Ma so khach hang cua ban la: ");scanf("%s",x.mskh);
  printf("Ten ban la :");scanf("%s",x.ten);
  printf("Chi phi ban da bo ra la: ");scanf("%lf",&x.tien);
  printf("So san pham moi loai la:\n");
  printf("   + Thuc pham: ");scanf("%d",&x.food);
  printf("   + Dien tu: ");scanf("%d",&x.electronic);
  printf("   + Quan ao: ");scanf("%d",&x.cloth);
  *tree=insert(*tree,x);
}
void timkiem(node *tree)
{
  char s[MAX];
  elementtype x;
  node *tmp = NULL;
  printf("ma so khach hang cua ban la: ");scanf("%s",s);
  strcpy(x.mskh,s);
  tmp = search(tree,x);
  if(tmp == NULL) printf("Khong tim thay mssk\n");
  else
    {
      printf("%8s%20s%8s\t%5s\t%10s\t%6s\n","mskh","ten","tien","food","electronic","cloth");
      printf("%8s%20s%8.1f\t%5d\t%10d\t%6d\n",tmp->data.mskh,tmp->data.ten,tmp->data.tien,tmp->data.food,tmp->data.electronic,tmp->data.cloth);
    }
}
void xoa(node **tree)
{
  char s[MAX];
  elementtype x;
  printf("Nhap ma so khach hang muon xoa: ");scanf("%s",s);
  strcpy(x.mskh,s);
  *tree=delete(*tree,x);
}
void ghifile(FILE *f_ghi,node *tree)
{
  if(tree != NULL)
    {
      fwrite(&tree->data,sizeof(elementtype),1,f_ghi);
      ghifile(f_ghi,tree->left);
      ghifile(f_ghi,tree->right);
    }
}
int main()
{
  FILE *f,*f_ghi;
  char filename[]="cskh.txt";
  char file_ghi[]="dulieura.dat";
  int i,k;
  node * tree=NULL;
  if((f=fopen(filename,"r")) == NULL)
    {printf("Loi mo file : %s",filename);return 1;}
  if((f_ghi=fopen(file_ghi,"wb")) == NULL)
    {printf("Loi mo file : %s",file_ghi);return 1;}
  do
    {
      menu();
      scanf("%d",&k);getchar();
      switch(k)
        {
        case 1:
          docfile(&tree,f);break;
        case 2:
          themkh(&tree);break;
        case 3:
          printf("%8s%20s%8s\t%5s\t%10s\t%6s\n","mskh","ten","tien","food","electronic","cloth");
          preorder(tree);printf("\n\n");break;
        case 4:
          printf("%8s%20s%8s\t%5s\t%10s\t%6s\n","mskh","ten","tien","food","electronic","cloth");
          inorder(tree);printf("\n\n");break;
        case 5:
          printf("%8s%20s%8s\t%5s\t%10s\t%6s\n","mskh","ten","tien","food","electronic","cloth");
          postorder(tree);printf("\n\n");break;
        case 6:
          xoa(&tree);break;
        case 7:
          timkiem(tree);break;
        case 8:
          printf("Du lieu se duoc ghi ra file %s\n",file_ghi);
          ghifile(f_ghi,tree);break;
        case 9:   fclose(f);fclose(f_ghi);return 0;
        default: printf("Wrong choice\n");
        }
    }
  while(1);

}
