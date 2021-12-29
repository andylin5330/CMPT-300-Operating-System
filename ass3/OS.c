#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "OS.h"

LIST *JobQ;
LIST *HighreadyQ;
LIST *NormalreadyQ;
LIST *LowreadyQ;
LIST *MsgQ;
LIST *BlockedQ;
LIST *CurrentQ;
int id;
int newid;
PCB *runningPCB;
PCB *currunningPCB;
PCB *controlB;
PCB *newcontrolB;
SEMAPHORE *s[5];


void init(){
    HighreadyQ = ListCreate();
    NormalreadyQ = ListCreate();
    LowreadyQ = ListCreate();
    MsgQ = ListCreate();
    JobQ = ListCreate();
    BlockedQ = ListCreate();
    CurrentQ = ListCreate();
    printf("test1\n");
    return;
}

//command c 
int createP(int priority){
    controlB = (PCB *)malloc(sizeof(PCB));
    id = ListCount(JobQ)+1;
    controlB->PID = id;
    controlB->priority = priority;
    controlB->cond = true;
    if(priority == 0){
        ListAppend(HighreadyQ,controlB);
    }
    if(priority == 1){
        ListAppend(NormalreadyQ,controlB);
    }
    if(priority == 2){
        ListAppend(NormalreadyQ,controlB);
    }
    ListAppend(JobQ,controlB);
    printf("process create successfully.\n");
    printf("job queue # is: %d\n", id);
    return controlB->PID;
} 

//command f
int forkP(){
    newcontrolB = (PCB *)malloc(sizeof(PCB));
    newcontrolB->PID = newid;
    newid++;
    newcontrolB->priority = controlB->priority;
    newcontrolB->storeMsg = NULL;
    if(newcontrolB->priority == 0){
        ListAppend(HighreadyQ,controlB);
    }
    if(newcontrolB->priority == 1){
        ListAppend(NormalreadyQ,controlB);
    }
    if(newcontrolB->priority == 2){
        ListAppend(NormalreadyQ,controlB);
    }
    return newcontrolB->PID;
}

//command k
int killP(int pid){
    if(pid == controlB->PID){
        if(controlB->priority == 0){
            ListRemove(HighreadyQ);
        }
        else if(controlB->priority == 1){
            ListRemove(NormalreadyQ);
        }
        else{
            ListRemove(LowreadyQ);
        }
    }
    return 1;

}

//command e
int exitP(){
    ListRemove(CurrentQ);
    return 1;
}

//command q
int QuantumP(){
    int priority = runningPCB->priority;
    if(priority == 0){
        ListAppend(HighreadyQ,runningPCB);
    }
    else if(priority == 1){
        ListAppend(NormalreadyQ,runningPCB);
    }
    else{
        ListAppend(LowreadyQ,runningPCB);
    }
    if(ListCount(HighreadyQ)>0){
        PCB *newprocess = ListTrim(HighreadyQ);
        runningPCB = newprocess;
        runningPCB->state = "running";
        return newprocess->PID;
    }
    if(ListCount(NormalreadyQ)>0){
        PCB *newprocess = ListTrim(NormalreadyQ);
        runningPCB = newprocess;
        runningPCB->state = "running";
        return newprocess->PID;
    }
    if(ListCount(LowreadyQ)>0){
        PCB *newprocess = ListTrim(LowreadyQ);
        runningPCB = newprocess;
        runningPCB->state = "running";
        return newprocess->PID;
    }
    return runningPCB->PID;
}

//command s
int sendP(int pid, char *msg){
    PCB *findprocess;
    while(findprocess != (PCB *)ListTrim(JobQ)){
        findprocess = findprocess->PID;
        return findprocess->PID;
    }
}

//command r
void receiveP(){
    printf("Receiving message.\n");
    return 0;
}

//command y
void replyP(int pid, char *msg){
    printf("Reply message.\n");
    return 0;
}

//command n
int iniSem(int semephore, int initvalue){
    return 0;
}

//command p
void semIDP(int semephore, int initvalue){
    return 0;
}

//command v
void semIDV(int semephore){
    return 0;
}

//command i
void procIN(int pid){
    return 0;
}

