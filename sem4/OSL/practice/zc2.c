#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

struct user{
    int id;
    long int size;
};

struct shared{
    int n; 
    struct user arr[20];
};

sem_t semaphore;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int disk[2] = {0}; 

void *assign(void *arg){
    struct user *u = (struct user *)arg;

    printf("User %d requesting disk\n", u->id);

    if(sem_trywait(&semaphore) != 0){
        printf("All disks busy. User %d waiting...\n", u->id);
        sem_wait(&semaphore);
    }

    pthread_mutex_lock(&lock);

    int disk_id = -1;
    for(int i = 0; i < 2; i++){
        if(disk[i] == 0){
            disk[i] = 1;
            disk_id = i + 1;
            break;
        }
    }

    pthread_mutex_unlock(&lock);

    printf("User %d allocated Disk %d\n", u->id, disk_id);
    printf("User %d writing %ld MB\n", u->id, u->size);

    sleep(1);

    printf("User %d finished and released Disk %d\n", u->id, disk_id);

    pthread_mutex_lock(&lock);
    disk[disk_id - 1] = 0;
    pthread_mutex_unlock(&lock);

    sem_post(&semaphore);

    return NULL;
}

int main(){
    int id = shmget((key_t)1234, sizeof(struct shared), 0666);
    struct shared *data = (struct shared *)shmat(id, NULL, 0);

    if(data->n <= 0){
        printf("No data received!\n");
        return 0;
    }

    printf("\nExecuting Disk Access Program...\n");

    sem_init(&semaphore, 0, 2);

    pthread_t t[data->n];

    for(int i = 0; i < data->n; i++){
        pthread_create(&t[i], NULL, assign, &data->arr[i]);
    }

    for(int i = 0; i < data->n; i++){
        pthread_join(t[i], NULL);
    }

    sem_destroy(&semaphore);
    shmdt(data);

    return 0;
}