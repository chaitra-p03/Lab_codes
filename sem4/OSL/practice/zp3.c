#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX 20

struct msg1 {
    long type;
    int n;
};

struct msg2 {
    long type;
    int id;
    int pages;
};

int main(){
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    // send n first
    struct msg1 m1;
    m1.type = 1;
    m1.n = n;
    msgsnd(msgid, &m1, sizeof(m1) - sizeof(long), 0);

    // send all student data
    struct msg2 m2;
    int id, pages;
    for(int i = 0; i < n; i++){
        printf("Enter student id and pages: ");
        scanf("%d %d", &id, &pages);
        m2.type = 2;
        m2.id = id;
        m2.pages = pages;
        msgsnd(msgid, &m2, sizeof(m2) - sizeof(long), 0);
    }

    // THEN fork and exec child
    pid_t pid = fork();
    if(pid == 0){
        execl("./zc3", "zc3", NULL);
    } else {
        wait(NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}