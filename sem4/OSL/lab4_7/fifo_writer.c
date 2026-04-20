#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd;
    int numbers[4] = {10, 20, 30, 40};
    
    // Create FIFO if it doesn't exist
    mkfifo(FIFO_PATH, 0666);
    
    printf("Writer: Waiting for reader...\n");
    
    // Open FIFO for writing (blocks until reader opens)
    fd = open(FIFO_PATH, O_WRONLY);
    
    printf("Writer: Connected! Sending data...\n");
    
    // Write data
    write(fd, numbers, sizeof(numbers));
    
    printf("Writer: Data sent\n");
    close(fd);
    
    return 0;
}