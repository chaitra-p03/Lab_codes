#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/wait.h>

struct shared{
    char string[50];
    char rev[50];
};
int main(){
    int id = shmget((key_t) 1243, sizeof(struct shared), 0666 | IPC_CREAT);
    struct shared * data = (struct shared *) shmat(id,NULL,0);
    printf("Enter string: ");
    fgets(data->string, 50, stdin);
    pid_t pid = fork();
    if(pid==0){
        execl("./c2", "c2", NULL);
    }
    else {
        wait(NULL);
    }
    printf("Reversed: %s\n", data->rev);
    shmdt(data);
    shmctl(id,IPC_RMID,0);
}