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
    struct shared_data *data;
    char buffer[BUFSIZ];
    
    int shmid = shmget(1234, sizeof(struct shared_data), 0666 | IPC_CREAT);
    
    void * shared_memory = shmat(shmid, NULL, 0);
    
    data = (struct shared_data *)shared_memory;
    data->written = 0;
    
    while(running) {
        while (data->written == 1) {
            sleep(1);
        }
        
        printf("Enter text: ");
        fgets(buffer, BUFSIZ, stdin);
        
        strcpy(data->text, buffer);
        data->written = 1;
        
        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
    }
    
    shmdt(shared_memory);
    return 0;
}