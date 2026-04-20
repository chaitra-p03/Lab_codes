#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>

struct student {
    char name[50];
    int marks;
};

struct shared {
    struct student s[3];
    int done;
};

int main(){
    int id = shmget((key_t) 1234, sizeof(struct shared), 0666 | IPC_CREAT);
    struct shared * data = (struct shared *) shmat(id,NULL,0);
    while(data->done==0){
        sleep(1);
    }
    for(int i = 0; i < 3; i++) {
        if(data->s[i].marks >= 50) {
            printf("Name: %s Marks: %d\n", data->s[i].name, data->s[i].marks);
        }
    }
    shmdt(data);
    return 0;
}