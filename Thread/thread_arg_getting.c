#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_fun(void *arg)
{
	int *x = (int *)arg;
	printf("Argument Receives: %d\n", *x);
	return NULL;
}
int main(void) {
	//we can pass arguments to thread and able to process the data there.

	pthread_t tid;
	printf("Main Thread Running..\n");
	int x = 100;
	pthread_create(&tid, NULL, thread_fun, &x); // x address is passed.
	pthread_join(tid, NULL);
	printf("Thread Closed\n");
	return 0;
}
