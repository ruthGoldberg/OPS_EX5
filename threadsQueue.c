#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "Queue.h"


pQueue initQueue() {
    pQueue newQueue = (pQueue) malloc(sizeof(BusyQueue));
    if (!newQueue)
        return NULL;
    newQueue->size = 0;
    newQueue->head = NULL;
    newQueue->tail = NULL;
    pthread_mutex_init(&newQueue->mutex, NULL);
    pthread_cond_init(&newQueue->cond, NULL);
    return newQueue;
}

void enqueue(pQueue queue, void *data) {

    if (!queue) {
        perror("queue is null");
        return;
    }
    pthread_mutex_lock(&queue->mutex);
    if (!data) {
        perror("data is null");
        return;
    }
    pNode newNode = (pNode) malloc(sizeof(Node));
    if (!newNode)
        return;
    newNode->data = data;
    newNode->next = NULL;

    if (queue->size == 0) {
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    queue->size++;
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
}

int isEmpty(pQueue queue) {
    return queue->size == 0;
}

void *dequeue(pQueue queue) {
    pthread_mutex_lock(&queue->mutex);
    while (isEmpty(queue)) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }
    pNode temp = queue->head;
    void *data = temp->data;
    queue->head = temp->next;
    free(temp);
    queue->size--;

    pthread_mutex_unlock(&queue->mutex);
    return data;
}

void destroyQueue(pQueue queue) {
    pNode current = queue->head;
    while (current != NULL) {
        pNode temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }

    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->cond);
    free(queue);
}

