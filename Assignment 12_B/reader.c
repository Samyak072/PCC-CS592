#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "psem.h"

#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
} SharedBuffer;

int main() {
    key_t key = 0720; // Shared memory key
    int shmid;
    SharedBuffer *buffer;

    // Attach shared memory segment
    if ((shmid = shmget(key, sizeof(SharedBuffer), 0666)) < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory
    if ((buffer = shmat(shmid, NULL, 0)) == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Initialize semaphores
    psem_t empty, full, mutex;
    psem_init(&empty, "empty", BUFFER_SIZE);
    psem_init(&full, "full", 0);
    psem_init(&mutex, "mutex", 1);

    int data;
    while (1) {
        // Wait for a full slot
        psem_wait(&full);

        // Enter critical section
        psem_wait(&mutex);

        // Read from buffer
        data = buffer->buffer[buffer->out];
        buffer->out = (buffer->out + 1) % BUFFER_SIZE;

        printf("Reader read data: %d\n", data);

        // Leave critical section
        psem_post(&mutex);

        // Signal empty slot
        psem_post(&empty);

        sleep(2); // Simulate reading time
    }

    return 0;
}
