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
    data->done=0;
    for(int i = 0; i < 3; i++) {
        printf("Enter name: ");
        fgets(data->s[i].name, 50, stdin);
        printf("Enter marks: ");
        scanf("%d", &data->s[i].marks);
        getchar();
    }
    data->done=1;
    shmdt(data);
    shmctl(id, IPC_RMID, 0);
}