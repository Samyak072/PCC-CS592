#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define READ_TIME 1 // Time for reading
#define WRITE_TIME 2 // Time for writing

pthread_mutex_t mutex; // Mutex for exclusive access to the writer
pthread_cond_t read_condition; // Condition variable for readers
int read_count = 0; // Number of readers reading
int write_count = 0; // Number of writers writing

void* reader(void* id) {
    int reader_id = *(int*)id;

    while (1) {
        // Reader starts waiting
        pthread_mutex_lock(&mutex);
        while (write_count > 0) { // Wait if there are writers
            pthread_cond_wait(&read_condition, &mutex);
        }
        read_count++; // Increment the number of readers
        pthread_mutex_unlock(&mutex); // Release the mutex

        // Reading data (simulated with sleep)
        printf("Reader %d is reading.\n", reader_id);
        sleep(READ_TIME);

        // Reader finishes reading
        pthread_mutex_lock(&mutex);
        read_count--; // Decrement the number of readers
        if (read_count == 0) {
            pthread_cond_broadcast(&read_condition); // Wake up writers waiting
        }
        pthread_mutex_unlock(&mutex);
        sleep(1); // Additional sleep before the next read
    }

    return NULL;
}

void* writer(void* id) {
    int writer_id = *(int*)id;

    while (1) {
        pthread_mutex_lock(&mutex);
        write_count++; // Increment the number of writers

        // Writing data (simulated with sleep)
        printf("Writer %d is writing.\n", writer_id);
        sleep(WRITE_TIME);

        // Writer finishes writing
        write_count--; // Decrement the number of writers
        if (write_count == 0) {
            pthread_cond_broadcast(&read_condition); // Wake up readers waiting
        }
        pthread_mutex_unlock(&mutex);
        sleep(1); // Additional sleep before the next write
    }

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    // Initialize mutex and condition variable
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&read_condition, NULL);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads (in practice, we may not want to join since this runs indefinitely)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&read_condition);

    return 0;
}


