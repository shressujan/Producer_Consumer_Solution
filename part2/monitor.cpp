#include "monitor.h"


void monitor_initialize() {
    sem_init(&mutex, 0, 1);
    sem_init(&next_, 0, 0);
}

void monitor_destroy_semaphores() {
    sem_destroy(&(full.blocked));
    sem_destroy(&(empty.blocked));
}

void monitor_insert(char item, void *threadid) {
    sem_wait(&mutex); /* Lock Critical section */
    /* Check if the buffer is full, if full wait */
    while ((int)buffer.size() == buffer_size) full.wait(&mutex, &next_, &next_count);
    /* Terminating condition for the loop */
    if (num_items_produced < num_of_items) {
        //inserting item into the item queue
        cout << "p:<" << (intptr_t) threadid << ">, item: " << item << ", at " << buffer.size() << '\n';
        buffer.push_back(item);
        ++num_items_produced;
    } else {
        empty.signal(&mutex, &next_, &next_count);
        pthread_exit(0);
    }
    empty.signal(&mutex, &next_, &next_count);
}

void monitor_remove(void *threadid) {
    sem_wait(&mutex); /* Lock Critical section */
    /* Check if the buffer is empty, if empty wait. */
    while ((int)buffer.size() == 0) empty.wait(&mutex, &next_, &next_count);
    /* Terminating condition for the loop */
    if (num_items_consumed < num_of_items) {
        //removing item from the item queue
        char item = buffer.back();
        buffer.pop_back();
        ++num_items_consumed;
        cout << "c:<" << (intptr_t) threadid << ">, item: " << item << ", at " << buffer.size() << '\n';
        if(num_items_consumed == num_of_items) { /* Exit condition */
            exit(0);
        }
    }
    full.signal(&mutex, &next_, &next_count);
}
