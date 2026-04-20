#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/shm.h>


struct student{
    int id; 
    int pages;
};

#define MAX 20

struct shared{
    int n; 
    struct student arr[MAX];
};

int main(){
    int shmid = shmget((key_t) 1234, sizeof(struct shared),0666 | IPC_CREAT);
    struct shared * data = (struct shared *) shmat(shmid,NULL,0);

    printf("Enter no of students: ");
    scanf("%d",&data->n);
    for(int i=0; i<data->n; i++){
        printf("Enter id and no of pages: ");
        scanf("%d",&data->arr[i].id);
        scanf("%d",&data->arr[i].pages);
    }

    printf("\nStudent ID | pages\n");
    for(int i=0; i<data->n; i++){
        printf("\n%d %d\n",data->arr[i].id, data->arr[i].pages);
    }

    pid_t pid = fork();
    if(pid==0){
        execl("./zc1","zc1",NULL);
    }
    else{
    wait(NULL);

    shmdt(data);
    shmctl(shmid, IPC_RMID, 0);
    }
    return 0;
}
