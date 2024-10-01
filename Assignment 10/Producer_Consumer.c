#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct {
    int *items;
    int front, rear, msize;
} CQ;
CQ queue;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER; 
int isFull() {
    return (queue.front == (queue.rear + 1) % queue.msize);
}
int isEmpty() {
    return (queue.front == -1);
}
void enqueue(int item) {
    if (isFull()) {
        printf("Queue is full!\n");
        return;
    }
    if (queue.front == -1) {
        queue.front = queue.rear = 0;
    } else {
        queue.rear = (queue.rear + 1) % queue.msize;
    }
    queue.items[queue.rear] = item;
}
int dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! \n");
        return -1;
    }
    int item = queue.items[queue.front];
    if (queue.front == queue.rear) {
        queue.front = queue.rear = -1;
    } else {
        queue.front = (queue.front + 1) % queue.msize;
    }
    return item;
}
void* producer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        int item = rand() % 100;
        pthread_mutex_lock(&mutex);
        while (isFull()) {
            pthread_cond_wait(&full, &mutex);
        }
        enqueue(item);
        printf("Producer %d: Produced %d\n", id, item);

        pthread_cond_signal(&empty); 
        pthread_mutex_unlock(&mutex);  

        sleep(1); 
    }
    return NULL;
}
void* consumer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (isEmpty()) {
            pthread_cond_wait(&empty, &mutex);
        }
        int item = dequeue();
        printf("Consumer %d: Consumed %d\n", id, item);
        pthread_cond_signal(&full); 
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;
}
int main() {
    int num_producers, num_consumers;
    int queue_size=10;
    printf("Enter the number of producers: ");
    scanf("%d", &num_producers);
    printf("Enter the number of consumers: ");
    scanf("%d", &num_consumers);
    queue.items = (int*)malloc(queue_size * sizeof(int));
    queue.front = queue.rear = -1;
    queue.msize = queue_size;
    pthread_t prod[num_producers], cons[num_consumers];
    int producer_id[num_producers], consumer_id[num_consumers];
    for (int i = 0; i < num_producers; i++) {
        producer_id[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, (void*)&producer_id[i]);
    }
    for (int i = 0; i < num_consumers; i++) {
        consumer_id[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, (void*)&consumer_id[i]);
    }
    for (int i = 0; i < num_producers; i++) {
        pthread_join(prod[i], NULL);
    }

    for (int i = 0; i < num_consumers; i++) {
        pthread_join(cons[i], NULL);
    }
    free(queue.items);
    return 0;
}
