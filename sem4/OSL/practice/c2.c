#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include <string.h>

struct shared{
    char string[50];
    char rev[50];
};
int main(){
    int id = shmget((key_t) 1243, sizeof(struct shared), 0666 | IPC_CREAT);
    struct shared * data = (struct shared *) shmat(id,NULL,0);
    int len = strlen(data->string);
    for(int i = 0; i < len/2; i++) {
        char temp = data->string[i];
        data->string[i] = data->string[len-1-i];
        data->string[len-1-i] = temp;
    }
    strcpy(data->rev, data->string);
    shmdt(data);
    return 0;
}