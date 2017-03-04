#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../di_graph.h"

#define MAX 80

Graph buildGraphFrom(FILE *file);

int main(int argc, char* argv[]){
  if(argc != 2) {
    printf("Please specify source file!\n");
    exit(1);
  }

  char file_name[MAX];
  FILE *file;

  strcpy(file_name, argv[1]);
  file = fopen(file_name, "r");
  if(file == NULL) {
    printf("Cannot open file \"%s\"!\n", file_name);
    exit(1);
  }

  Graph G;


  return 0;
}

Graph buildGraphFrom(FILE *file) {
  Graph G = create();

  char *sub = (char*)malloc(sizeof(char) * MAX );
  char *preSub = (char*)malloc(sizeof(char) * MAX );

}
