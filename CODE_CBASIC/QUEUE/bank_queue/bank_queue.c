#include<stdio.h>
#include<stdlib.h>
#include"queue_list.h"
#define MAX 10
typedef struct quay_data
{
  time tg;
  int stt,doi;
}quay_data;

int a,XL,q;
time work1,work2;
queue hang[MAX];
quay_data p[MAX];

int cmp(time t1,time t2)
{
  return (t1.gio-t2.gio)*60+(t1.phut-t2.phut);
}
int check(time t)
{
  if(t.gio>23 || t.gio<0 || t.phut>59 || t.phut<0)
    {printf("Nhap thoi gian sai\n");return 1;}
  if(cmp(t,work1)<0 || cmp(t,work2)>0)
    {printf("Het gio\n");return 1;}
  return 0;
}
time plus(time t,int i)
{
  t.gio+=(t.phut+i)/60;
  t.phut=(t.phut+i)%60;
  return t;
}
void vao(time t,int kh,int dem,int *dem_kh,long *dem_tg)
{
  int i,j,doi=0;
  for(j=dem;j<dem+kh;j++)
    {
      i=j%q;
      if(p[i].stt==-1) continue; //Qua gio lam viec
      //Xu ly truoc khi dua them phan tu vao hang doi
      if(p[i].stt==0)            //Quay rong
        {
          if(!isEmpty_queue(hang[i]))
            {
              p[i].tg=dequeue(&(hang[i]));
              p[i].stt=1;
              (*dem_kh)++;
            }
        }
      else                        //Quay dang co nguoi
        {
          while(!isEmpty_queue(hang[i]) && (cmp(t,hang[i].front->data)-cmp(hang[i].front->data,p[i].tg)) >=0)
            {
              doi=XL-cmp(hang[i].front->data,p[i].tg);
              p[i].tg=plus(dequeue(&(hang[i])),doi);
              p[i].doi=p[i].doi-doi;
            }
          // Xu ly khi hang doi rong
          if(isEmpty_queue(hang[i]))
            if(cmp(t,p[i].tg) >= XL)
              {p[i].tg=t;p[i].stt=0;p[i].doi=0;}
        }
      //Xep va xu ly dua phan tu moi vao hang doi
      if((p[i].stt==0) && (!check(plus(t,XL))))
        {
          p[i].tg=t;p[i].stt=1;(*dem_kh)++;
          printf("Khach hang thu %d vao quay so %d\n",j-dem+1,i+1);
        }
      else
        {
          if(isEmpty_queue(hang[i])) p[i].doi=XL-cmp(t,p[i].tg);
          else p[i].doi+=XL;
          if(!check(plus(t,p[i].doi+XL)))
            {
              enqueue(&(hang[i]),t);
              (*dem_tg)+=p[i].doi;
              (*dem_kh)++;
              printf("Khach hang thu %d vao hang %d doi:%d phut\n",j-dem+1,i+1,p[i].doi);
            }
          else
            p[i].stt=-1;
        }
    }
}

int main(int argc, char *argv[])
{
  FILE *f;
  int i,dem_kh=0,dem=0,kh;
  long dem_tg=0;
  char buff[100];
  time t;
  if (argc != 2)
    {printf("Wrong argument!\nStruct: %s <filename>\n",argv[0]);return 1;}
  if((f=fopen(argv[1],"r")) == NULL)
    {printf("Cannot open file\n");return 1;}
  else
    {
      printf("\n\nNgan hang BIDV\n\n");
      printf("Thoi gian bat dau lam viec:");scanf("%d:%d",&(work1.gio),&(work1.phut));
      printf("Thoi gian ket thuc lam viec:");scanf("%d:%d",&(work2.gio),&(work2.phut));
      printf("Thoi gian xu ly 1 giao dich:");scanf("%d",&XL);
      printf("So quay phuc vu trong ngan hang:");scanf("%d",&q);
      printf("\n\n");

      for(i=0;i<q;i++)
        {
          queueConstruct(&hang[i]);
          p[i].stt = p[i].doi = 0;
        }
      fscanf(f,"%[^\n]",buff); // xoa dong dau tien trong filetxt

      while(!feof(f))
        {
          fscanf(f,"%d:%d%d",&t.gio,&t.phut,&kh);
          if(!feof(f))
            {
              if(check(t) != 1)
                {
                  printf("%2d:%02d%40d khach hang\n",t.gio,t.phut,kh);
                  vao(t,kh,dem,&dem_kh,&dem_tg);
                  dem+=kh;
                }
            }
        }
      //Thong ke
      printf("\n-----------------------------------------------------\n");
      printf("Hom nay da phuc vu giao dich cho %d khach hang\n",dem_kh);
      printf("Tong thoi gian cho:%ld\n",dem_tg);
      printf("Thoi gian cho trung binh la:%.1f\n",dem_tg/(dem_kh*1.0));
      fclose(f);
    }
  return 0;
}
