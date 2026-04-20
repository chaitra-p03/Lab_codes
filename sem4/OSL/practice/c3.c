#include<stdio.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>

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
    struct msg1 m1;
    struct msg2 m2;
    m2.type = 2;
    for(int i=0; i<5; i++){
    msgrcv(id,&m1,sizeof(m1.number),1,0);
    if(m1.number%2==0){
        strcpy(m2.res,"Even");
    }
    else strcpy(m2.res,"Odd");

    msgsnd(id,&m2,sizeof(m2.res),0);
}
return 0;
}