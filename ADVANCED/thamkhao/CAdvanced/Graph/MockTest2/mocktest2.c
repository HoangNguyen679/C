#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "di_w_graph.h"

#define MAX 80

char getMenu();
void clear_buffer();
Graph buildGraph(FILE *file);

int main(int argc, char const *argv[])
{
	char choice;
	char file_name[MAX] = "flight.txt";
	FILE *file;

	file = fopen(file_name, "r");
	if(file == NULL) {
		printf("Cannot open file \"%s\"!\n", file_name);
		exit(1);
	}

	Graph G;

	while (1)
	{
		clear_buffer();
		choice = getMenu();

		switch (choice)
		{
			case '1':
			{
				G = buildGraph(file);


				break;
			}
			case '2':
			{
				break;
			}
			case '3':
			{
				break;
			}
			case '4':
			{
				break;
			}
			case '5':
			{
				break;
			}
			case '6':
			{
				break;
			}
			case '7':
			{
				break;
			}
		    case '8'://Exit
		    {
		    	printf("Thoat...\n");
		    	return 0;
		    	break;
		    }
		    default:
		    {
		    	printf("Khong hop le!\n");
		    	break;
		    }
		}
	}

	return 0;
}

void clear_buffer ()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

char getMenu()
{
	char choice;

	printf("----------------------------------------------------------\n");
	printf("\t.================================.\n");
	printf("\t*    1.Thong tin chuyen bay      *\n");
	printf("\t*    2.Thong ke                  *\n");
	printf("\t*    3.Tim chuyen bay thang      *\n");
	printf("\t*    4.So duong bay nhieu nhat   *\n");
	printf("\t*    5.Kiem tra hanh trinh       *\n");
	printf("\t*    6.Tim thanh phan lien thong *\n");
	printf("\t*    7.Tim lo trinh toi uu       *\n");
	printf("\t*    8.Thoat                     *\n");
	printf("\t*================================*\n");

	printf("\t\tNhap lua chon: ");
	scanf("%c",&choice);
	printf("----------------------------------------------------------\n");

	return choice;
}

Graph buildGraph(FILE *file) {
	Graph G = create();

	char abbr[MAX];
	char fullname[MAX];
	char c1[MAX], c2[MAX];
	double w;

	do {
		fscanf(file,"%[^=\"]=\"%[^\"]\"\n", abbr, fullname);
		if(strlen(abbr) == 3) {
			printf("abbr = %s full = %s\n", abbr, fullname);	
			addVertex(&G, abbr, fullname);
		} 
		// else {
		// 	fseek(file, -strlen(abbr), SEEK_CUR);
		// 	while(!feof(file))
		// 		fscanf(file, "%s %s %lf\n", c1, c2, &w);
		// 	// printf("c1: %s c2 = %s w = %.2lf\n", c1, c2, w);
		// }
	} while(strlen(abbr) == 3);

	return G;
}