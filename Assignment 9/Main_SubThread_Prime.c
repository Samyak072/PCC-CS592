#include <stdio.h>
#include <math.h>
#include <pthread.h>
int isPrime(int n){
  if(n<2)
    return 0;
  for(int i=2; i <= n/2; i++)
    if(n%i == 0)
        return 0;
  return 1;
}
int thread1(void *n){
  printf("Sub-thread is starting......\n");
  pthread_t th;
  int status = isPrime(*(int*)n);
  printf("Sending status to Main thread....\n");
  printf("Sub-thread terminating....\n");
  return status;
}
int main(){
  printf("Main thread is starting......\n\n");
  pthread_t th;
  int n, status;
  printf("Enter the number : ");
  scanf("%d",&n);
  printf("Sending the number to sub-thread.....\n\n");
  pthread_create(&th, NULL, (void*)thread1, (void*)&n);
  pthread_join(th, (void*)&status);
  if(status == 0)
      printf("\n%d is not a prime number.\n",n);
  else 
    printf("\n%d is a prime number.\n",n);
  printf("\nMain thread terminating....\n");
  return 0;
}
