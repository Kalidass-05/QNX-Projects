#include <stdio.h>
#include <pthread.h>

int count = 0;                 // Shared data
pthread_mutex_t mutex;         // Mutex

void *thread1(void *arg)
{
    pthread_mutex_lock(&mutex);

    count++;
    printf("Thread 1: count = %d\n", count);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *thread2(void *arg)
{
    pthread_mutex_lock(&mutex);

    count++;
    printf("Thread 2: count = %d\n", count);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    // Wait for threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final count = %d\n", count);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
