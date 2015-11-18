#ifndef SEM_H
#define SEM_H

#include <semaphore.h>

sem_t* createNewSemaphore(char* sem_name, int StartingValue);

sem_t* openSemaphore(char* sem_name);

void closeSemaphore(char* sem_name);

void semPost(sem_t* semDes);

void semWait(sem_t* semDes);

#endif
