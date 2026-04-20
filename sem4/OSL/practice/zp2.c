#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/wait.h>

struct user{
    int id;
    long int size;
};

struct shared{
    int n; 
    struct user arr[20];
};

int main(){
    int id = shmget((key_t) 1234, sizeof(struct shared), 0666 | IPC_CREAT);
    struct shared * data = (struct shared *) shmat(id,NULL,0);

    printf("Enter no of users: ");
    scanf("%d",&data->n);
    for(int i=0; i<data->n; i++){
        printf("Enter user id and filesize ");
        scanf("%d %d",&data->arr[i].id, &data->arr[i].size);
    }

    printf("\nUSERID\tFILESIZE\n");
    for(int i=0; i<data->n; i++){
        printf("%d\t%d\n",data->arr[i].id, data->arr[i].size);
    }

    pid_t pid = fork();
    if(pid==0){
        execl("./zc2","zc2",NULL);
    }
    else{
        wait(NULL);
        shmdt(data);
        shmctl(id,IPC_RMID,0);
    }
    return 0;
}