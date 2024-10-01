#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<stdio.h>
int main() {
	int pid;
	printf("STARTING PARENT...\n");
	pid=fork();
	if(pid>0){
	printf("Parent:PID=%d\tPPID=%d\n",getpid(),getppid());
	sleep(9);
	}
	if(pid==0){
		printf("Child: PID=%d\tPPID=%d\n",getpid(),getppid());
		system("ps");
		sleep(9);
	}
	return 0;
}
