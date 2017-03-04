#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum{MAX=81,LINE=5};
typedef struct dt
{char model[50],phangiai[10];float store,gia;}dt;
void conv_dat(FILE *f1,FILE *f2)
{
  float store,gia;
  char ten[50],pg[50];
  dt a;
  while(fscanf(f1,"%s",ten)!=EOF)
    {
      strcpy(a.model,ten);
      fscanf(f1,"%f",&store);
      a.store=store;
      fscanf(f1,"%s",pg);
      strcpy(a.phangiai,pg);
      fscanf(f1,"%f",&gia);
      a.gia=gia;
      fwrite(&a,sizeof(dt),1,f2);
    }
}
void in(dt *a)
{
  printf("Model:%s\nThong tin:\nBo nho:%g\nDo phan giai:%s\nGia:%g\n***\n",a->model,a->store,a->phangiai,a->gia);
}
void show(FILE *f)
{
  char buff[81];
  int dem=0;
  dt *a;
  a=(dt *)malloc(sizeof(dt));
  rewind(f);
  while(fread(a,sizeof(dt),1,f)!=0)
    {
      dem++;
      if(dem%LINE==0) {printf("press any key to continue\n");getchar();}
      in(a);
    }
  free(a);
}
void search(FILE *f)
{
  char model[50];
  dt *a;
  printf("Nhap model dien thoai ban muon tim kiem:");
  scanf("%s",model);
  rewind(f);
  a=(dt *)malloc(sizeof(dt));
  while(fread(a,sizeof(dt),1,f)!=0)
      if(strcmp(a->model,model)==0) {in(a);break;}
  free(a);
}
int main(int argc,char* argv[])
{
  FILE *f,*f1;
  int chon;
  if(argc!=2) {printf("Cu phap: %s <file data.txt>\n",argv[0]);exit(1);}
  else
    if((f=fopen(argv[1],"r"))==NULL)
      {printf("Cant open file %s\n",argv[1]);exit(0);}
    else
      {
        printf("Cua hang di dong NO-store\n");
        printf("Menu\n1.Chuyen du lieu tu file .txt sang .doc\n");
        printf("2.Hien danh sach dien thoai cua cua hang\n");
        printf("3.Tim kiem mau dien thoai theo model\n");
        printf("4.Exit\n");
        if((f1=fopen("dt.dat","w+b"))==NULL)
          {printf("Cant open file dt.dat\n");exit(1);}
        else
          do{
            printf("Chon:");
            scanf("%d",&chon);
            switch(chon)
              {
              case 1:conv_dat(f,f1);break;
              case 2:show(f1);break;
              case 3:search(f1);break;
              }
          }while(chon!=4);
        fclose(f);fclose(f1);
      }
  return 0;
}
