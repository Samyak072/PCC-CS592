#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define DATASIZE 100
int main()
{
	int pfd[2];
	int pid;
	char write_msg[DATASIZE];
	char read_msg[DATASIZE];
	pipe(pfd);
	pid=fork();
	if(pid==0)
	{
		printf("Enter a message\n");
		fgets(write_msg,DATASIZE,stdin);
		write(pfd[1],write_msg,strlen(write_msg)+1);
	}
	else if(pid>1)
	{
		read(pfd[0],read_msg,DATASIZE);
		printf("message received %s\n",read_msg);
	}
	return 0;
}


