#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void *thread1_func(void *param) {
    sem_post(&semaphore);   // signal
    return NULL;
}

void *thread2_func(void *param) {
    sem_wait(&semaphore);   // wait
    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&semaphore, 0, 0);

    pthread_create(&t1, 0, thread1_func, 0);
    pthread_create(&t2, 0, thread2_func, 0);

    pthread_join(t1, 0);
    pthread_join(t2, 0);

    sem_destroy(&semaphore);
    return 0;
}