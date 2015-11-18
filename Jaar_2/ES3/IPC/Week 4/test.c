#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore;

void threadfunc() {
    while (1) {
        sem_wait(&semaphore);
        printf("Hello from da thread!\n");
        sem_post(&semaphore);
        sleep(1);
    }
}

void threadfunc1() {
    while (1) {
        sem_wait(&semaphore);
        printf("Hello from da thread1!\n");
        sem_post(&semaphore);
        sleep(1);
    }
}

int main(void) {
    
    // initialize semaphore, only to be used with threads in this process, set value to 1
    sem_init(&semaphore, 0, 1);
    
    pthread_t *mythread, *mythread1;
    
    mythread = (pthread_t *)malloc(sizeof(*mythread));
    mythread1 = (pthread_t *)malloc(sizeof(*mythread1));
    
    // start the thread
    printf("Starting thread, semaphore is unlocked.\n");
    pthread_create(mythread, NULL, (void*)threadfunc, NULL);
    pthread_create(mythread1, NULL, (void*)threadfunc1, NULL);
    while(1){}

    
    return 0;
}
