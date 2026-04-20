#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define TEXT_SIZE 2048

struct shared_data {
    int written;
    char text[TEXT_SIZE];
};

int main() {
    int running = 1;
    
    int shmid = shmget(1234, sizeof(struct shared_data), 0666 | IPC_CREAT);
    struct shared_data *data = (struct shared_data *)shmat(shmid, NULL, 0);
    
    while(running) {
        if (data->written == 1) {
            printf("Received: %s", data->text);
            data->written = 0;
            
            if (strncmp(data->text, "end", 3) == 0)
                running = 0;
        }
        usleep(50000);
    }
    
    shmdt(data);
    shmctl(shmid, IPC_RMID, 0);
    
    return 0;
}