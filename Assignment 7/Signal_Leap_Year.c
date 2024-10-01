#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int leap_year_check(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                return 1; 
            else
                return 0;  
        } else {
            return 1; 
        }
    } else {
        return 0; 
    }
}
void handle_signal(int sig) {
    int year;
    printf("Child process received SIGUSR1. Enter a year to check if it's a leap year: ");
    scanf("%d", &year);
    if (leap_year_check(year)) {
        printf("The year %d is a leap year.\n", year);
    } else {
        printf("The year %d is not a leap year.\n", year);
    }
}
int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        signal(SIGUSR1, handle_signal);
        printf("Child process started and waiting for SIGUSR1 from parent.\n");
        while (1) {
            pause(); 
        }
    } else {
        printf("Parent process sending SIGUSR1 to child every 5 seconds.\n");
        while (1) {
            sleep(5);  
            kill(pid, SIGUSR1);  
            printf("Parent sent SIGUSR1 to child.\n");
        }
    }
    return 0;
}
