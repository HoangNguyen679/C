#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"queue_list.h"

void creatNewProgram(node **root,char str[MAX],long memo, long *sum);
void killProgram(node **root,char *str2,long *sum);

node *root=NULL;
queue q;
int p;
long max,memo,sum=0;
char str[MAX],str2[MAX];

int main()
{
  int ch;
  queueConstruct(&q);
  printf("\n\n>>>>>>>>>>INPUT<<<<<<<<<\n\n");
  printf("Enter number of parallel process CPU can run: ");scanf("%d",&p);
  printf("Enter memory capacity: ");scanf("%ld",&max);

  do
    {
      printf("\n\nMENU\n\n");
      printf("1. Creat new program\n");
      printf("2. Kill a program\n");
      printf("3. Show status\n");
      printf("4. Exit\n\n");
      printf("Please select: ");scanf("%d",&ch);getchar();
      switch(ch)
        {
        case 1:
          {
            printf("Enter the ID: ");gets(str);
            printf("Enter the memory of %s: ",str);scanf("%ld",&memo);getchar();
            creatNewProgram(&root,str,memo,&sum);
          }break;
        case 2:
          {
            printf("Enter the ID you want to kill: ");gets(str2);
            killProgram(&root,str2,&sum);
          }break;
        case 3:
          printf("\n\n>>>>>>>>>>RUNNING<<<<<<<<<\n\n");
          printList(root);
          printf("\n\n>>>>>>>>>>WAITING<<<<<<<<<<\n\n");
          printQueue(q);
          break;
        case 4: return;
        default: printf("Wrong choice\n\n");
        }
    } while(1);
  return 0;
}


void creatNewProgram(node **root,char str[MAX],long memo,long *sum)
{
  inf data;
  strcpy(data.ID,str);
  data.memory = memo;
  *sum += memo;
  int n=0;
  n = size(*root);
  if(memo > max)
    {
      printf("Chuong trinh qua nang, CPU khong tai noi\n");
      *sum-=memo;
      return;
    }
  if(n>p)
    {
      printf("CPU dang nong,process se duoc cho vao hang doi");
      *sum-=memo;
      enqueue(&q,data);
      return ;
    }
   if(*sum > max)
    {
      printf("CPU dang nong,process se duoc cho vao hang doi\n");
      *sum-=memo;
      enqueue(&q,data);
      return;
    }
   if(!isEmpty_queue(q))
     {
       printf("Process thu tu uu tien thapp hon, cho vao hang doi\n");
       *sum-=memo;
       enqueue(&q,data);
       return;
     }
   insert(root,data);
}
void killProgram(node **root,char str2[MAX],long *sum)
{
  node *temp,*temp2;
  int j=0;
  if (*root == NULL)
    {printf("NOTHING TO KILL\n");return;}
  for(temp = *root; temp != NULL; temp = temp->next )
    if(strcmp(temp->data.ID,str2) == 0)
      {
        j++;
        *sum -= temp->data.memory;
        // xoa temp;
        if(temp == *root)
          {
            if((*root)->next == NULL)
	      {
            *root = NULL;
            free(temp);
	      }
            else
              {
                *root = (*root)->next;
                free(temp);
              }
          }
        else
          {
            for(temp2=*root;temp2->next != temp; temp2= temp2->next);
            temp2->next = temp->next;
            if(temp->next != NULL) temp->next->prev = temp2;
            free(temp);
            break;
          }
      }
  if(j==0){printf("Khong co process giong nhu ban da nhap\n");return;}
  int n = size(*root);
  while(!isEmpty_queue(q) && (*sum +q.front->data.memory) <= max)
    {
      inf thu;
      thu = dequeue(&q);
      *sum += thu.memory;
      insert(root,thu);
    }
}
