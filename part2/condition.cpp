#include <semaphore.h>

class condition {
public:
    /**
     * Defining variables
     */
    int count;
    /**
     * Defining Semaphores
     */
    sem_t blocked; /* Maintains the blocked queue of process. */


    /**
     * Default Constructor
     */
    condition() {
        count = 0;
        sem_init(&blocked, 0, 0);
    }

    /**
     * Function to count the number of blocked threads in the given condition variable.
     * @return count
     */
    int blocked_count() {
        return count;
    }

    /**
     * A function that gives up exclusive access to the monitor
     * and suspends appropriate thread
     * @param *mutex, *next_, *next_count
     */
    void wait(sem_t *mutex, sem_t *next_, int *next_count) {
        count += 1; /* Increment the blocked thread count for given cv */
        if (*next_count > 0) {
            sem_post(next_); /* Resume a suspended thread. */
        } else {
            sem_post(mutex); /* Allow a new thread in the monitor */
        }
        sem_wait(&blocked); /* Blocks the current thread */
        count -= 1; /* Decrement the blocked thread count for given cv */
    }

    /**
     * Function to unblock the suspended thread at the head of queue, and resume execution
     * @param *mutex, *next_, *next_count
     */
    void signal(sem_t *mutex, sem_t *next_, int *next_count) {
        if (count > 0) { /* Dont signal anyone if no one is waiting. */
            *next_count += 1;
            sem_post(&blocked); /* Signal the blocked thread in the given condition variable */
            sem_wait(next_); /* Wait for the signaled thread to finish executing. HOARE Semantics */
            *next_count -= 1;
        }
        sem_post(mutex);
    }
};