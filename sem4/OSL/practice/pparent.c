#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

struct shared {
    int arr[5];
    int sum;
    float avg;
    int done;
};

int main() {
    int id = shmget((key_t)123, sizeof(struct shared), 0666 | IPC_CREAT);
    struct shared *data = (struct shared *)shmat(id, NULL, 0);

    for(int i = 0; i < 5; i++) {
        printf("Enter number: ");
        scanf("%d", &data->arr[i]);
    }

    pid_t pid = fork();

    if(pid == 0) {
        // child
        execl("./child", "child", NULL);
    } else {
        // parent waits
        wait(NULL);
        printf("Sum = %d\n", data->sum);
        printf("Average = %.2f\n", data->avg);
        shmdt(data);
        shmctl(id, IPC_RMID, 0);
    }

    return 0;
}