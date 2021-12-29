/*Citation:
https://beej.us/guide/bgnet/html/#getaddrinfoprepare-to-launch
https://www.youtube.com/watch?v=DboEGcU6rLI&ab_channel=Learning-X
https://www.youtube.com/watch?v=Emuw71lozdA
https://www.youtube.com/watch?v=Pg_4Jz8ZIH4&ab_channel=JacobSorber*/


#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <netdb.h>
#include "list.h"
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <pthread.h>



LIST *Send_list;
LIST *Receive_list;
struct sockaddr_in addr1, addr2;
char *host;
int Port1;
int Port2; 
int s;
char buffer1[256];
char buffer2[256];
pthread_mutex_t mutex;
pthread_cond_t send_msg;
pthread_cond_t recv_msg;
pthread_t keyboard_thread;
pthread_t send_thread;
pthread_t recv_thread;
pthread_t screen_thread;

void OpenSocket();
void *keyboard(void *ptr);
void *sendsocket(void *ptr);
void *recvsocket(void *ptr);
void *screen(void *ptr);


//initializing a socket
void OpenSocket(){
    struct hostent *host_name;
    host_name = gethostbyname(host);
    memset((char *)&addr1, 0, sizeof(addr1));
    addr1.sin_family = AF_INET; //set family type to AF_INET for IPv4
    addr1.sin_addr.s_addr = INADDR_ANY;
    addr1.sin_port = htons(Port1);
    memset(&addr1.sin_zero, '\0', 8);

    memset((char *)&addr2, 0, sizeof(addr2));
    addr2.sin_family = AF_INET; //set family type to AF_INET for IPv4
    addr2.sin_port = htons(Port2);
    memcpy((void *)&addr2.sin_addr, host_name->h_addr_list[0], host_name->h_length);
    

    //create socket;
    s = socket(AF_INET, SOCK_DGRAM,0);
    
    //bind socket
    bind(s, (struct sockaddr *)&addr1, sizeof(struct sockaddr_in));

    printf("create socket successfully!\n");
}


//keyboard input
void *keyboard(void *ptr){
    ptr = (char *)ptr;
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    while(1){
        //while first element of buffer1 equals NULL read the whole buffer1 list.
        do {
			read(0, buffer1, 256);
		} while (buffer1[0] == '\0');
        char *new_msg = malloc(257);
        strcpy(new_msg, buffer1); //copy the inpute message to buffer1
        pthread_mutex_lock(&mutex); //thread lock
        ListAdd(Send_list, new_msg);
        pthread_mutex_unlock(&mutex); //thread unlock
        pthread_cond_signal(&send_msg);
        memset(buffer1, 0, 256);
    }
    return NULL;
}

//send massage with sendto function
void *sendsocket(void *ptr){
    ptr = (char *)ptr;

    //infinite loop to get get user input
    while(1){
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&send_msg, &mutex);
        while(ListCount(Send_list) != 0){
            char *send_msg = ListTrim(Send_list);
            sendto(s, send_msg, strlen(send_msg), 0, (struct sockaddr *)&addr2, sizeof(struct sockaddr_in));
            // if input equals ! end the chat.
            if(send_msg[0] == '!'){
                pthread_mutex_unlock(&mutex);
                close(s);
                exit(0);
            }
            printf("send local\n");
        }
        pthread_mutex_unlock(&mutex);  
    }
    return NULL;
}

//receive massage with recvfrom function
void *recvsocket(void *ptr){
    ptr = (char *)ptr;
    socklen_t stringlen = sizeof(struct sockaddr_in);
    while(1){
        recvfrom(s, buffer2, 256, 0, (struct sockaddr *)&addr2, &stringlen);
        pthread_mutex_lock(&mutex); //thread lock
        char *new_msg = malloc(257);
        strcpy(new_msg, buffer2); //copy the inpute message to buffer2
        ListAdd(Receive_list, new_msg);
        memset(buffer2, 0, 256);
        pthread_mutex_unlock(&mutex); //thread unlock
        pthread_cond_signal(&recv_msg);
    }
    return NULL;
}

//print out massage with the write function
void *screen(void *ptr){
    ptr = (char *)ptr;
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    
    while(1){
        pthread_mutex_lock(&mutex); //thread lock
        pthread_cond_wait(&recv_msg, &mutex);
        
        while(ListCount(Receive_list)>0){
            char *writestring = (char *)ListTrim(Receive_list);
        write(0,writestring, strlen(writestring));
        printf("send by %s\n", host);
            if(writestring[0] == '!'){ 
                pthread_mutex_unlock(&mutex); //thread unlock
                printf("chat terminated!\n");
                close(s);
                exit(0);
            }
        } 
        pthread_mutex_unlock(&mutex); //thread unlock to continue next thread
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&send_msg, NULL);
    pthread_cond_init(&recv_msg, NULL);

    
    Send_list = ListCreate();
    Receive_list = ListCreate();

    host = argv[2]; //get hostname from the user argument input
    Port1 = atoi(argv[1]); //get local_port from the user argument input
    Port2 = atoi(argv[3]); //get remot_port from the user argument input

    OpenSocket();
    printf("Welcome to s-talk!\n");

    //create threads
    pthread_create(&keyboard_thread, NULL, keyboard, NULL);
    pthread_create(&send_thread, NULL, sendsocket, NULL);
    pthread_create(&recv_thread, NULL, recvsocket, NULL);
    pthread_create(&screen_thread, NULL, screen, NULL);
    //join threads
    pthread_join(keyboard_thread, NULL);
    pthread_join(send_thread, NULL);
    pthread_join(recv_thread, NULL);
    pthread_join(screen_thread, NULL);

    return 0;
}
