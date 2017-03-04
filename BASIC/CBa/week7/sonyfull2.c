#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"doublelinkedlist.h"
#define MAX  81

/*
void splitList(int n,int m) {
  if(n < 0 || root == NULL) {
    printf("Loi!/n");
    return ;
  }

  int i,j=0;
  node *tmp,*tmp2;
  for(tmp = root ; tmp != NULL ; tmp = tmp->next) j++;
  if(n+m > j || m > (j-n+1)) {
    printf("Danh sach co %d phan tu",j);
    return ;
  }

  tmp=root;
  for(i = 0 ; i < n-1 ; i++) tmp = tmp->next;
  root2 = tmp->next;
  tmp2=root2;
  for(i = 0 ; i < m-1 ; i++) tmp2 = tmp2->next;
  tmp->next = tmp2->next;
  tmp2->next = NULL;
  return ;
}

void splitList2(int n) {
  if(n < 0 || root == NULL) {
    printf("Loi!/n");
    return ;
  }

  int i,j=0;
  node *tmp,*tmp2;
  for(tmp = root ; tmp != NULL ; tmp = tmp->next) j++;
  if(n > j) {
    printf("Danh sach co it hon %d phan tu",n);
    return ;
  }

  tmp = root;
  for(i = 0 ; i < n-1 ; i++) tmp = tmp->next;
  root2 = tmp->next;
  tmp2 = root2;
  tmp->next = NULL;
  return;
}
*/

int main() {
  doublelist root1,tail1,cur1;
  MakeNullList(&root1,&tail1,&cur1);
  do {
    printf("MENU\n");
    printf("1. Import from DB\n");
    printf("2. Display\n");
    printf("3. Add a new phone\n");
    printf("4. Insert at Position\n");
    printf("5. Delete at Position\n");
    printf("6. Delete current \n");
    printf("7. Delete first\n");
    printf("8. Search and Update\n");
    printf("9. Devide and Extract\n");
    printf("10. Reserve List\n");
    printf("11. Save to file\n");
    printf("12. Quit\n\n");
    int chon;
    printf("Please select: ");
    scanf("%d",&chon);getchar();
    if(chon == 12){
      printf("Bye bye :p See you again\n");
      break;
    } // quit

    char filedat[]="sony.dat";
    FILE *f,*fout;
    info *phone;

    switch(chon){

    case 1: {
      info tmp;
      if( (f = fopen(filedat,"rb")) == NULL) {
        printf("Cannot open %s",filedat);
        return 1;
      } // mo file dat
      while(feof(f) == 0) {
        fread(&tmp,sizeof(info),1,f);
        insertAfterCur(tmp,&root1,&cur1,&tail1);
      }
    } break; // het case 1.1

    case 2: {
      traversingList(root1);
    } break; // het case 2.1

    case 3: {
      do {
        printf("Add a new phone\n");
        printf("1. Add before\n");
        printf("2. Add after\n");
        printf("3. Quit\n\n");

        int chon3;
        printf("Please select: ");scanf("%d",&chon3);getchar();

        if(chon3 == 3) break;
        switch(chon3) {

        case 1: {
          info tmp31;
          tmp31 = readNode();
          insertBeforeCur(tmp31,&root1,&cur1,&tail1);
          traversingList(root1);
        } break;

        case 2: {
          info tmp32;
          tmp32 = readNode();
          insertAfterCur(tmp32,&root1,&cur1,&tail1);
          traversingList(root1);
        } break;

        }
      }while(1); // het vong do case 3
    } break; // het case 3.1
      /*
    case 4: {
      int placeToInsert;
      info tmp4;
      tmp4 = readNode();

      printf("Enter place to insert:");
      scanf("%d",&placeToInsert);getchar();

      insertAtPosition(root,tmp4,placeToInsert);
      traversingList(root);
    } break; // het case 4.1
      */
      /*
    case 5: {
      int placeToDel;
      printf("Enter place to del:");
      scanf("%d",&placeToDel);
      delAtPosition(root,placeToDel);
      traversingList(root);
    } break; // het case 5.1
      */

    case 6: {
      delCur(&root1,&cur1,&tail1);
      traversingList(root1);
    } break; // het case 6.1

    case 7: {
      delFirst(&root1);
      traversingList(root1);
    } break; // het case 7.1

    case 8: {
      do {
        printf("Search and update\n");
        printf("1. Search\n");
        printf("2. Update\n");
        printf("3. Quit\n\n");
        printf("Please select: ");

        int chon8;
        scanf("%d",&chon8);getchar();
        if(chon8 == 3) break;
        switch(chon8) {
        case 1: {
          char test[MAX];
          printf("Enter the model ( with lower-case ): ");
          gets(test);
          int j=0;
          node *tmp = NULL;
          for(tmp = root1 ; tmp != NULL ; tmp = tmp->next){
            if(strcmp((tmp->e).model,test) == 0) {
              displayNode(tmp);
              j++;
            }
          }
          if(j == 0) printf("No model like you enter\n");
        } break;
        case 2: {} break;
        }
}while(1);
    } break; // het case 8.1
      /*
    case 9: {
      do {
        printf("Devide and Extract\n");
        printf("1. Devide\n");
        printf("2. Extract\n");
        printf("3. Quit\n\n");

        int chon9;
        printf("Please select: ");
        scanf("%d",&chon9);
        if(chon9 == 3) break;
        switch(chon9) {

        case 1: {
          int start,number;
          printf("Enter from element: ");scanf("%d",&start);
          printf("List 2 has ... element: ");scanf("%d",&number);
          splitList(start,number);

          printf("List 1\n");printNode(root);printf("\n");
          printf("List 2\n");printNode(root2);printf("\n");
        } break;

        case 2: {
          int dividePoint;
          printf("Enter devidePoint: ");scanf("%d",&dividePoint);
          splitList2(dividePoint);

          printf("List 1\n");printNode(root);printf("\n");
          printf("List 2\n");printNode(root2);printf("\n");
        } break;
        }//het vong switch
      }while(1); //het vong do trong case 9
    } break; // het case 9.1 */

    case 10: {} break; // het case 10.1

    case 11: { } break; // het case 11.1
    } // het vong switch

  }while(1); //het vong lap do lon nhat
  return 0;
}
