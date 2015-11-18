#ifndef SEM_H
#define SEM_H

#include <semaphore.h>

void createNewSemaphore(char* sem_name, sem_t* semdes);

void openSemaphore(char* sem_name, sem_t** semdes);

void closeSemaphore(char * sem_name);

void semPost(sem_t* semDes);

void semWait(sem_t* semDes);

#endif
