#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define MAX 20

struct msg1 {
    long type;
    int n;
};

struct msg2 {
    long type;
    int id;
    int pages;
};

struct student {
    int id;
    int pages;
};

struct student arr[MAX];
int n;

sem_t sem;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int printers[3] = {0};  // 3 printers

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

    printf("Student %d finished and released Printer %d\n", s->id, p_id);

    pthread_mutex_lock(&lock);
    printers[p_id - 1] = 0;
    pthread_mutex_unlock(&lock);

    sem_post(&sem);

    return NULL;
}

int main(){
    int msgid = msgget(1234, 0666);

    struct msg1 m1;
    struct msg2 m2;

    msgrcv(msgid, &m1, sizeof(m1) - sizeof(long), 1, 0);
    n = m1.n;

    for(int i = 0; i < n; i++){
        msgrcv(msgid, &m2, sizeof(m2) - sizeof(long), 2, 0);

        arr[i].id = m2.id;
        arr[i].pages = m2.pages;
    }

    sem_init(&sem, 0, 3);

    pthread_t t[n];

    for(int i = 0; i < n; i++){
        pthread_create(&t[i], NULL, access_printer, &arr[i]);
    }

    for(int i = 0; i < n; i++){
        pthread_join(t[i], NULL);
    }

    sem_destroy(&sem);

    return 0;
}