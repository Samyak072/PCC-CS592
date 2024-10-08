#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#define N 5  // Number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num + 4) % N
#define RIGHT (ph_num + 1) % N
sem_t mutex;
sem_t S[N];
int state[N];
int phil[N] = {0, 1, 2, 3, 4};  // Philosophers numbered 0 to 4
void test(int ph_num) {
    if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[ph_num] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", ph_num + 1, LEFT + 1, ph_num + 1);
        printf("Philosopher %d is eating\n", ph_num + 1);
        sem_post(&S[ph_num]);  // Allow philosopher to eat
    }
}
void take_fork(int ph_num) {
    sem_wait(&mutex);  // Entry section
    state[ph_num] = HUNGRY;
    printf("Philosopher %d is hungry\n", ph_num + 1);
    test(ph_num);  // Try to acquire forks and eat
    sem_post(&mutex);  // Exit section
    sem_wait(&S[ph_num]);  // Wait if forks are not available
    sleep(1);
}
void put_fork(int ph_num) {
    sem_wait(&mutex);  // Entry section
    state[ph_num] = THINKING;  // Philosopher is thinking
    printf("Philosopher %d puts down fork %d and %d\n", ph_num + 1, LEFT + 1, ph_num + 1);
    printf("Philosopher %d is thinking\n", ph_num + 1);
    test(LEFT);  // Test if left neighbor can eat
    test(RIGHT);  // Test if right neighbor can eat
    sem_post(&mutex);  // Exit section
}
void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1);
        take_fork(*i);  // Philosopher takes forks to eat
        sleep(0);
        put_fork(*i);  // Philosopher puts forks down after eating
    }
}
int main() {
    int i;
    pthread_t thread_id[N]; 
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++) {
        sem_init(&S[i], 0, 0);
    }
    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }
    return 0;
}
