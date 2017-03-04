#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAXL 20

typedef struct Student_t{
	int id;
	char name[MAXL];
	int grade;
} Student;

Student *bangDiem;

int ReadData(FILE *fin){
	int i= 0, j= 0;
	while(feof(fin)== 0) {
		fscanf(fin, "%d %s", &bangDiem[i++].id, bangDiem[i].name);
	}
	for(j=0; j< i-1; j++){
		do{

			bangDiem[j].grade = rand()%10;
	  /*MANUAL INPUT
	  printf("Grade of student %d: ", bangDiem[j].id);
	  scanf("%d", &bangDiem[j].grade);
	  */
	}
	while(bangDiem[j].grade <0 || bangDiem[j].grade> 10);
}
  return i-1; //return number of student
}

int StudentCount(FILE *fin){
	int count = 0;
	char s[MAXL];
	while(feof(fin)== 0) {
		fgets(s, 100, fin); count++;
	}
  //printf("%d", count);
	return count-1;
}

int main(int argc, char **argv){
	srand((unsigned)time(NULL));
	FILE *fin, *fout, *foutbin;
	int i;
	if(argc != 3) printf("Invaild argument!\n");
	else if((fin = fopen(argv[1], "r")) == NULL) perror("ERROR");
	else if((fout = fopen(argv[2], "w")) == NULL) perror("ERROR");
	else{
		int numberOfStudent=StudentCount(fin);

		bangDiem = (Student*)malloc(sizeof(Student)* numberOfStudent);
		fin = fopen(argv[1], "r");
		ReadData(fin);

		for(i = 0; i <= numberOfStudent; i++){
	  //printf("%-2d %-20s %-2d\n", bangDiem[i].id, bangDiem[i].name, bangDiem[i].grade);
			fprintf(fout, "%-2d %-20s %-2d\n", bangDiem[i].id, bangDiem[i].name, bangDiem[i].grade);
		}


		foutbin = fopen("grade.dat", "wb");
		fwrite(bangDiem, sizeof(Student), numberOfStudent+1, foutbin);
		fclose(foutbin);

		free(bangDiem);

		Student bangDiemRead[100];
		foutbin = fopen("grade.dat", "rb");
		fread(bangDiemRead, sizeof(Student), numberOfStudent, foutbin);
		for(i = 0; i < numberOfStudent; i++)
			printf("%-2d %-20s %-2d\n", bangDiemRead[i].id, bangDiemRead[i].name, bangDiemRead[i].grade);

	// free(bangDiem);
		int fcloseall();
		return 0;
	}
}
