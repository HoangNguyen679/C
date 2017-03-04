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
  phoneaddress a[MAX];
  phoneaddress one_address,*phonebook=&one_address;
  int n;
  int i;
  int reval = SUCCESS;
  printf("Nhap so phan tu muon nhap\n");
  scanf("%d",&n);getchar();
  for(i=0;i<n;i++){
    printf("Ten: ");gets(a[i].name);
    printf("So dient hoai: ");gets(a[i].sdt);
    printf("Email: ");gets(a[i].email);
  }
  FILE *f;
  if((f=fopen("phonebook.dat","w+b")) == NULL){
    printf("Cannot open phonebook.dat\n");
    reval=FAIL;;
  }
  int b;//gtri fwrite tra ve
  b=fwrite(a,sizeof(phoneaddress),n,f);
  printf("fwrite tra ve %d\n",b);
  rewind(f);
  int c;//gtri tra ve fread
  c=fread(a,sizeof(phoneaddress),n,f);
  printf("fread tra ve gia tri %d\n",c);
  for(i=0;i<n;i++){
    printf("%s-",a[i].name);
    printf("%s-",a[i].sdt);
    printf("%s\n",a[i].email);
  }
  fclose(f);
  return reval;
}