//command t
void totalINF(){
    if(ListCount(HighreadyQ) == 0){
        printf("no process is in the queues");
    }
    else{
        ListFirst(HighreadyQ);
        for(int i=0; i<ListCount(HighreadyQ); i++){
            PCB *process = (PCB *)ListCurr(HighreadyQ);
            printf("%d, ", process->PID);
            ListNext(HighreadyQ);
        }
        printf("\n");
    }
    if(ListCount(NormalreadyQ) == 0){
        printf("no process is in the queues");
    }
    else{
        ListFirst(NormalreadyQ);
        for(int i=0; i<ListCount(NormalreadyQ); i++){
            PCB *process = (PCB *)ListCurr(NormalreadyQ);
            printf("%d, ", process->PID);
            ListNext(NormalreadyQ);
        }
        printf("\n");
    }
    if(ListCount(LowreadyQ) == 0){
        printf("no process is in the queues");
    }
    else{
        ListFirst(LowreadyQ);
        for(int i=0; i<ListCount(LowreadyQ); i++){
            PCB *process = (PCB *)ListCurr(LowreadyQ);
            printf("%d, ", process->PID);
            ListNext(LowreadyQ);
        }
        printf("\n");
    }

    if(ListCount(BlockedQ) == 0){
        printf("no process is in the queues");
    }
    else{
        ListFirst(BlockedQ);
        for(int i=0; i<ListCount(BlockedQ); i++){
            PCB *process = (PCB *)ListCurr(BlockedQ);
            printf("%d, ", process->PID);
            ListNext(BlockedQ);
        }
        printf("\n");
    }

    if (runningPCB != NULL){
        printf("The running process ID is %d, Priority: %d, State: %s\n", runningPCB->PID, runningPCB->priority, runningPCB->state);
    }
    else{
        printf("The init process ID is %d, Priority: %d, State: %s\n", runningPCB->PID, runningPCB->priority, runningPCB->state);
    }
    return 0;
}


int main(){
    int temp;
    init();
    char inputC;
    char *inputKill;
    char *msg[40];
    int *id;
    int *semep;
    int *initvalue;
    int *pid;
    printf("Type in the correspending character for specific process.\n");
    scanf("%c", &inputC);
    while(1){
        switch(inputC){
            case 'c':
            case 'C':
                printf("command C activated\n");
                printf("insert number 0 or 1 or 2 for creating a corresponding process.\n");
                printf("Insert 0 for High priority process\n");
                printf("Insert 1 for Normal priority process\n");
                printf("Insert 2 for Low priority process.\n");
                int inputCreate = scanf("%d", &temp);
                createP(inputCreate); 
                break;
            
            case 'f':
            case 'F':
                printf("command F activated\n");
                forkP();
                break;
            
            case 'k':
            case 'K':    
                printf("command K activated\n");
                printf("Type in the relatited process id to that you want to kill.");
                scanf("c\n",&inputKill);
                killP(inputKill);
                break;

            case 'e':
            case 'E':
                printf("command E activated\n");
                exitP();
                break;

            case 'q':
            case 'Q':
                printf("command Q activated\n");
                QuantumP();
                break;

            case 's':
            case 'S':
                printf("command S activated\n");
                printf("please type in the process you want to send to.\n");
                scanf("%d\n",&id);
                printf("Please type in the message you want to send.\n");
                scanf("%s\n",msg);
                sendP(id, msg);
                break;

            case 'r':
            case 'R':
                printf("command R activated\n");
                receiveP();
                break;
            
            case 'y':
            case 'Y':
                printf("command Y activated\n");
                printf("please type in the process you want to reply to.\n");
                scanf("%d\n",&id);
                printf("Please type in the message you want to reply.\n");
                scanf("%s\n",msg);
                replyP(id, msg);
                break;
            
            case 'n':
            case 'N':
                printf("command N activated\n");
                printf("please type in the semephore you want to have.");
                scanf("%d\n",&semep);
                printf("please type in the initial value you want to have.");
                scanf("%d\n",&initvalue);
                iniSem(semep, initvalue);
                break;
            
            case 'p':
            case 'P':
                printf("command P activated\n");
                printf("please type in the semephore you want to have.");
                scanf("%d\n",&semep);
                printf("please type in the initial value you want to have.");
                scanf("%d\n",&initvalue);
                semIDP(semep, initvalue);
                break;
            
            case 'v':
            case 'V':
                printf("command V activated\n");
                printf("please type in the semephore you want to have.");
                scanf("%d\n",&semep);
                semIDV(semep);
                break;
            
            case 'i':
            case 'I':
                printf("command I activated\n");
                printf("please type in the process id that you want to see the information of it.\n");
                scanf("%d",&pid);
                procIN(pid);
                break;

            case 't':
            case 'T':
                printf("command T activated\n");
                totalINF();
                break;
        }
    return 0;
    }
}