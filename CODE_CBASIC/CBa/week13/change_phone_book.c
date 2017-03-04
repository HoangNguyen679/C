#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 81

typedef struct phone_address{
  char name[25];
  char tel[12];
  char email[25];
}phone_address;
typedef phone_address elementtype;
void SWAP(elementtype *list1,elementtype *list2)
{
  elementtype temp=*list1;
  *list1 = *list2;
  *list2 = temp;
}
void quick_sort(elementtype list[], int left, int right)
{
  int i,j;///pivot la phan tu chot
  char pivot[MAX];
  if(left < right)
    {
      i = left;
      j = right + 1;
      strcpy(pivot,list[left].name);
      do
        {
          do i++;while(strcmp(pivot,list[i].name)<0);
          do j--;while(strcmp(pivot,list[j].name)>0);
          if(i<j) SWAP(&list[i],&list[j]);
        }
      while(i<j);
      SWAP(&list[left],&list[j]);
      quick_sort(list,left,j-1);
      quick_sort(list,j+1,right);
    }
}
char filedat[]="phone_data.dat";
char filetext[]="phone_data.txt";
FILE *f_dat,*f_txt;
void menu()
{
  printf("MENU\n\n");
  printf("1. Nhap tu txt -> dat\n");
  printf("2. In ra du lieu\n");
  printf("3. Sap xep theo ten\n");
  printf("4. Thoat\n");
  printf("Please select: ");
}
int main(){
  phone_address *phone;
  if((f_txt=fopen(filetext,"r+")) == NULL){printf("Cannot open %s\n",filetext); return 1;}
  if((f_dat=fopen(filedat,"w+b")) == NULL){printf("Cannot open %s\n",filedat); return 1;}
  char str[MAX]; int n=0,i,k;
  while(fgets(str,MAX,f_txt) != NULL) n++;
  rewind(f_txt);
  phone = (phone_address *)malloc(n*sizeof(phone_address));
  do
    {
      menu();scanf("%d",&k);
      switch(k)
        {
        case 1:
          for(i = 0; i < n; i++)
            {
              fscanf(f_txt,"%s",(phone+i)->name);
              fscanf(f_txt,"%s",(phone+i)->tel);
              fscanf(f_txt,"%s",(phone+i)->email);
            }
          fwrite(phone,sizeof(phone_address),n,f_dat);
          break;
        case 2:
          for(i = 0; i < n; i++)
            printf("%-25s\t%12s\t%-25s\n",(phone+i)->name,(phone+i)->tel,(phone+i)->email);
          break;
        case 3:
          quick_sort(phone,0,n-1);break;
        case 4: return 0;
        default: printf("Wrong choice\n");
        }
    }
  while(1);
  free(phone);
  fclose(f_txt);
  fclose(f_dat);
}
