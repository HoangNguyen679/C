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

Student bangDiem[1000];

int main(int argc, char **argv){
	FILE *foutbin;
	int i;
	foutbin = fopen(argv[1], "rb");

	int irc= fread(bangDiem, sizeof(Student), 100, foutbin);
	for(i = 0; i < irc; i++){
		printf("%-2d %-20s %-2d\n", bangDiem[i].id, bangDiem[i].name, bangDiem[i].grade);
	}
	printf("\nFREAD: %d\n", irc);
	fclose(foutbin);
	return 0;
}
