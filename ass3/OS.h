#include "list.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int PID;
    int priority;
    bool cond;
    char *state;
    char *storeMsg;
}PCB;

typedef struct{
    int value;
    PCB *waitinglist;
}SEMAPHORE;



int createP(int priority);
int forkP();
int killP(int pid);
int exitP();
int  QuantumP();
int sendP(int pid, char *msg);
void receiveP();
void replyP(int pid, char *msg);
int iniSem(int SID, int INIT);
void semIDP(int semephore, int initvalue);
void semIDV(int semephore);
void procIN(int pid);
void totalINF();