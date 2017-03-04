#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define SIZE 100
char *my_strcat(char *str1,char *str2){
  char *str;
  int l1,l2;
  l1=strlen(str1);
  l2=strlen(str2);
  str=(char*)malloc((l1+l2+1)*sizeof(char));
  if (str == NULL){
    printf("Cap phat that bai!");
    return NULL;
  }
  strcpy(str,str1);
  strcpy(str+l1,str2);
  return str;
}
int main(){
  char str1[SIZE],str2[SIZE];
  char *catStr;
  printf("Nhap vao hai chuoi: ");
  scanf("%100s",str1);
  scanf("%100s",str2);
  catStr=my_strcat(str1,str2);
  if(catStr == NULL){
    printf("Loi trong qua trinh cap phat bo nho\n");
    return 1;
  }
  printf("chuoi noi %s va %s la %s \n",str1,str2,catStr);
  free(catStr);
  return 0;
}
