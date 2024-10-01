#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define N 10
#define MAX 100
void *prime(void*x);
typedef struct limit{
	int thread_no;
	int upper;
	int lower;
}l;
int main(){
	pthread_t thread1[N];
	l lim[10];
	//t1 = pthread_create(&thread1 , NULL , func_1 , &n );
	for(int  i = 0; i<N; i++){
		lim[i].thread_no = i+1;
		lim[i].lower = i*(MAX/N)+1;
		lim[i].upper = lim[i].lower+(MAX/N)-1;
		pthread_create(&thread1[i] , NULL , prime , &lim[i]);
		}
	for(int i = 0; i<N; i++){
		pthread_join(thread1[i], NULL);
		}
	return 0;
	}
void *prime(void* x){
	l n = *((l *) x);
	printf("thread number: %d\n", n.thread_no);
	for(int i=n.lower; i<n.upper+1;i++){
		int flag = 0;
		for(int j=2;j<i/2;j++){
			if(i%j==0){
				flag=1;
				break;
				}
			}
		if(flag == 0){
			printf(" prime: %d\n",i);
			}
		}
	pthread_exit(NULL);
}

