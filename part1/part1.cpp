/**
 * The goal of this program is to solve the producer/consumer problem using semaphores.
 */

#include "part1.h"


void parseInput(int argc, char **argv) {
    int option; /* A local variable that stores different options being passed in from the command line. */
    /* Using built-in getopt function to parse the command line input. */
    while ((option = getopt(argc, argv, "b:p:c:i:")) != -1) {
        switch (option) {
            case 'b':
                buffer_size = atoi(optarg);
                sem_init(&empty, 0, buffer_size); /* Initializing the empty semaphore to buffer_size. */
                break;
            case 'p':
                producer_threads_max = atoi(optarg);
                break;
            case 'c':
                consumer_threads_max = atoi(optarg);
                break;
            case 'i':
                num_of_items = atoi(optarg);
                break;
            case ':':
                printf("argument required: %c\n", option);
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                break;
        }
    }
}

/**
 * Main driver function
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {

    /* Calling the parseInput function to begin parsing the command line args. */
    parseInput(argc, argv);

    /* Declaring pthread_t type variables globally. */
    pthread_t producer_threads[producer_threads_max]; // Stores produced threads.
    pthread_t consumer_threads[consumer_threads_max]; // Stores consumed threads.

    /* Initializing the semaphores mutex and full. */
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);

    /* Initializing the number of items produced and consumed to zero. */
    num_items_produced = 0;
    num_items_consumed = 0;

    /* Creating producer threads*/
    for (int i = 0; i < producer_threads_max; i++) {
        pthread_create(&producer_threads[i], NULL, producer, (void *) (intptr_t) i);
    }
    /* Creating consumer threads*/
    for (int i = 0; i < consumer_threads_max; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, (void *) (intptr_t) i);
    }

    /* Waiting for producer_threads to terminate */
    for (int i = 0; i < producer_threads_max; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    /* Waiting for consumer_threads to terminate */
    for (int i = 0; i < consumer_threads_max; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    /* Last thing that main() should do - destroy the semaphores */
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    /* Terminates any thread waiting to terminate */
    pthread_exit(0);

    return 0;
}

void *producer(void *threadid) {

    /* Creating an infinite loop using while statement */
    while (true) {
        /* Decrements the value of semaphores,
         * If either one of the semaphore is less than or equal to zero, the thread is blocked */
        sem_wait(&empty);
        sem_wait(&mutex);

        /* Terminating condition for the infinite loop */
        if (num_items_produced < num_of_items) {
            /* inserting an item char 'X' into the item queue */
            cout << "p:<" << (intptr_t) threadid << ">, item: " << 'X' << ", at " << buffer.size() << '\n';
            buffer.push_back('X');
            ++num_items_produced; /* Incrementing the number of items produced. */
        } else {    /* Exit condition, Increment the value of semaphores mutex and full */
            sem_post(&mutex);
            sem_post(&full);
            pthread_exit(0); /* Terminates the thread */
        }
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *threadid) {

    /* Creating an infinite loop using while statement */
    while (true) {
        /* Decrements the value of semaphores,
        * If either one of the semaphore is less than or equal to zero, the thread is blocked */
        sem_wait(&full);
        sem_wait(&mutex);

        /* Terminating condition for the infinite loop */
        if (num_items_consumed < num_of_items) {
            /* Removing the item char 'X' from the end of the item queue */
            buffer.pop_back();
            cout << "c:<" << (intptr_t) threadid << ">, item: X, at " << buffer.size() << '\n';
            ++num_items_consumed; /* Incrementing the number of items consumed. */
        } else { /* Exit condition, Increment the value of semaphores mutex and full */
            sem_post(&mutex);
            sem_post(&empty);
            pthread_exit(0);
        }
        sem_post(&mutex);
        sem_post(&empty);
    }
}
