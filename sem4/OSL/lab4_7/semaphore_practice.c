#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore1, semaphore2;

void *thread1(void *param) {
    printf("Thread 1\n");
    sem_post(&semaphore1);
    return NULL;
}
void *thread2(void *param) {
    sem_wait(&semaphore1);
    printf("Thread 2\n");
    sem_post(&semaphore2);
    return NULL;
}
void *thread3(void *param) {
    sem_wait(&semaphore2);
    printf("Thread 3\n");
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    sem_init(&semaphore1, 0, 0);
    sem_init(&semaphore2, 0, 0);

    pthread_create(&t1, 0, thread1, 0);
    pthread_create(&t2, 0, thread2, 0);
    pthread_create(&t3, 0, thread3, 0);

    pthread_join(t1, 0);
    pthread_join(t2, 0);
    pthread_join(t3, 0);

    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
    return 0;
}