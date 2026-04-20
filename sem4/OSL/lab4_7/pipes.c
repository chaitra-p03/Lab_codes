#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];  
    pid_t pid;
    char message[] = "Hello from parent!";
    char buffer[100];
    
    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }
    
    pid = fork();
    
    if (pid > 0) {  
        close(fd[0]);  
        write(fd[1], message, strlen(message) + 1);
        printf("Parent: Sent message\n");
        close(fd[1]);  
        
        wait(NULL);
        
    } else {  
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("Child: Received: %s\n", buffer);
        close(fd[0]);
    }
    
    return 0;
}