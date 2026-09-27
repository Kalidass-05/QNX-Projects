/*
=========================================================
QNX SCHED_RR (ROUND-ROBIN) SCHEDULING
=========================================================

COMMANDS TO COMPILE AND RUN:

1. Create file:
   rr.c

2. Compile:
   qcc rr.c -o rr

3. Run:
   ./rr

4. Check threads:
   pidin threads

=========================================================
IMPORTANT CONCEPT:

Two threads:
    Thread 1 -> Priority 10 -> SCHED_RR
    Thread 2 -> Priority 10 -> SCHED_RR

Both have SAME priority.

SCHED_RR gives CPU time to each thread
using a time quantum.

Conceptually:

    Thread 1
       ↓
    Time Quantum
       ↓
    Thread 2
       ↓
    Time Quantum
       ↓
    Thread 1
       ↓
      ...

=========================================================
*/

#include <stdio.h>
#include <pthread.h>
#include <sched.h>

/*
pthread.h
    -> Thread functions

sched.h
    -> Scheduling policies such as SCHED_RR
*/

void *task(void *arg)
{
    int id = *(int *)arg;

    /*
    Get the thread ID number.
    id = 1 for Thread 1
    id = 2 for Thread 2
    */

    for (int i = 0; i < 10; i++)
    {
        printf("Task %d running\n", id);

        /*
        CPU-intensive work.

        We don't use sleep() here because
        we want the threads to remain READY/RUNNING
        and observe Round-Robin scheduling.
        */

        for (volatile long j = 0; j < 50000000; j++);
    }

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    /*
    t1 -> Thread 1
    t2 -> Thread 2
    */

    struct sched_param p;

    /*
    sched_param stores scheduling information,
    especially thread priority.
    */

    int id1 = 1;
    int id2 = 2;

    /*
    Create Thread 1
    */
    pthread_create(&t1, NULL, task, &id1);

    /*
    Create Thread 2
    */
    pthread_create(&t2, NULL, task, &id2);


    /*
    Set SAME priority for both threads.
    */
    p.sched_priority = 10;


    /*
    Set Thread 1 scheduling policy to SCHED_RR.

    SCHED_RR = Round-Robin scheduling
    */
    pthread_setschedparam(t1, SCHED_RR, &p);


    /*
    Set Thread 2 scheduling policy to SCHED_RR.
    */
    pthread_setschedparam(t2, SCHED_RR, &p);


    /*
    Wait for Thread 1 to finish.
    */
    pthread_join(t1, NULL);

    /*
    Wait for Thread 2 to finish.
    */
    pthread_join(t2, NULL);

    return 0;
}


/*
=========================================================
IMPORTANT LINES FOR REVISION
=========================================================

1. Create thread:

   pthread_create(&t1, NULL, task, &id1);


2. Set priority:

   p.sched_priority = 10;


3. Set Round-Robin policy:

   pthread_setschedparam(t1, SCHED_RR, &p);


4. Same for Thread 2:

   pthread_setschedparam(t2, SCHED_RR, &p);


5. Compile:

   qcc rr.c -o rr


6. Run:

   ./rr


7. Check threads:

   pidin threads


=========================================================
SCHED_RR LOGIC
=========================================================

Thread 1
Priority = 10
Policy   = SCHED_RR

        +

Thread 2
Priority = 10
Policy   = SCHED_RR

        ↓

Same priority
        ↓
Both are READY
        ↓
Scheduler gives CPU time
        ↓
Thread 1 runs
        ↓
Time quantum
        ↓
Thread 2 runs
        ↓
Time quantum
        ↓
Thread 1 runs
        ↓
...


=========================================================
INTERVIEW ANSWER
=========================================================

SCHED_RR is a preemptive scheduling policy in which
READY threads having the same priority share the CPU
using a time quantum.

=========================================================
FIFO vs RR
=========================================================

SCHED_FIFO
    ↓
Thread runs until:
    - it blocks
    - it yields
    - it terminates
    - higher-priority thread preempts it

SCHED_RR
    ↓
Thread runs for its time quantum
    ↓
Next same-priority READY thread gets CPU


=========================================================
MEMORY TRICK
=========================================================

FIFO → "Run until something happens"

RR   → "Run for a time slice"

=========================================================
*/
