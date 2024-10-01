#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main() {
	int pid,stat;
	puts("Starting Parent...\n");
	pid=fork();
	if(pid>0){
	printf("Parent:PID=%d\tPPID=%d\n",getpid(),getppid());
	sleep(15);
	wait(&stat);
	}
	if(pid==0){
		printf("Child: PID=%d\tPPID=%d\n",getpid(),getppid());
		sleep(8);
		printf("The child has died");
	}
	system("ps");
	return 0;
}
