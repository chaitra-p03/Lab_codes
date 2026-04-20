#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buf[SIZE];
int f = -1, r = -1;

sem_t mutex, full, empty;

void *produce(void *arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty);       
        sem_wait(&mutex);       
        r = (r + 1) % SIZE;
        buf[r] = i;
        printf("Produced: %d\n", i);
        sem_post(&mutex);  
        sem_post(&full); 
        sleep(1);
    }
    return NULL;
}

void *consume(void *arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);         // wait for item
        sem_wait(&mutex);        // lock
        f = (f + 1) % SIZE;
        int item = buf[f];
        printf("Consumed: %d\n", item);
        sem_post(&mutex);        // unlock
        sem_post(&empty);        // signal producer
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&mutex, 0, 1);      // 1 = unlocked
    sem_init(&full, 0, 0);       // 0 items initially
    sem_init(&empty, 0, SIZE); 

    pthread_create(&t1, NULL, produce, NULL);
    pthread_create(&t2, NULL, consume, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}