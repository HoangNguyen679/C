#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXL 20

typedef struct mobile_t{
  char model[MAXL];
  float storage;
  float scrSize;
  int price;
} mobile;

mobile nokia[100];

void clrBuff();
int GetMenu(void);
int PrintDB(mobile *, int);
int ImportTxt(char *);
int ImportDat(char *, int);
int Search(char *, int);


int main(int argc, char argv[]){
  int menu, amount=0;
  int option;
  char key[MAXL];
  do{
    switch(menu = GetMenu()){
      case 1:
      amount=ImportTxt("nokia");
      break;
      case 2:
      do{
       printf("   1. partial reading\n   2. Whole Reading\n   Your option: ");
       clrBuff();
       scanf("%d", &option);
     }while(option < 1 || option >2);

     amount=ImportDat("nokia", option);
     break;
     case 3:
     PrintDB(nokia, amount);
     break;
     case 4:
     printf("Enter Key: "); clrBuff(); scanf("%s", key);
     Search(key, amount);
     break;
   }
 }while(menu != 0);



 return 0;
}


//FUNCTION HERE
int PrintDB(mobile *nokia, int amount){
  int i=0;
  char c;

  printf("\n    %-8s  %-8s   %-8s   %-10s\n", "Model", "Storage(Mb)",
    "ScrSize(in)", "Price(VND)");
  for(i = 0; i < amount; i++){
    printf("%-2d  %-8s  %-12g  %-12.1f  %-10d\n", i+1, nokia[i].model, nokia[i].storage,
      nokia[i].scrSize, nokia[i].price);

    //Devide data into pages if there are many data
    //which is cannot be display in a whole page
    //Formulaly, Linux system terminal contain 24 Lines, just why i%23
    if((i%20) == 0 && i!=0) {
      printf("Press Return to continue page\n");
      clrBuff();
      //This will delay printf and wait user for enter a Return
      scanf("%c", &c);
      printf("   %-8s  %-8s  %-8s  %-10s\n", "Model", "Storage(Mb)",
        "ScrSize(in)", "Price(VND)");
    }
  }
  printf("--END--\n\n");
}


int ImportTxt(char *fileinName){
  FILE *fin, *fout;
  int i=0;

  //Open and Create file for read and write
  if((fin=fopen("Nokia.txt", "r")) == NULL) perror("ERROR");
  else if((fout=fopen("Nokia.dat","w")) == NULL) perror("ERROR");
  else{
    //Scan text file and Import to array
    while(!feof(fin)){
      fscanf(fin, "%s %f %f %d", nokia[i++].model, &nokia[i].storage,
        &nokia[i].scrSize, &nokia[i].price);
    }
  }
  //Write to file
  fwrite(nokia, sizeof(mobile), i, fout);

  //Close files
  fclose(fin);
  fclose(fout);
  printf("\n**Import Successfully**\n\n");
  int c; printf("Press Return to continue\n"); clrBuff(); scanf("%c", &c);
  //Return number of Phone  //amount
  return i;
}

int ImportDat(char *filename, int option){
  FILE *fin;
  int amount=0; //number of phone
  //Open *.dat file to read
  if((fin=fopen("Nokia.dat", "r")) == NULL) {
    perror("ERROR");
    return 0;
  }

  if(option == 2){
    amount = fread(nokia, sizeof(mobile), 100, fin);
    return amount;
  }
  else{
    int startPoint, endPoint;
    do{
     printf("Start at phone #: "); clrBuff(); scanf("%d", &startPoint);
     printf("End at phone #: "); clrBuff(); scanf("%d", &endPoint);
   }while(startPoint <= 0 || endPoint <= 0 || endPoint < startPoint);

      //Seek to the exactly start point - 1
   fseek(fin, (startPoint-1)*sizeof(mobile), SEEK_SET);
   amount = fread(nokia, sizeof(mobile), endPoint-startPoint+1, fin);
 }
 printf("\n**Import Successfully**\n");
 int c; printf("Press Return to continue\n"); clrBuff(); scanf("%c", &c);
 return amount;
}

int Search(char *name, int amount){
  int i;
  printf("Search Result:\n");
  for(i = 0; i < amount; i++){
    if(strcmp(name, nokia[i].model) == 0){
      printf("    %-8s  %-8s   %-8s   %-10s\n", "Model", "Storage(Mb)",
        "ScrSize(in)", "Price(VND)");
      printf("%-2d  %-8s  %-12g  %-12.1f  %-10d\n", i+1, nokia[i].model,
        nokia[i].storage, nokia[i].scrSize, nokia[i].price);
    }
    else("No match Found\n");
  }
}

/////Addition Function
void clrBuff(){
  char c;
  while((c=getchar()) !='\n' && c != EOF);
}


int GetMenu(void){
  int menu;
  do{
    printf("\n----MENU----\n");
    printf("1. Import DB from *.text\n");
    printf("2. Import DB from *.dat\n");
    printf("3. Print DB\n");
    printf("4. Search Mobile\n");
    printf("0. Exit\n");
    printf("Your choice: ");
    scanf("%d", &menu);
  }while(menu<0 || menu>=5);
  return menu;
}
