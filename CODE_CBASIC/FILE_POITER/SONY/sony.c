#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 81

typedef struct sony_data{
  char model[25];
  float rom;
  float screen;
  float price;
}sony_data;

void importFile(FILE *fin,FILE *fout);
void printAll(FILE *f);
void printPhone1(FILE *f,int x);
void printPhone2(FILE *f,int x);
int findPhone(FILE *f,char str[MAX]);
void printMenu(); // in menu chinh
void printMenu2(); // in menu in theo mot phan
void printMenu2_2(); // in menu chon tu dau hoac cuoi
int size(FILE *f); // tra ve so phan tu cua file

FILE *f_txt,*f_dat;
char filetext[]="sony.txt";
char filedat[]="sony.dat";

int main(){
  do{
    printMenu(); int ch;
    printf("Please select: "); scanf("%d",&ch);getchar();
    switch(ch) {
    case 1: importFile(f_txt,f_dat); break;
    case 2: {
      do{
        printMenu2(); int ch2;
        printf("Please select: "); scanf("%d",&ch2);getchar();
        if(ch2 == 3)break;
        switch(ch2){
        case 1:printAll(f_dat);break;
        case 2:{
          do{
            printMenu2_2(); int ch2_2;
            printf("Please select: "); scanf("%d",&ch2_2);getchar();
            if(ch2_2 == 3)break;
            switch(ch2_2){
            case 1:{
              printf("Enter the number of phone: ");
              int num1; scanf("%d",&num1);
              printPhone1(f_dat,num1);
            } break;
            case 2:{
              printf("Enter the number of phone: ");
              int num2; scanf("%d",&num2);
              printPhone2(f_dat,num2);
            }break;
            default: printf("Wrong choice!!!\n");
            } //het switch nho
          }while(1); //het do nho
        } break;
        default: printf("Wrong choice!!!\n");
        } // het switch to
      }while(1); //het do to
    } break;
    case 3: printAll(f_dat);break;
    case 4:
      {
        char phone_find[MAX];
        printf("Enter the model (in lowcase): ");gets(phone_find);
        findPhone(f_dat,phone_find);
      }break;
    case 5: return;break;
    default: printf("\nWrong choice!\n");
    }
  }while(1);
  return 0;
}

int size(FILE *f){
  int k;
  fseek(f,0,2);
  k=ftell(f)/sizeof(sony_data);
  rewind(f);
  return k;
}

void printMenu(){
  printf("\n\n>>>>>>>>>>MENU<<<<<<<<<<\n\n");
  printf("1. Import data from text file to dat file\n");
  printf("2. Read data from dat file\n");
  printf("3. Print all Sony Database\n");
  printf("4. Find phone(model)\n");
  printf("5. Exit\n\n");
}

void printMenu2(){
  printf("\n\n>>>>>>>>>>MENU<<<<<<<<<<\n\n");
  printf("1. All-part\n");
  printf("2. One-part\n");
  printf("3. Exit\n\n");
}

void printMenu2_2(){
  printf("\n\n>>>>>>>>>>MENU<<<<<<<<<<\n\n");
  printf("1. From begin\n");
  printf("2. From end\n");
  printf("3. Exit\n\n");
}

void printPhone1(FILE *f,int x){
  if((f=fopen(filedat,"rb")) == NULL){printf("Cannot open %s\n",filedat); return; }
  sony_data *phone;
  int i=0,n=size(f);
  if(x<=0 || x>n) {printf("---------->ERROR\n");return;}
  phone =(sony_data *)malloc(x*sizeof(sony_data));
  fread(phone,sizeof(sony_data),x,f);
  printf("\n\n>>>>>>>>>> DATABASE <<<<<<<<<<\n\n");
  printf("\n\n%-25s\t%-8s\t%-8s\t%-8s\n\n","MODEL","ROM","SCREEN","PRICE");
  for(i=0; i<x; i++){
  	printf("%-25s\t%-8.1f\t%-8.1f\t%-8.1f\n",(phone+i)->model,(phone+i)->rom,(phone+i)->screen,(phone+i)->price);
  }
  free(phone);fclose(f);
}

void printPhone2(FILE *f,int x){
  if((f=fopen(filedat,"rb")) == NULL){printf("Cannot open %s\n",filedat); return; }
  sony_data *phone;
  int i=0,n=size(f);
  if(x<=0 || x>n) {printf("---------->ERROR\n");return;}
  fseek(f,(n-x)*sizeof(sony_data),0);
  phone =(sony_data *)malloc(x*sizeof(sony_data));
  fread(phone,sizeof(sony_data),x,f);
  printf("\n\n>>>>>>>>>> DATABASE <<<<<<<<<<\n\n");
  printf("\n\n%-25s\t%-8s\t%-8s\t%-8s\n\n","MODEL","ROM","SCREEN","PRICE");
  for(i=0; i<x; i++){
    printf("%-25s\t%-8.1f\t%-8.1f\t%-8.1f\n",(phone+i)->model,(phone+i)->rom,(phone+i)->screen,(phone+i)->price);
  }
  free(phone);fclose(f);
}

void importFile(FILE *fin,FILE *fout){
  if((fin=fopen(filetext,"r")) == NULL){printf("Cannot open %s\n",filetext); return; }
  if((fout=fopen(filedat,"wb")) == NULL){printf("Cannot open %s\n",filedat); return; }
  sony_data *phone;
  int n=0,i;
  char str[MAX];
  while(fgets(str,MAX,fin)) n++;
  rewind(fin);
  phone = (sony_data *)malloc(n*sizeof(sony_data));
  for(i = 0; i<n; i++){
    fscanf(fin,"%s",(phone+i)->model);
    fscanf(fin,"%f",&((phone+i)->rom));
    fscanf(fin,"%f",&((phone+i)->screen));
    fscanf(fin,"%f",&((phone+i)->price));
  }
  int c;
  c=fwrite(phone,sizeof(sony_data),n,fout);
  if(c==n) printf("\n>>>>>>>>>>SUCCESS!!!<<<<<<<<<<\n\n");
  free(phone);fclose(fin);fclose(fout);
}

void printAll(FILE *f){
  if((f=fopen(filedat,"rb")) == NULL){printf("Cannot open %s\n",filedat); return; }
  int i=0,n=size(f);
  sony_data *phone;
  phone = (sony_data *)malloc(n*sizeof(sony_data));
  fread(phone,sizeof(sony_data),n,f);
  printf("\n\n>>>>>>>>>> DATABASE <<<<<<<<<<\n\n");
  printf("\n\n%-25s\t%-8s\t%-8s\t%-8s\n\n","MODEL","ROM","SCREEN","PRICE");
  for(i=0; i<n; i++){
    printf("%-25s\t%-8.1f\t%-8.1f\t%-8.1f\n",(phone+i)->model,(phone+i)->rom,(phone+i)->screen,(phone+i)->price);
  }
}

int findPhone(FILE *f,char str[MAX]){
  if((f=fopen(filedat,"rb")) == NULL){printf("Cannot open %s\n",filedat); return; }
  sony_data *phone;
  int i=0,j=0,n=size(f);
  phone = (sony_data *)malloc(n*sizeof(sony_data));
  fread(phone,sizeof(sony_data),n,f);
  for(i=0; i<n; i++)
    if(strcmp((phone+i)->model,str) == 0){
      printf("\n%-25s\t%-8.1f\t%-8.1f\t%-8.1f\n",(phone+i)->model,(phone+i)->rom,(phone+i)->screen,(phone+i)->price);
      j++;
    }
  if(j == 0) printf("---------->Found no model\n");
  free(phone);fclose(f);
}
