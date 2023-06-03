#include "ActiveObject.h"
#include "st_pipeline.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *busyLoop(void *arg) {
    pActiveObject object = (pActiveObject) arg;
    void *data;
    int result;
    while (1) {
        if (object->function != AO1) {
            data = dequeue(object->queue);
        }
        if (object->function != NULL) {
            result = object->function(data);
            if (object->next) {
                enqueue(object->next->queue, (void *) result);
            }
        } else {
            pthread_mutex_lock(&object->queue->mutex);
            if (!object->isActive)
                break;
            pthread_mutex_unlock(&object->queue->mutex);
        }
        object->N--;
        if(object->N  == 0)
            break;
    }
    return NULL;
}

pActiveObject CreateActiveObject(func function, pActiveObject next, size_t N) {
    pActiveObject obj = (pActiveObject) malloc(sizeof(ActiveObject));
    if (obj == NULL) {
        return NULL;
    }
    obj->queue = initQueue();
    if (!obj->queue) {
        perror("init queue");
        exit(1);
    }
    obj->function = function;
    obj->N = N;
    obj->isActive = 1;
    obj->next = next;
    obj->thread = (pthread_t *) calloc(1, sizeof(pthread_t));

    if (pthread_create(obj->thread, NULL, busyLoop, obj)) {
        printf("failed create thread\n");

        destroyQueue(obj->queue);
        free(obj->thread);
        free(obj);
        return NULL;
    }
    return obj;
}

pQueue getQueue(void *this) {
    pActiveObject object = (pActiveObject) this;
    if (!object)
        return NULL;
    return object->queue;
}

void stop(pActiveObject object) {
    if (!object)
        return;
    object->isActive = 0;
    destroyQueue(object->queue);
    object->function = NULL;
    pthread_join(*(object->thread), NULL);
    free(object);

}