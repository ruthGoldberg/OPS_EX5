#ifndef EX5_OPS_QUEUE_H
#define EX5_OPS_QUEUE_H

typedef struct Node {
    void* data;
    struct Node* next;
} Node ,*pNode;

typedef struct {
    pNode head;
    pNode tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int size;
} BusyQueue ,*pQueue;

pQueue initQueue();
void enqueue(pQueue queue, void* item);
void destroyQueue(pQueue queue);
void* dequeue(pQueue queue);
int isEmpty(pQueue);
#endif //EX5_OPS_QUEUE_H
