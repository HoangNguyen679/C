#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define MAX  81
typedef struct{
  char model[25];
  char rom[3];
  char screen[5];
  char price[8];
}info;
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
    if(chon==5){
      printf("Bye bye :p See you again\n");
      break;
    }
    //mo con tro file
    char filedat[]="sony.dat";
    char filetxt[]="sony.txt";

    FILE *fin,*f;
    info *phone;
    switch(chon){
    case 1:{
      int i; // bien dem
      if((fin=fopen(filetxt,"r")) == NULL){
        printf("Cannot open %s",filetxt);
        return 1;
      }
      char str[MAX];
      int soluong=0; // so luong dien thoai
      while((fgets(str,MAX,fin)) != NULL) soluong ++;
      rewind(fin);
      printf("%d\n",soluong);
      phone=(info *)malloc(soluong*sizeof(info));
      for(i=0;i<soluong;i++){
        fscanf(fin,"%s",(phone+i)->model);
        fscanf(fin,"%s",(phone+i)->rom);
        fscanf(fin,"%s",(phone+i)->screen);
        fscanf(fin,"%s",(phone+i)->price);
      } // het vong for
      // ghi ra file dat
      if((f=fopen(filedat,"wb")) == NULL){
        printf("Cannot open %s",filedat);
        return 1;
      }
      fwrite(phone,sizeof(info),soluong,f);
      //giai phong bo nho + dong con tro file
      free(phone);
      fclose(fin);
      fclose(f);
    }break;
    case 2:{
      if((fin=fopen(filetxt,"r")) == NULL){
        printf("Cannot open %s",filetxt);
        return 1;
      }
      char str[MAX];
      int soluong=0; // so luong dien thoai
      while((fgets(str,MAX,fin)) != NULL) soluong ++;
      fclose(fin);
      printf("%d\n",soluong);
      do{
        printf("1. Che do doc toan phan\n");
        printf("2. Che do doc mot phan\n");
        printf("3. Thoat\n\n");
        printf("Nhap lua chon: ");
        int chon2;
        scanf("%d",&chon2);
        if(chon2 == 3) break;
        switch(chon2){
        case 1:{
          //doc tu file dat
          if((f=fopen(filedat,"rb")) == NULL){
            printf("Cannot open %s",filedat);
            return 1;
          }
          phone=(info * )malloc(soluong*sizeof(info));
          fread(phone,sizeof(info),soluong,f);
          printf("%-25s\t%-3s\t%-5s\t%-8s\n","Model","Rom","Screen","Price");
          int i; // bien dem
          for(i=0;i<soluong;i++)
            printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone+i)->model,(phone+i)->rom,(phone+i)->screen,(phone+i)->price);
          free(phone);
          fclose(f);
        }break; //het case 1 nho
        case 2:{
          printf("Nhan 1 de doc tu dau danh sach\nNhan 2 de doc tu cuoi danh sach\n");
          int chon3;
          scanf("%d",&chon3);
          switch(chon3){
          case 1:{
            printf("Nhap so dien thoai muon xem: ");
            int sodt1;
            scanf("%d",&sodt1);
            if((f=fopen(filedat,"rb")) == NULL){
              printf("Cannot open %s",filedat);
              return 1;
            }
            info *phone1;
            phone1=(info*)malloc(sodt1*sizeof(info));
            fread(phone1,sizeof(info),sodt1,f);
            printf("%-25s\t%-3s\t%-5s\t%-8s\n","Model","Rom","Screen","Price");
            int i; // bien dem
            for(i=0;i<sodt1;i++)
              printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone1+i)->model,(phone1+i)->rom,(phone1+i)->screen,(phone1+i)->price);
            fclose(f);
            free(phone1);
          }break;//het case 1 nho nho

          case 2:{
            printf("Nhap so dien thoai muon xem: ");
            int sodt2;
            scanf("%d",&sodt2);
            if((f=fopen(filedat,"rb")) == NULL){
              printf("Cannot open %s",filedat);
              return 1;
            }
            info *phone2;
            phone2=(info*)malloc(sodt2*sizeof(info));
            // fseek(f,sodt2*sizeof(info),SEEK_END);
            fread(phone2,sizeof(info),sodt2,f);
            printf("%-25s\t%-3s\t%-5s\t%-8s\n","Model","Rom","Screen","Price");
            int i; // bien dem
            for(i=0;i<sodt2;i++)
              printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone2+i)->model,(phone2+i)->rom,(phone2+i)->screen,(phone2+i)->price);
            fclose(f);
            free(phone2);
          }break; //het case 2 nho nho
          default: printf("Nhap sai! \n");break;
          }
        }break; //het case 2 nho
        } //het switch
      }while(1); //het vong do
    }break;
    case 3:{
      if((f=fopen(filedat,"rb")) == NULL){
        printf("Cannot open %s",filedat);
        return 1;
      }
      int i=0; // so luong dient hoai
      while(fread(phone+i,sizeof(info),1,f)) i++;
      fread(phone,sizeof(info),i,f);
      int j=0; // bien dem
      while(i>30){
        printf("%-25s\t%-3s\t%-5s\t%-8s\n","Model","Rom","Screen","Price");
        for(j=0;j<30;j++)
          printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone+j)->model,(phone+j)->rom,(phone+j)->screen,(phone+j)->price);
        i-=30;
      }
      if(i<=30){
        printf("%-25s\t%-3s\t%-5s\t%-8s\n","Model","Rom","Screen","Price");
        for(j=0;j<i;j++)
          printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone+j)->model,(phone+j)->rom,(phone+j)->screen,(phone+j)->price);
      }
      fclose(f);
    }break;
    case 4:{
      if((f=fopen(filedat,"rb")) == NULL){
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
      int i=0,j=0;
      for(i=0;i<sodt;i++){
        if((strcmp(mod,(phone+i)->model)) == 0){
          printf("%-25s\t%-3s\t%-5s\t%-8s\n",(phone+j)->model,(phone+j)->rom,(phone+j)->screen,(phone+j)->price);
          j++;
        } //het if
      } //het for
      if(j==0) printf("Khong co mau model nhu ban go\n");
      fclose(f);
    }break; //het case 4
    }//het switch
  }while(1); //het vong lap do
}//het vong main
