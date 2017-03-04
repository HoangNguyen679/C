#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "di_graph.h"

void menu1();
void menu2();
void menu3();
void MENU(int *);
void GraphInit();

Graph A;
int main()
{
  A = createGraph();
  GraphInit();
  int menu;
  do {
    MENU(&menu);
    switch (menu)
      {
      case 1: menu1(); break;
      case 2: menu2(); break;
      case 3: menu3(); break;
      case 4: printf("Ket thuc chuong trinh\n");
      }
  } while (menu != 4);
  dropGraph(A);
}
///////////////////////////////////////////////////
void MENU(int *c)
{
  printf("########################################################\n");
  printf("# -:- isling -:-                                       #\n");
  printf("########################################################\n");
  printf("                          MENU");
  printf("\n1, Kiem tra chu trinh");
  printf("\n2, Cach chon trang phuc");
  printf("\n3, Do can mac truoc 1 do gi do");
  printf("\n4, Thoat");
  printf("\n\tBan chon: ");
  scanf("%d",c); getchar();
  while (*c < 1 || *c > 4)
    {
      printf("\nBan chon sai. Chon lai: ");
      scanf("%d",c);
      DEL();
    }
}
void GraphInit(){
  addVertex(A, 1, strdup("So mi"));
  addVertex(A, 2, strdup("Quan dai"));
  addVertex(A, 3, strdup("Giay"));
  addVertex(A, 4, strdup("Tat"));
  addVertex(A, 5, strdup("That lung"));
  addVertex(A, 6, strdup("Do lot"));
  addEdge(A, 4, 3);
  addEdge(A, 6, 1);
  addEdge(A, 6, 2);
  addEdge(A, 2, 5);
  addEdge(A, 2, 3);
}

void menu1()
{
  if (is_cyclic(A) == 0)
    printf("Do thi khong co chu trinh\n");
  else printf("Do thi co chu trinh\n");
}

void menu2()
{
  int output[100], n, i;
  Tsort(A, output, &n);
  if (n == -1)
    {
      printf("Ban khong the mac duoc trang phuc\n");
      return;
    }
  printf("Thu tu mac trang phuc: ");
  for (i=0; i<n; i++)
    {
      printf("%d, %s\t",i+1,getVertex(A, output[i]));
    }
  printf("\n");
}
int print(int v)
{
  printf("%s\t", getVertex(A, v));
}
void menu3()
{
  char s[20];
  int v;
  BFS(A, 6, print);
  printf("\n");
  do
    {
      printf("Ban muon kiem tra do nao: ");
      scanf("%[^\n]", s); getchar();
    } while ((v = getID(A, s)) == -1);
  int output[100], n, i;
  allInDegree(A, v, output, &n);
  for (i=n-1; i>=0; i--) printf("%s\t", getVertex(A, output[i]));
  printf("\n");
}
