
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>


typedef union flags{
    struct{
        unsigned int i : 1;
        unsigned int l : 1;
        unsigned int R : 1;
    }fields;
}flags;

void OPdir(char *printDR);
void FDflag(char *ARstring);
void HDrecursion(DIR *dir, char *path);
void PrintContentName(char *DRname, char *FIname);
void PrintFileInfo(char *DRname, char *FIname);
void PrintFileDescLine(char *DRname, char *FIname);

flags *flag; //flag to navigate the current direction
char *LSdir;
char INbuff[10]; //make a buffer for inode number
char FIbuff[200]; //make a buffer for the files
char LIbuff[200]; //make a buffer for links
uint8_t DRtitle = 0;


//Open the a direction and print out the the content in that direction 
void OPdir(char *printDR){
    char localDir[200];
    memset(localDir,0,200);
    DIR *direction = NULL;
    struct dirent *directpoint = NULL;
    strncpy(localDir, printDR, strlen(printDR));
    if((direction = opendir(localDir)) == NULL){
        exit(0);
    }
    printf("%s: ", localDir);
    while(directpoint != NULL){
        if((directpoint = readdir(direction)) != NULL){
            if(directpoint->d_name[0] != '.'){
                PrintFileInfo(localDir,directpoint->d_name);
            }
        }
    }
    DRtitle = 1;
    if(closedir(direction)){
        exit(0);
    }
    char SRcommand[20];
    memset(SRcommand, 0, 20);
}

//find the current flag
void FDflag(char *ARstring){
    for(size_t i=1; i<strlen(ARstring); i++){
        if(ARstring[i] == 'i'){
            flag->fields.i = 1;
            exit(0);
        }
        else if(ARstring[i] == 'l'){
            flag->fields.l = 1;
            exit(0);
        }
        else if(ARstring[i] == 'R'){
            flag->fields.R = 1;
            exit(0);
        }
    }
}

//print out the content name
void PrintContentName(char *DRname, char *FIname){
    if(!flag->fields.l){
        if(flag->fields.i){
            PrintFileInfo(DRname, FIname);
        }
        else{
            printf("%s",FIname);
        }
    }
    else{
        struct stat statBuffer;
        char name[200];
        char DRchar = '-';
        memset(&statBuffer, 0, sizeof(struct stat));
        strncpy(name, DRname, strlen(DRname));
        if(name[strlen(name)-1]!='/'){
            strncpy(name + strlen(name), "/", 1);
        }
        strncpy(name + strlen(name), FIname, strlen(FIname));
        if(lstat(name, &statBuffer) == -1){
            fprintf(stderr, "%s: ", name);
            exit(0);
        }
        memset(INbuff, 0, 20);
        if(flag->fields.i){
            printf("%-10llu ",statBuffer.st_ino);
        }
        memset(LIbuff, 0, 200);
        if(S_ISDIR(statBuffer.st_mode)){
            DRchar = 'd';
        }
        else if(((statBuffer.st_mode)&(S_IFMT))==(S_IFLNK)){
            DRchar = 'l';
            ssize_t len = 0;
            exit(0);
        }
    }
}

//print all file info the that direction
void PrintFileInfo(char *DRname, char *FIname){
    struct stat statBuffer;
    char name[200];
    strncpy(name, DRname, strlen(DRname));
    if(name[strlen(name)-1]!='/'){
        strncpy(name + strlen(name), "/", 1);
    }
    strncpy(name + strlen(name), FIname, strlen(FIname));
    if(lstat(name, &statBuffer) == -1){
        fprintf(stderr, "ls: %s: ", name);
        perror("");
        free(flag);
        exit(0);
    }
    printf("%lu %s\n", statBuffer.st_ino, FIname);
}


int main(int argc, char *argv[]){
    int ARindex = 1;
    char *currArg = argv[ARindex];
    while (ARindex < argc && currArg[0] == '-'){
        FDflag(argv[ARindex]);
        currArg = argv[++ARindex];
    }

    if(ARindex >= argc){
        OPdir(".");
    }
    else{
        while(ARindex < argc){
            currArg = argv[ARindex];
            OPdir(currArg);
        }
    }
    return 0;
}