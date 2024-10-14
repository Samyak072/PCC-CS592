#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

// Define a structure to hold shared data
typedef struct {
    char str[100];   // Store the input string
    int result;      // Result of the palindrome check
} SharedData;

void* check_palindrome(void* arg) {
    SharedData* data = (SharedData*)arg;
    int len = strlen(data->str);
    int is_palindrome = 1; // Assume it's a palindrome initially

    for (int i = 0; i < len / 2; i++) {
        if (data->str[i] != data->str[len - i - 1]) {
            is_palindrome = 0; // Not a palindrome
            break;
        }
    }
    
    data->result = is_palindrome; // Store the result
    return NULL;
}

int main() {
    // Create shared memory
    int shm_fd = shm_open("my_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedData)); // Set the size of shared memory

    SharedData* data = mmap(0, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Process P1: Input string from user
    printf("Enter a string: ");
    fgets(data->str, sizeof(data->str), stdin);
    data->str[strcspn(data->str, "\n")] = 0; // Remove newline character

    // Create Process P2 using a thread for simplicity
    pthread_t thread;
    pthread_create(&thread, NULL, check_palindrome, data);
    
    // Wait for the thread to finish
    pthread_join(thread, NULL);

    // Process P1: Print the result
    printf("The result is: %d (1 for Palindrome, 0 for NOT Palindrome)\n", data->result);

    // Clean up
    munmap(data, sizeof(SharedData));
    shm_unlink("my_shm");

    return 0;
}

