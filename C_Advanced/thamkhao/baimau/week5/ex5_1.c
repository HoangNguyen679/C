#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct sv
{char ten[50];long ms;float diem;}sv;
void conv_dat(FILE *f1,FILE *f2)
{
  long ms;
  char ten[50];
  float mark;
  sv a;
  while(fscanf(f1,"%s",ten)!=EOF)
    {
      strcpy(a.ten,ten);
      fscanf(f1,"%ld",&ms);
      a.ms=ms;
      printf("Nhap diem thi sinh %s:",ten);
      scanf("%f",&mark);
      a.diem=mark;
      fwrite(&a,sizeof(sv),1,f2);
    }
}
void in(sv *a)
{  printf("Sinh vien:%s\t-MSSV:%ld\nDiem:%g\n",a->ten,a->ms,a->diem);}
void hien(FILE *f)
{
  sv *a;
  int n;
  a=(sv *)malloc(sizeof(sv));
  rewind(f);
  while((n=fread(a,sizeof(sv),1,f))!=0)
    in(a);
}
void hien2(FILE *f,int n, int m)
{
  sv *a;
  int number,i;
  rewind(f);
  a=(sv *)malloc(sizeof(sv));
  fseek(f,(n-1)*sizeof(sv),SEEK_SET);
  for(i=n;i<=m;i++)
    {
      number=fread(a,sizeof(sv),1,f);
      in(a);
    }
  free(a);
}
void fix(FILE *f)
{
  sv *a;
  long ms;
  int n,dem=0;
  float diem;
  printf("Nhap ma so sv:");
  scanf("%ld",&ms);
  a=(sv *)malloc(sizeof(sv));
  rewind(f);
  while(!feof(f))
    {n=fread(a,sizeof(sv),1,f);
      if(a->ms==ms) break;
      dem++;}
  if (feof(f)) printf("Khong co ai co MSSV nhu vay\n");
  else
    {printf("Nhap diem sua:");
      scanf("%f",&diem);
      a->diem=diem;
      fseek(f,dem*sizeof(sv),SEEK_SET);
      printf("%ld\t",ftell(f));
      n=fwrite(a,sizeof(sv),1,f);
      in(a);
      printf("%ld\n",ftell(f));
      rewind(f);
    }
  free(a);
}
int main(int argc,char* argv[])
{
  FILE *f,*f1;
  int chon,m,n;
  char *datfile="bangdiem.dat";
  if(argc!=2)
    {printf("Cu phap:%s <file .txt>\n",argv[0]);exit(1);}
  else
    {
      printf("Chuong trinh quan ly diem SV:\n");
      printf("Menu:\n1.Chuyen doi dong bo du lieu\n");
      printf("2.In danh sach sinh vien theo yeu cau\n");
      printf("3.Sua diem\n");
      printf("4.In danh sach sinh vien\n");
      printf("5.Exit\n");
      if((f=fopen(argv[1],"r"))==NULL)
        {printf("Cant open file %s\n",argv[1]);exit(1);}
      else
        {
          printf("Start creat file\n");
          if((f1=fopen(datfile,"w+b"))==NULL)
          { printf("Cant open file %s\n",datfile);exit(1);}
        else
          do{
            printf("Lua chon:");
            scanf("%d",&chon);
            printf("Da chon\n");
            switch(chon)
              {
              case 1:conv_dat(f,f1);break;
              case 2:printf("Xem tu vi tri thu:");scanf("%d",&n);
                printf("Xem den vi tri:");scanf("%d",&m);hien2(f1,n,m);break;
              case 3:fix(f1);break;
              case 4:hien(f1);break;
              }
          }while(chon!=5);
        }
      fclose(f);fclose(f1);}
  return 0;
}
