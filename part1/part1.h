//
// Created by Sujan Shrestha on 5/3/20.
//

#ifndef SSHRESTHA11_PA3_PART1_H
#define SSHRESTHA11_PA3_PART1_H


/**
 * Importing all the necessary libraries in C++.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

/**
 * Declaring semaphore variables globally.
 */
sem_t mutex;
sem_t empty;
sem_t full;

/**
 * Declaring integer variables globally used in this program.
 */
int buffer_size; // Stores the size of buffer.
int producer_threads_max; // Stores the maximum number of producer threads to be produced.
int consumer_threads_max; // Stores the maximum number of consumer threads to be produced.
int num_of_items; // Stores the number of items to be produced and consumed.
int num_items_produced; // Stores the number of items produced.
int num_items_consumed; // Stores the number of items consumed.

/**
 * Using namespace to define the context in which the variables, functions are defined.
 */
using namespace std;

/**
 * A vector array of char that stores the items produced.
 */
vector <char> buffer;

/**
 * A thread function that produces items.
 * @param threadid
 * @return
 */
void *producer(void *threadid);

/**
 * A thread function that consumes items.
 * @param threadid
 * @return
 */
void *consumer(void *threadid);

/**
 * A function that parses the command line input, and stores values in the respective variables.
 * @param argc
 * @param argv
 */
void parseInput(int argc, char **argv);

#endif //SSHRESTHA11_PA3_PART1_H
