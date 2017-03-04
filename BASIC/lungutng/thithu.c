/* Nguyen Duc Hoang - 9A */
// Date Create:
#include<stdio.h>
#include<string.h>
#define Total 4
int khoangtrang(char s[]){
  int i=0;
  while (s[i] != '\0') {
    if (s[i] == ' ') return 1;
    i++;
  }
  return 0;
}
void clear_buffer() {
	int ch;
	while ((ch=getchar()) != '\n' && ch != EOF);
}
typedef struct {
  char Name[25];
  int Old;
  int Score[5];
} Game;
main() {
  int chon,dai,dem=0;
  int i=0,j,k,M,a;
  int sapxep[4];
  Game Person[Total],doi[Total];
	char s[41],s1[41],sthu[41],c[4];
	do {
		printf("MENU\n");
		printf("1.Khoi dong tro choi\n");
		printf("2.Choi doan ki tu\n");
		printf("3.Tong hop ket qua\n");
		printf("4.Thoat\n");
		do {
			printf("Nhap lua chon: ");
			scanf("%d",&chon);getchar();
			if (chon < 1 || chon >4) printf("Nhap lai!\n");
		} while (chon < 1 || chon >4);
		switch(chon){
		case 1: {
		  do {
		    printf("Nhap vao xau ki thu : ");
		    gets(s);
		    if (strlen(s) < 20 || strlen(s) > 40) {
		      printf("Nhap lai xau ki tu chieu dai trong khoang 20 den 40\n");
              continue;
            }
            if (khoangtrang(s) == 1)
              printf("Nhap lai xau ki tu khong co khoang trang!\n");
           } while (strlen(s) < 20 || strlen(s) > 40 || khoangtrang(s) == 1);
          do {
		    printf("Nhap vao tong so nguoi choi: ");
		    scanf("%d",&M);getchar();
		    if (M < 1 || M > 4) printf("Nhap lai !\n");
		    } while (M < 1 || M > 4);
		    for (i=0;i<M;i++){
		      printf("Nguoi choi thu %d\nTen: ",i+1);
		      gets(Person[i].Name);
		      printf("Tuoi: ");scanf("%d",&Person[i].Old);getchar();
		    }
		    printf("%-25s\t\t%-4s\n","Ho ten","Tuoi");
		    for(i=0;i<M;i++)
		      printf("%-25s\t\t%-4d\n",Person[i].Name,Person[i].Old);
		      }break;
		case 2: {
		  for(i=0;i<M;i++){
            dai=strlen(s);
		  for(a=0;a<dai;a++) s1[a]='*';s1[dai]='\0';
		  puts(s1);
		    printf("Nguoi choi thu %d\n",i+1);
		    for(j=0;j<4;j++){
		      printf("Doan ki tu lan %d: ",j+1);
		      scanf("%c",&c[j]);getchar();
		      for(k=0;k<dai;k++){
			if (s[k] == c[j] || s[k] == c[j] +32 ) {s1[k]=c[j];dem++;}
		      }
		      puts(s1);Person[i].Score[j]=dem;dem=0;
		    }
		    printf("Nhap xau ki tu: ");
		    gets(sthu);
		    if (strcmp(sthu,s) == 0){ printf("ban da thang cuoc\n");Person[i].Score[4]=20+Person[i].Score[0]+Person[i].Score[1]+Person[i].Score[2]+Person[i].Score[3];}else {
              printf("Ban da nhap sai day ki tu ! \n");
              Person[i].Score[4]=Person[i].Score[0]+Person[i].Score[1]+Person[i].Score[2]+Person[i].Score[3];}
		  }
		  printf("%-25s\t%3s\t%3s\t%3s\t%3s\%5s\n","Ho ten","L1","L2","L3","L4","Tong");
		  for(i=0;i<M;i++)
		    printf("%-25s\t%3d\t%3d\t%3d\t%3d\%5d\n",Person[i].Name,Person[i].Score[0],Person[i].Score[1],Person[i].Score[2],Person[i].Score[3],Person[i].Score[4]);
		}break;
		case 3: {

		  printf("%3s\t%-25s\t%s\n","STT","Ho ten","Do sai lech");
		  for(i=0;i<M;i++) {
            if (Person[i].Score[4]<Person[i+1].Score[4]) {
              doi[i] = Person[i];
              Person[i] = Person[i+1];
              Person[i+1] = doi[i];
            }
          }
          for(i=0;i<M;i++)
            printf("%3d\t%-25s\t%d\n",i+1,Person[i].Name,Person[i].Score[4]);
		}break;
		}
		if (chon == 4) break;
	} while (1);
}
