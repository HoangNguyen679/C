/* Nguyen Duc Hoang - 9A */
// Date Create:
#include<stdio.h>
#include<string.h>
#define Total 5
void clear_buffer() {
	int ch;
	while ((ch=getchar()) != '\n' && ch != EOF);
}
int ktraten(char s[]) {
  int i=0;
  while (s[i] != '\0') {
    i++;
    if (s[i] == ' ') return 1;
  }
}
typedef struct {
char Name[25];
int Old;
float Suggest[6];
} Result;
main() {
	int chon;
	int i,j,M;
    float N,saiso[6],temp;
	Result Person[Total],doi[Total];
    for(i=0;i<Total;i++)
      for(j=0;j<6;j++) Person[i].Suggest[j] = 0;
	do {
		printf("MENU\n");
		printf("1.Khoi dong tro choi\n");
		printf("2.Choi doan so\n");
		printf("3.Ket qua\n");
		printf("4.Thoat\n");
		do {
			printf("Nhap lua chon: ");
			scanf("%d",&chon);
			if (chon < 1 || chon >4) printf("Nhap lai!\n");
		} while (chon < 1 || chon >4);
		switch(chon){
		case 1: {
          do {
            printf("Nhap N: ");scanf("%f",&N);clear_buffer();
            if(N<1 || N>100) printf("Nhap lai !\n");
          }while (N<1 || N>100);
          do {
            printf("Nhap vao so nguoi choi: ");scanf("%d",&M);clear_buffer();
            if (M<1 || M>5) printf("Nhap lai!\n");
          }while (M<1 || M>5);
          for (i=0;i<M;i++){
            printf("Nguoi choi thu %d\n",i+1);
            do {
              printf("Nhap ten: ");gets(Person[i].Name);
              if (ktraten(Person[i].Name) != 1) printf("Nhap lai ten co khoang trang!\n");
            }while(ktraten(Person[i].Name) != 1);
            printf("Nhap tuoi: ");scanf("%d",&Person[i].Old);clear_buffer();
          }
          printf("%3s\t%-25s\t%4s\n","STT","Ho ten","Tuoi");
          for(i=0;i<M;i++) printf("%3d\t%-25s\t%4d\n",i+1,Person[i].Name,Person[i].Old);
        }break;
		case 2: {
          for(i=0;i<M;i++){
            printf("Nguoi choi thu %d doan so\n",i+1);
            for(j=0;j<6;j++){
              printf("Lan thu %d\n",j+1);
              do {
              scanf("%f",&Person[i].Suggest[j]);
              if (Person[i].Suggest[j] <1 || Person[i].Suggest[j] >100) printf("Nhap ;ai !\n");
              }while (Person[i].Suggest[j] <1 || Person[i].Suggest[j] >100);
              if (Person[i].Suggest[j] == N) {
                printf("Ban da nhap dung\n");
                break;
              }
              else if(Person[i].Suggest[j] > N) printf("So ban vua nhap lon hon N! \n");
              else if(Person[i].Suggest[j] < N) printf("So ban vua nhap nho hon N! \n");
            }
          }
          printf("%-25s\t%4s\t%4s\t%4s\t%4s\t%4s\t%4s\n","Ho ten","L1","L2","L3","L4","L5","L6");
          for(i=0;i<M;i++) printf("%-25s\t%4g\t%4g\t%4g\t%4g\t%4g\t%4g\n",Person[i].Name,Person[i].Suggest[0],Person[i].Suggest[1],Person[i].Suggest[2],Person[i].Suggest[3],Person[i].Suggest[4],Person[i].Suggest[5]);
        }break;
		case 3: {
          for(i=0;i<M;i++){
            j=0;
            while(Person[i].Suggest[j] != 0 && j<6) j++;
            saiso[i]=Person[i].Suggest[j-1]/N-1;
            if(saiso[i]<0) saiso[i]=saiso[i]*(-1);
          }

          for(i=0;i<M-1;i++){
            if (saiso[i]>saiso[i+1]){
              temp=saiso[i];
              saiso[i]=saiso[i+1];
              saiso[i+1]=temp;
              doi[i]=Person[i];
              Person[i]=Person[i+1];
              Person[i+1]=doi[i];
            }
          }
          printf("%3s\t%-25s\t%-10s\n","STT","Ho ten","Do sai lech");
            for(i=0;i<M;i++) printf("%3d\t%-25s\t%.4f\n",i+1,Person[i].Name,saiso[i]);
        }break;
		}
		if (chon == 4) break;
	} while (1);
}
