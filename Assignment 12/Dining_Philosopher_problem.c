#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS]; // Mutexes for each fork

void* philosopher(void* id) {
    int philosopher_id = *(int*)id;
    
    while (1) {
        printf("Philosopher %d is thinking.\n", philosopher_id);
        sleep(rand() % 3); // Simulate thinking time

        // Pick up left fork
        pthread_mutex_lock(&forks[philosopher_id]);
        printf("Philosopher %d picked up left fork.\n", philosopher_id);

        // Pick up right fork
        pthread_mutex_lock(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up right fork.\n", philosopher_id);

        // Eating
        printf("Philosopher %d is eating.\n", philosopher_id);
        sleep(rand() % 3); // Simulate eating time

        // Put down right fork
        pthread_mutex_unlock(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right fork.\n", philosopher_id);

        // Put down left fork
        pthread_mutex_unlock(&forks[philosopher_id]);
        printf("Philosopher %d put down left fork.\n", philosopher_id);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutexes for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

