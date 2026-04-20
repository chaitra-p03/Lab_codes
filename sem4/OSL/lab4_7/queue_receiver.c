#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg_st {
    long int type;
    char text[BUFSIZ];
};

int main() {
    int running = 1;
    int msgid;
    struct my_msg_st m;
    
    msgid = msgget(1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    while(running) {
        msgrcv(msgid, (void *)&m, BUFSIZ, 0, 0);
        printf("You wrote: %s", m.text);
        
        if (strncmp(m.text, "end", 3) == 0) {
            running = 0;
        }
    }
    
    msgctl(msgid, IPC_RMID, 0);
    
    exit(EXIT_SUCCESS);
}