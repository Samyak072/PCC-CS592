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

    // Create shared memory segment
    if ((shmid = shmget(key, sizeof(SharedBuffer), IPC_CREAT | 0666)) < 0) {
        perror("shmget failed");
        exit(1);
    }

    // Attach shared memory
    if ((buffer = shmat(shmid, NULL, 0)) == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Initialize shared buffer
    buffer->in = 0;

    // Initialize semaphores
    psem_t empty, full, mutex;
    psem_init(&empty, "empty", BUFFER_SIZE);
    psem_init(&full, "full", 0);
    psem_init(&mutex, "mutex", 1);

    int data = 1; // Data to write
    while (1) {
        // Produce data
        printf("Writer wrote data: %d\n", data);

        // Wait for an empty slot
        psem_wait(&empty);

        // Enter critical section
        psem_wait(&mutex);

        // Write to buffer
        buffer->buffer[buffer->in] = data;
        buffer->in = (buffer->in + 1) % BUFFER_SIZE;

        // Leave critical section
        psem_post(&mutex);

        // Signal full slot
        psem_post(&full);

        data++;
        sleep(1); // Simulate writing time
    }

    return 0;
}
