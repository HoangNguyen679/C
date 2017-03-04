#include<stdio.h>
#include<math.h>
typedef struct point
{float x,y;}point;
typedef struct circle
{point tam;float r;}circle;
float distance(point a,point b)
{
  return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int check(circle *c1,circle *c2)
{
  float a=(distance(c1->tam,c2->tam));
  if ((a-(c1->r+c2->r)<=0)&&(a-fabs(c1->r-c2->r)>0)) return 1;
  return 0;
}
void nhap(circle *p)
{
  printf("Nhap to do tam duong tron:\nOx:");
  scanf("%f",&(p->tam.x));
  printf("Oy:");
  scanf("%f",&(p->tam.y));
  printf("Nhap do dai R=");
  scanf("%f",&(p->r));
}
void in(circle *p,int i)
{
  printf("Duong tron O%d:\nTam : O(%5g,%5g)\nBan kinh:%g\n",i,p->tam.x,p->tam.y,p->r);
}
int main()
{
  circle *p;
  int save,max,dem,num,i,j,kt[20][20];
  printf("Nhap vao so duong tron ma ban muon tao:");
  scanf("%d",&num);
  p=(circle *)malloc(num*sizeof(circle));
  if(p==NULL)
    {printf("Khong the cap phat bo nho\n");exit(1);}
  for(i=0;i<num;i++)
    {
      nhap(p);
      p++;
    }
  p=p-num;
  for(j=0;j<num;j++)
    {
      in(p,j+1);
      p++;
    }
  p=p-num;
  for(i=0;i<num;i++)
    for(j=i;j<num;j++)
      if (i==j) kt[i][j]=0;
      else {kt[i][j]=check(p+i,p+j);kt[j][i]=kt[i][j];}
  max=0;save=0;
  for(i=0;i<num;i++)
    {dem=0;
      for(j=0;j<num;j++)
        dem=dem+kt[i][j];
      if (dem>save) {max=i;save=dem;}
    }
  printf("Duong tro giao voi nhieu duong tron nhat:\n");
  in(p+max,max+1);
  printf("Cat cac duong tron:\n");
  for(i=0;i<num;i++)
    if (kt[max][i]) in(p+i,i+1);
  return 0;
}

