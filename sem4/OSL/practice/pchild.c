#include <stdio.h>
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

    data->sum = 0;
    for(int i = 0; i < 5; i++) {
        data->sum += data->arr[i];
    }
    data->avg = (float)data->sum / 5;
    data->done = 1;

    shmdt(data);
    return 0;
}