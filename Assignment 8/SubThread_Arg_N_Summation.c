#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
void *sum(void* arg){
	int n=*((int *)arg);
	int sum=0;
	for(int i=0;i<=n;i++){
		sum+=i;
	}
	int *result=(int *)malloc(sizeof(int));
	*result=sum;
	pthread_exit(result);
}
int main(){
	pthread_t th1;
	int n;
	printf("Enter the number: ");
	scanf("%d",&n);
	pthread_create(&th1,NULL,sum,&n);
	printf("Joining the Thread\n");
	int *res;
	pthread_join(th1,(void **)&res);
	printf("Sum is %d\n",*res);
	return 0;
}
