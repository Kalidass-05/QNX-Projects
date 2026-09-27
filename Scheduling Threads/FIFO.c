#include <stdio.h>
#include <pthread.h>
#include <sched.h>

void *high(void *arg)
{
    printf("HIGH priority thread\n");
    return NULL;
}

void *low(void *arg)
{
    printf("LOW priority thread\n");
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    // attribute creation: These objects contain configuration information for the threads.
    pthread_attr_t attr1;
    pthread_attr_t attr2;

    //Create scheduling parameter structures
    struct sched_param param1;  //
    struct sched_param param2;

    //Before using attr1 and attr2, we initialize them.
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    //scheduling policy: here FIFO is used
    pthread_attr_setschedpolicy(&attr1, SCHED_FIFO);
    pthread_attr_setschedpolicy(&attr2, SCHED_FIFO);

    param1.sched_priority = 20; //high priority
    param2.sched_priority = 10; //low priority

    //This associates the scheduling parameters with the corresponding attributes.
    pthread_attr_setschedparam(&attr1, &param1);
    pthread_attr_setschedparam(&attr2, &param2);

    pthread_create(&t1, &attr1, high, NULL);
    pthread_create(&t2, &attr2, low, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);

    return 0;
}
