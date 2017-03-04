#include <stdio.h>
#include <stdlib.h>

typedef struct ElementType_t{
    int id;
    int memory;
} ElementType;

#include "QueueLLLib.h"

QueueType Running;
QueueType Waiting;

int mProcess;
int mMemory;

void clrBuff(void);
int GetMenu(void);
ElementType MakeProcess(void);
int CheckRunningStatus(ElementType newProcess);
void CreateProgram(void);
void KillProcess(void);
void PrintProcess(ElementType e);
void Traverse(QueueType *Q);
void ShowStatus(void);




int main(int argc, char const **argv){
    printf("Maximum Processes: "); scanf("%d", &mProcess);
    printf("Maximun Memory: "); scanf("%d", &mMemory);

    int menu;

    do{
        switch(menu = GetMenu()){
        case 1:
        CreateProgram();        
        break;

        case 2:
        KillProcess();
        break;

        case 3:
        ShowStatus();
        break;
        }
    } while(menu != 0);

    FreeQueue(&Running);
    FreeQueue(&Waiting);
    return 0;
}

void clrBuff(){
  while(getchar()!='\n');
}

int GetMenu(void){
    char menu[10];
    int menuOp = -1;
    do{
        printf("\n----MENU----\n");
        printf("1. Create New Program\n");
        printf("2. Kill Process\n");
        printf("3. Show Status\n");
        printf("0. Exit\n");
        printf("Your Option: ");
        clrBuff(); scanf("%s", menu);
        if (menu[0]>='0' && menu[0]<='9') menuOp=menu[0]-'0';
    } while (menuOp < 0 || menuOp > 3);
    
    return menuOp;
}


ElementType MakeProcess(void){
    ElementType temp;

    printf("ID: "); clrBuff(); scanf("%d", &temp.id);
    printf("Memory: "); clrBuff(); scanf("%d", &temp.memory);
    return temp;
}

int CheckRunningStatus(ElementType newProcess){
    int numberRunningProcess = 0;
    int totalRunningMemory = 0;
    node *p;
    
    for(p=(&Running)->front; p!=NULL; p=p->next) {
        numberRunningProcess++;
        totalRunningMemory += p->element.memory;
    }
    
    if(numberRunningProcess < mProcess && (totalRunningMemory+newProcess.memory) <= mMemory)
        // totalRunningMemory is total of ran memory, this must be + memory of newProcess to check condition of available of memory
        // if this sum < maxMemory, newProcess is able to run
        return 1;

    return 0;
}

void CreateProgram(void){
    EnQueue(MakeProcess(), &Waiting);
    printf("PROGRAM CREATED!\n");
    while(!IsEmpty(&Waiting) && CheckRunningStatus(Waiting.front->element)==1) EnQueue(DeQueue(&Waiting), &Running);
}

void KillProcess(void){
    if(IsEmpty(&Running)) {
        printf("No Process Running!\n");
        return;
    }
    DeQueue(&Running);
    printf("PROCESS KILLED!\n");
    while(!IsEmpty(&Waiting) && CheckRunningStatus(Waiting.front->element)==1) EnQueue(DeQueue(&Waiting), &Running);
}

void PrintProcess(ElementType e){
    printf("ID: %d - Memory: %d\n", e.id, e.memory);
}

void Traverse(QueueType *Q){
    node *p;
    for(p=Q->front; p!=NULL; p=p->next)
        PrintProcess(p->element);
}


void ShowStatus(void){
    printf("\nRUNNING:\n");
    Traverse(&Running);
    printf("\nWAITING:\n");
    Traverse(&Waiting);
    printf("\n");
}

