#ifndef EX5_OPS_ACTIVEOBJECT_H
#define EX5_OPS_ACTIVEOBJECT_H

#include <pthread.h>
#include <stdio.h>
#include "Queue.h"

typedef int (*func)(void*);

typedef struct ActiveObject_{
    pQueue queue;
    pthread_t* thread;
    func function;
    int isActive;
    struct ActiveObject_* next;
    size_t N;
} ActiveObject ,*pActiveObject;

pActiveObject CreateActiveObject(func function , pActiveObject next , size_t N);
pQueue getQueue();
void stop(pActiveObject);
void* busyLoop(void* arg);
#endif //EX5_OPS_ACTIVEOBJECT_H
