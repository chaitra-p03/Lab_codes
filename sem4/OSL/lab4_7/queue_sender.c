#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st {
    long int type;
    char text[MAX_TEXT];
};

int main() {
    int running = 1;
    struct my_msg_st m;
    int msgid;
    char buffer[BUFSIZ];
    
    msgid = msgget(1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    while(running) {
        printf("Enter some text:");
        fgets(buffer, BUFSIZ, stdin);
        
        m.type = 1;
        strcpy(m.text, buffer);
        
        msgsnd(msgid, (void *)&m, MAX_TEXT, 0);
        
        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
    }
    
    exit(EXIT_SUCCESS);
}