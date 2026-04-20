#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int read_count = 0;
sem_t mutex, write_lock;

void *reader(void *arg) {
    int id = *(int *)arg;

    // entry section
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)        // first reader locks out writers
        sem_wait(&write_lock);
    sem_post(&mutex);

    // reading
    printf("Reader %d is reading\n", id);
    sleep(1);

    // exit section
    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)        // last reader unlocks writers
        sem_post(&write_lock);
    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&write_lock);
    printf("Writer %d is writing\n", id);
    sleep(1);
    sem_post(&write_lock);

    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int rid[3] = {1, 2, 3};
    int wid[2] = {1, 2};

    sem_init(&mutex, 0, 1); 
    sem_init(&write_lock, 0, 1);

    // create 3 readers and 2 writers
    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &rid[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}