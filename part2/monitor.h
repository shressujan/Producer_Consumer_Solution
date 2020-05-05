//
// Created by Sujan Shrestha on 5/3/20.
//

#ifndef SSHRESTHA11_PA3_MONITOR_H
#define SSHRESTHA11_PA3_MONITOR_H

/**
 * Including the required C libraries.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <semaphore.h>
#include <iostream>
#include <string>


/**
 * Using namespace to define the context in which the variables, functions are defined.
 */
using namespace std;

/**
 * Defining a condition structure -> cond
 */
struct cond {
    sem_t blocked; /* Tracks whether the calling threads is blocked or not. */
    int count;
};

/**
 * Defining variables empty and full of type "cond"
 */
cond empty, full;
sem_t mutex;
sem_t next_;

/**
 * Defining a vector array to hold the char items produced.
 */
vector<char> buffer;

/**
 * Defining integer variables
 */
int num_items_produced;
int num_items_consumed;
int buffer_size;
int num_of_items;
int next_count =0;

/**
 * A function that returns the count of threads blocked on cv.
 * @param cv
 * @return
 */
int count(cond *cv);

/**
 * A function that gives up exclusive access to the monitor
 * and suspends appropriate thread
 * @param cv
 */
void wait(cond *cv);

/**
 * A function that unblocks suspended thread at head of queue.
 * @param cv
 */
void signal(cond *cv);

/**
 * A function to initialize starting values for different variables
 * @return
 */
extern void monitor_initialize();

/**
 * A function that destroys the pre-existing semaphores.
 */
extern void monitor_destroy_semaphores();

/**
 * A function that inserts the input char item in the buffer vector array.
 * @param item
 * @param threadid
 */
extern void monitor_insert(char item, void *threadid);

/**
 * A function that removes the last item from the buffer vector array.
 * @param threadid
 */
extern void monitor_remove(void *threadid);

#endif //SSHRESTHA11_PA3_MONITOR_H
