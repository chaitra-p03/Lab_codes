#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  

sem_t forks[N]; 

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;         
    int right = (id + 1) % N;

    printf("Philosopher %d is thinking\n", id);
    sleep(1);

    if (id % 2 == 0) {
        sem_wait(&forks[left]);
        printf("Philosopher %d picked up left fork %d\n", id, left);
        sem_wait(&forks[right]);
        printf("Philosopher %d picked up right fork %d\n", id, right);
    } else {
        sem_wait(&forks[right]);
        printf("Philosopher %d picked up right fork %d\n", id, right);
        sem_wait(&forks[left]);
        printf("Philosopher %d picked up left fork %d\n", id, left);
    }

   printf("Philosopher %d is eating\n", id);
    sleep(1);

    sem_post(&forks[left]);
    printf("Philosopher %d put down left fork %d\n", id, left);
    sem_post(&forks[right]);
    printf("Philosopher %d put down right fork %d\n", id, right);

    printf("Philosopher %d is thinking again\n", id);

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1); 

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&forks[i]);

    return 0;
}