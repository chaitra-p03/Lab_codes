#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<pthread.h>
#include<semaphore.h>

#define MAX 20

struct student{
    int id; 
    int pages;
};

struct shared{
    int n; 
    struct student arr[MAX];
};

sem_t sem;                      
pthread_mutex_t lock;     

int printers[3] = {0};

void* access_printer(void* arg){
    struct student *s = (struct student*)arg;

    printf("Student %d requesting printer\n", s->id);

    if(sem_trywait(&sem) != 0){
        printf("All printers busy. Student %d waiting...\n", s->id);
        sem_wait(&sem);
    }

    pthread_mutex_lock(&lock);

    int p_id = -1;
    for(int i = 0; i < 3; i++){
        if(printers[i] == 0){
            printers[i] = 1;
            p_id = i + 1;
            break;
        }
    }

    pthread_mutex_unlock(&lock);

    printf("Student %d allocated Printer %d\n", s->id, p_id);
    printf("Student %d printing %d pages\n", s->id, s->pages);

    sleep(1);

    printf("Student %d finished printing and released printer %d\n", s->id, p_id);

    pthread_mutex_lock(&lock);
    printers[p_id - 1] = 0;
    pthread_mutex_unlock(&lock);

    sem_post(&sem);

    return NULL;
}

int main(){
    int shmid = shmget((key_t)1234, sizeof(struct shared), 0666);
    struct shared *data = (struct shared*)shmat(shmid, NULL, 0);

    sem_init(&sem, 0, 3);              
    pthread_mutex_init(&lock, NULL);

    pthread_t t[data->n];

    for(int i = 0; i < data->n; i++){
        pthread_create(&t[i], NULL, access_printer, &data->arr[i]);
    }

    for(int i = 0; i < data->n; i++){
        pthread_join(t[i], NULL);
    }

    sem_destroy(&sem);
    pthread_mutex_destroy(&lock);
    shmdt(data);

    return 0;
}