#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;   // Shared data

void *thread1(void *arg)
{
    count++;
    printf("Thread 1: count = %d\n", count);

    return NULL;
}

void *thread2(void *arg)
{
    count++;
    printf("Thread 2: count = %d\n", count);

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final count = %d\n", count);

    return 0;
}
