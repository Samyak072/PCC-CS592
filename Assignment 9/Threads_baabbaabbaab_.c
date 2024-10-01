#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
sem_t mutex;
void *tf1(void *arg);
void *tf2(void *arg);
int main(){
	sem_init(&mutex,0,1);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,tf1,NULL);
	pthread_create(&t2,NULL,tf2,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("\n");
	sem_destroy(&mutex);
	return 0;
}
void *tf1(void *arg1){
	for(int i=1;i<=3;i++){
		sem_wait(&mutex);
		printf("ba");
		sem_post(&mutex);
		sleep(1);
	}
	pthread_exit(NULL);
}
void *tf2(void *arg2){
	for(int i=1;i<=3;i++){
	         sem_wait(&mutex);
	         printf("ab");
		 sem_post(&mutex);
		 sleep(1);
	}
        pthread_exit(NULL);
}

