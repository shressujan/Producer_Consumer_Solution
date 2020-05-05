#include "part2.h"


void parseInput(int argc, char **argv) {
    int option; /* A local variable that stores different options being passed in from the command line. */
    /* Using built-in getopt function to parse the command line input. */
    while ((option = getopt(argc, argv, "b:p:c:i:")) != -1) {
        switch (option) {
            case 'b':
                buffer_size = atoi(optarg);
                break;
            case 'p':
                producer_threads_max_count = atoi(optarg);
                break;
            case 'c':
                consumer_threads_max_count = atoi(optarg);
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

    /* Calling the parseInput function to begin parsing the command line args */
    parseInput(argc, argv);

    /* Setting the starting point for producing a series of pseudo-random integers */
    srand(time(NULL));

    /* initializing the semaphores */
    monitor_initialize();

    pthread_t *producer_threads = new pthread_t[producer_threads_max_count];
    pthread_t *consumer_threads = new pthread_t[consumer_threads_max_count];

    /* Creating producer threads*/
    for (int i = 0; i < producer_threads_max_count; i++) {
        pthread_create(&producer_threads[i], NULL, producer, (void *) (intptr_t) i);
    }
    /* Creating consumer threads*/
    for (int i = 0; i < consumer_threads_max_count; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, (void *) (intptr_t) i);
    }

    /* Waiting for producer_threads to terminate */
    for (int i = 0; i < producer_threads_max_count; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    /* Waiting for consumer_threads to terminate */
    for (int i = 0; i < consumer_threads_max_count; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    /* Calling the monitor_destroy_semaphores */
    monitor_destroy_semaphores();

    /* Terminates any thread waiting to terminate */
    pthread_exit(0);

    return 0;
}

void *producer(void *threadid) {

    /* Creating an infinite loop using while statement */
    while (true) {
        char alpha = alphabet[rand() % SIZE]; /* Selects a random character from alphabet array and stores in alpha variable. */
        /* Calling the monitor_insert function to insert the character alpha */
        monitor_insert(alpha, threadid);
    }
    /* Terminates waiting thread */
    pthread_exit(0);
}

void *consumer(void *threadid) {
    /* Creating an infinite loop using while statement */
    while (true) {
        /* Calling the monitor_remove to remove the last item from the buffer deque */
        monitor_remove(threadid);
    }
    /* Terminates waiting thread */
    pthread_exit(0);
}
