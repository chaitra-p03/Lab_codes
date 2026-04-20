#include<stdio.h>
#include<pthread.h>

int balance = 1000;
pthread_mutex_t mutex;

void *add(void * param){
    for(int i=0; i<10; i++){
        pthread_mutex_lock(&mutex);
        balance+=500;
        printf("Balance: %d\n",balance);
        pthread_mutex_unlock(&mutex);
    }
}

void *sub(void *param){
    for(int i=0; i<10; i++){
        pthread_mutex_lock(&mutex);
        balance-=200;
        printf("Balance: %d\n",balance);
        pthread_mutex_unlock(&mutex);
    }
}

int main(){
    pthread_t t1, t2;
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&t1,0,add,0);
    pthread_create(&t2,0,sub,0);
    pthread_join(t1,0);
    pthread_join(t2,0);
    pthread_mutex_destroy(&mutex);
    return 0;
}