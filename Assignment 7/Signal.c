#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
void handle_signal(int signal_num) {
    printf("\nReceived signal %d, terminating the process.\n", signal_num);
    signal(SIGINT, SIG_DFL);
    raise(SIGINT); 
}
int main() {
    signal(SIGINT, handle_signal);
    while (1) {
        printf("Running... Press Ctrl+C to stop.\n");
        sleep(1);  // Sleep for 1 second to avoid spamming the console
    }
    return 0;
}

