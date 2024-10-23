#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
void *sum (void *arg) {
	int n;
	printf("Enter the number: ");
	scanf("%d", &n);
	int sum=0;
	for(int i=0;i<=n;i++){
		sum+=i;
	}
	printf("Total Sum: %d\n",sum);
	pthread_exit(NULL);
}
int main(){
	pthread_t th1;
	pthread_create(&th1,NULL,sum,NULL);
	pthread_join(th1,NULL);
	printf("exit");
	return 0;
}
