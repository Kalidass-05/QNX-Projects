#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_fun(void *arg)
{
	printf("Hello from thread\n");
	return NULL;
}
int main(void) {
	pthread_t tid;
	printf("Main Thread Running\n");
	pthread_create(&tid, NULL, thread_fun, NULL); //(thread id, attributes, thread function, argument passed)
	pthread_join(tid, NULL); // Wait for thread tid to terminate.
	printf("Thread going to end");
	return 0;
}
