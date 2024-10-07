#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main() {
    pid_t p = fork();
    if (p > 0) {
        printf("Parent process with ID: %d\n", getpid());
        printf("Child process ID: %d\n", p);
        sleep(10);
        printf("Parent process waking up after sleep.\n");
    } 
    else if (p == 0) {
        printf("Child process with ID: %d is terminating.\n", getpid());
        exit(0); 
    } 
    else {
        printf("Fork failed.\n");
        return 1;
    }
    return 0;
}
