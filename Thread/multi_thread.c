#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread1_fun(void* arg)
{
	printf("Thread 1 Running..\n");
	return NULL;
}

void *thread2_fun(void* arg)
{
	printf("Thread 2 Running..\n");
	return NULL;
}

int main(void) {
	pthread_t tid1, tid2;
	printf("Main thread running..\n");

	pthread_create(&tid1, NULL, thread1_fun, NULL); //create and call the thread1 function
	pthread_create(&tid2, NULL, thread2_fun, NULL);

	pthread_join(tid1, NULL); //wait for some time or else it will terminate thread suddenly.
	pthread_join(tid2, NULL);

	printf("All thread ends../n");
	return 0;
}
