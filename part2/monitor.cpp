#include "monitor.h"


int count(cond *cv) {
    return cv->count;
}

void wait(cond *cv) {
    cv->count += 1; /* Increment the blocked thread count for given cv */
    if (next_count > 0) {
        sem_post(&next_); /* Resume a suspended thread. */
    } else {
        sem_post(&mutex); /* Allow a new thread in the monitor */
    }
    sem_wait(&(cv->blocked));
    cv->count -=1; /* Decrement the blocked thread count for given cv */
}

void signal(cond *cv) {
    if (cv->count > 0) { /* Dont signal anyone if no one is waiting. */
        next_count += 1;
        sem_post(&(cv->blocked));
        sem_wait(&next_);
        next_count -= 1;
    }
}

void monitor_initialize() {
    empty.count = 0;
    full.count = 0;
    sem_init(&(full.blocked), 0, 0);
    sem_init(&(empty.blocked), 0, 0);
    sem_init(&mutex, 0, 1);
    sem_init(&next_, 0, 0);
}

void monitor_destroy_semaphores() {
    sem_destroy(&(full.blocked));
    sem_destroy(&(empty.blocked));
}

void monitor_insert(char item, void *threadid) {
    sem_wait(&mutex);
    /* Check if the buffer is full, if full wait */
    while ((int)buffer.size() == buffer_size) wait(&full);
    /* Terminating condition for the loop */
    if (num_items_produced < num_of_items) {
        //inserting item into the item queue
        cout << "p:<" << (intptr_t) threadid << ">, item: " << item << ", at " << buffer.size() << '\n';
        buffer.push_back(item);
        ++num_items_produced;
    } else {
        signal(&empty);
        sem_post(&mutex);
        exit(0);
    }
    signal(&empty);
    sem_post(&mutex);
}

void monitor_remove(void *threadid) {
    sem_wait(&mutex);
    /* Check if the buffer is empty, if empty wait. */
    while ((int)buffer.size() == 0) wait(&empty);
    /* Terminating condition for the loop */
    if (num_items_consumed < num_of_items) {
        //removing item from the item queue
        char item = buffer.back();
        buffer.pop_back();
        ++num_items_consumed;
        cout << "c:<" << (intptr_t) threadid << ">, item: " << item << ", at " << buffer.size() << '\n';
    } else {
        signal(&full);
        sem_post(&mutex);
        exit(0);
    }
    signal(&full);
    sem_post(&mutex);
}
