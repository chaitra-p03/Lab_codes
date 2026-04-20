#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>

struct msg1{
    long int type;
    int number;
};

struct msg2{
    long int type;
    char res[10];
};

int main(){
    int id = msgget((key_t) 1234, 0666 | IPC_CREAT);
    // send
    struct msg1 m;
    struct msg2 m2;
    m.type = 1;
    for(int i=0; i<5; i++){
        printf("Enter number: ");
        scanf("%d",&m.number);
        msgsnd(id,&m,sizeof(m.number),0);
        msgrcv(id,&m2,sizeof(m2.res),2,0);
        printf("Number is %s", m2.res);
    }

    msgctl(id,IPC_RMID,0);
}