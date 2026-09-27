#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;

void *producer(void *arg)
{
    printf("Producer: Working...\n");

    sleep(2);

    printf("Producer: Data ready\n");

    sem_post(&sem);  // INCREASES semaphore value by 1. Signals that data/resource is available.

    return NULL;
}

void *consumer(void *arg)
{
    printf("Consumer: Waiting for data...\n");

    sem_wait(&sem); //DECREASES semaphore value by 1.

    printf("Consumer: Data received\n");

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    sem_init(&sem, 0, 0);

    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);

    return 0;
}
