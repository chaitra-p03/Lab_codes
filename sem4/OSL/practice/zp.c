#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

struct process {
    int pid;
    int bt;
};

struct shared {
    struct process p[4];
};

int main() {
    int id = shmget((key_t)1234, sizeof(struct shared), 0666 | IPC_CREAT);
    struct shared *data = (struct shared *)shmat(id, NULL, 0);

    for(int i = 0; i < 4; i++) {
        printf("Enter pid and bt: ");
        scanf("%d", &data->p[i].pid);
        scanf("%d", &data->p[i].bt);
    }

    printf("\nPID\tBT\n");
    for(int i = 0; i < 4; i++)
        printf("%d\t%d\n", data->p[i].pid, data->p[i].bt);

    pid_t pid = fork();
    if(pid == 0) {
        execl("./zc", "zc", NULL);
    } else {
        wait(NULL);
        shmdt(data);
        shmctl(id, IPC_RMID, 0);
    }
    return 0;
}