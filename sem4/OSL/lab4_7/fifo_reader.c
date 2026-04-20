#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd;
    int numbers[4];
    
    printf("Reader: Waiting for writer...\n");
    
    // Open FIFO for reading (blocks until writer opens)
    fd = open(FIFO_PATH, O_RDONLY);
    
    printf("Reader: Connected! Receiving data...\n");
    
    // Read data
    read(fd, numbers, sizeof(numbers));
    
    printf("Reader: Received numbers: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    close(fd);
    
    // Clean up FIFO
    unlink(FIFO_PATH);
    
    return 0;
}