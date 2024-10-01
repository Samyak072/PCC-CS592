#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<stdio.h>
int main(){
	int pid;
	printf("Starting Parent...\n");
	pid=fork();
	if(pid>0) {
		printf("Parent:PID=%d\tPPID=%d\n",getpid(),getppid());
		sleep(8);
		printf("The parent is died");
	}
	if(pid==0){
		printf("Child: PID=%d\tPPID=%d\n",getpid(),getppid());
		system("ps");
		sleep(15);
	}
	return 0;
}
