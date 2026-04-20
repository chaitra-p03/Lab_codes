#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/shm.h>

struct process {
    int pid;
    int bt;
};

struct shared {
    struct process p[4];
};

sem_t sem;

void *threadfunction(void *arg) {
    struct process *p = (struct process *)arg;
    printf("Process %d waiting for CPU\n", p->pid);
    sem_wait(&sem);
    printf("Process %d got CPU, executing for %d secs\n", p->pid, p->bt);
    sleep(p->bt);
    printf("Process %d finished, releasing CPU\n", p->pid);
    sem_post(&sem);
    return NULL;
}

int main() {
    int id = shmget((key_t)1234, sizeof(struct shared), 0666 | IPC_CREAT);
    struct shared *data = (struct shared *)shmat(id, NULL, 0);

    sem_init(&sem, 0, 2);  // 2 CPUs

    pthread_t threads[4];
    for(int i = 0; i < 4; i++)
        pthread_create(&threads[i], NULL, threadfunction, &data->p[i]);
    for(int i = 0; i < 4; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&sem);
    shmdt(data);
    return 0;
}
