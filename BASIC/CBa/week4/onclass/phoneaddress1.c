#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 100
enum {SUCCESS,FAIL};
typedef struct{
  char name[30];
  char sdt[12];
  char email[30];
}phoneaddress;
int main(){
  phoneaddress *phonearr;
  int n;
  int i,irc;
  int reval = SUCCESS;
  FILE *f;
  if((f=fopen("phonebook.dat","r+b")) == NULL){
    printf("Cannot open phonebook.dat\n");
    reval=FAIL;
  }
  int canduoi, cantren;
  do{
    printf("Nhap can duoi du lieu: ");
    scanf("%d",&canduoi);
    if(canduoi<0) printf("Nhap so >0!\n");
  }while(canduoi<0);
  do{
    printf("Nhap can tren du lieu: ");
    scanf("%d",&cantren);
    if(cantren<canduoi) printf("Nhap loi! Nhap can tren > can duoi !\n");
  }while(cantren<canduoi);


  phonearr=(phoneaddress *)malloc((cantren-canduoi+1)*sizeof(phoneaddress));
  if(phonearr == NULL){
    printf("Memory allocation failed\n");
    return FAIL;
  }
  if (fseek(f,canduoi*sizeof(phoneaddress),SEEK_SET) != 0){
    printf("Fseek failed!\n");
    return FAIL;
  }
  irc = fread(phonearr, sizeof(phoneaddress), (cantren-canduoi+1), f);
  printf("So du lieu doc dc : %d\n",irc);
  for(i=0; i<(cantren-canduoi+1); i++){
	printf("%s-",phonearr[i].name);
	printf("%s-",phonearr[i].sdt);
	printf("%s\n",phonearr[i].email);
  }
  strcpy(phonearr[1].name,"Mail Lien");
  strcpy(phonearr[1].sdt,"091234576");
  strcpy(phonearr[1].email,"mailien@gmail.com");
  fseek(f,canduoi*sizeof(phoneaddress),SEEK_SET);
  irc = fwrite(phonearr, sizeof(phoneaddress), (cantren-canduoi+1), f);
  fseek(f,canduoi*sizeof(phoneaddress),SEEK_SET);
  for(i=0; i<(cantren-canduoi+1); i++){
	printf("%s-",phonearr[i].name);
	printf("%s-",phonearr[i].sdt);
	printf("%s\n",phonearr[i].email);
  }
  fclose(f);
  free(phonearr);
  return reval;
}
