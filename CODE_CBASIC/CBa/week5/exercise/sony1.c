#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#define MAX  81

typedef struct{
  char model[25];
  char rom[3];
  char screen[5];
  char price[8];
}info;

struct list_el{
  struct list_el *next;
  info smartPhone;
};
typedef struct list_el node_smartPhone;

node_smartPhone *root=NULL,*cur=NULL,*prev=NULL;

node_smartPhone *makeNewNode(info smartPhone){
  node_smartPhone *new=(node_smartPhone *)malloc(sizeof(node_smartPhone));
  new->smartPhone=smartPhone;
  new->next=NULL;
  return new;
}

node_smartPhone *insertFirst(info smartPhone){
  node_smartPhone *new=makeNewNode(smartPhone);
  new->smartPhone=smartPhone;
  new->next=root;
  root=new;
  cur=new;
  return new;
}

node_smartPhone *insertAfterCur(info smartPhone){
  node_smartPhone *new=makeNewNode(smartPhone);
  if(root==NULL) cur=root=new;
  else{
    new->next = cur->next;
    cur->next = new;
    prev = cur;
    cur = cur->next;
  }
}

void printNode(node_smartPhone *p){
  if(p == NULL) printf("Loi con tro NULL\n");
  for(p ; p!=NULL ; p = p->next)
    printf("%-25s\t%-3s\t%-5s\t%-8s\n",(p->smartPhone).model,(p->smartPhone).rom,(p->smartPhone).screen,(p->smartPhone).price);
}

int main(){
  do{
    printf("MENU\n");
    printf("1. Import DB from text\n");
    printf("2. Import from DB\n");
    printf("3. Print all Sony Database\n");
    printf("4. Find phone(model)\n");
    printf("5. Exit\n\n");

    int chon;
    printf("Please select: ");
    scanf("%d",&chon);
    if(chon == 5){
      printf("Bye bye :p See you again\n");
      break;
    }

    char filedat[]="sony.dat";
    char filetxt[]="sony.txt";
    FILE *fin,*f;
    info *phone;
    int i;
    switch(chon){

    case 1:{
      if((fin=fopen(filetxt,"r")) == NULL){
        printf("Cannot open %s",filetxt);
        return 1;
      }

      char str[MAX];
      int soluong=0; // so luong dien thoai
      while((fgets(str,MAX,fin)) != NULL) soluong ++;
      rewind(fin);

      phone=(info *)malloc(soluong*sizeof(info));
      for(i = 0 ; i < soluong ; i++){
        fscanf(fin,"%s",(phone+i)->model);
        fscanf(fin,"%s",(phone+i)->rom);
        fscanf(fin,"%s",(phone+i)->screen);
        fscanf(fin,"%s",(phone+i)->price);
      } // het vong for

      if((f = fopen(filedat,"wb")) == NULL){
        printf("Cannot open %s",filedat);
        return 1;
      }
      fwrite(phone,sizeof(info),soluong,f);

      free(phone);
      fclose(fin);
      fclose(f);
    }break;

    case 2:{
      if( (f = fopen(filedat,"rb")) == NULL) {
        printf("Cannot open %s",filedat);
        return 1;
      }

      do{
        printf("1. Che do doc toan phan\n");
        printf("2. Che do doc mot phan\n");
        printf("3. Thoat\n\n");
        printf("Nhap lua chon: ");

        int chon2;
        scanf("%d",&chon2);
        if(chon2 == 3) break;
        switch(chon2) {
        case 1:{
          info tmp;
          while(feof(f) == 0) {
            fread(&tmp,sizeof(info),1,f);
            insertAfterCur(tmp);
          }
          printNode(root);
          fclose(f);
        } break; //het case 1 nho

        case 2:{
          if( (f = fopen(filedat,"rb")) == NULL) {
            printf("Cannot open %s",filedat);
            return 1;
          }
          printf("1. Doc tu dau danh sach\n");
          printf("2. Doc tu cuoi danh sach\n");
          printf("3. Thoat\n\n");

          int chon22;
          printf("Nhap lua chon: ");
          scanf("%d",&chon22);

          if(chon22 == 3) break;
          switch(chon22) {
          case 1: {
            printf("Nhap so dien thoai muon xem: ");
            int sodt1;
            scanf("%d",&sodt1);

            info *phone1;
            phone1 = (info*)malloc(sodt1*sizeof(info));
            fread(phone1,sizeof(info),sodt1,f);
            printf("%-25s\t%-3s\t%-5s\t%-8s\n","Model","Rom","Screen","Price");
            for(i = 0 ; i < sodt1 ; i++)
              printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone1+i)->model,(phone1+i)->rom,(phone1+i)->screen,(phone1+i)->price);
            fclose(f);
            free(phone1);
          }break;//het case 1 nho nho

          case 2:{
            printf("Nhap so dien thoai muon xem: ");
            int sodt2;
            scanf("%d",&sodt2);

            info *phone2;
            phone2 = (info*)malloc(sodt2*sizeof(info));

            int n=0;
            fseek(f,0,2);
            n=ftell(f)/sizeof(info);
            rewind(f);

            fseek(f , (n-sodt2)*sizeof(info) , 0);
            fread(phone2,sizeof(info),sodt2,f);
            printf("%-25s\t%-3s\t%-5s\t%-8s\n","Model","Rom","Screen","Price");
            for(i = 0 ; i < sodt2 ; i++)
              printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone2+i)->model,(phone2+i)->rom,(phone2+i)->screen,(phone2+i)->price);
            fclose(f);
            free(phone2);
          }break; //het case 2 nho nho
          default: printf("Nhap sai! \n");break;
          }
        }break; //het case 2 nho
        } //het switch
      }while(1); //het vong do
    } break;

    case 3:{
      if((f = fopen(filedat,"rb")) == NULL){
        printf("Cannot open %s",filedat);
        return 1;
      }
      int a=0; // so luong dient hoai
      while(fread(phone+a,sizeof(info),1,f)) a++;
      fread(phone,sizeof(info),i,f);
      while(a>30){
        printf("%-25s\t%-3s\t%-5s\t%-8s\n","Model","Rom","Screen","Price");
        for(i = 0 ; i < 30 ; i++)
          printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone+i)->model,(phone+i)->rom,(phone+i)->screen,(phone+i)->price);
        a-=30;
      }
      if(a <= 30){
        printf("%-25s\t%-3s\t%-5s\t%-8s\n","Model","Rom","Screen","Price");
        for(i = 0 ; i < a ; i++)
          printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone+i)->model,(phone+i)->rom,(phone+i)->screen,(phone+i)->price);
      }
      fclose(f);
    } break;

    case 4: {
      if((f = fopen(filedat,"rb")) == NULL){
        printf("Cannot open %s",filedat);
        return 1;
      }
      int sodt=0; // so luong dient hoai
      while(fread(phone+sodt,sizeof(info),1,f)) sodt++;
      fread(phone,sizeof(info),sodt,f);
      getchar();
      char mod[MAX];
      printf("Nhap model dien thoai ( chu thuong): ");
      gets(mod);
      int j=0;
      for(i = 0 ; i < sodt ; i++){
        if((strcmp(mod,(phone+i)->model)) == 0){
          printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone+j)->model,(phone+j)->rom,(phone+j)->screen,(phone+j)->price);
          j++;
        }
      } //het for
      if(j == 0) printf("Khong co mau model nhu ban go\n");
      fclose(f);
    } break; //het case 4
    } //het switch
  }while(1); //het vong lap do
}//het vong main
